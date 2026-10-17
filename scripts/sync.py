#!/usr/bin/env python3
"""
sync.py - Compiles snippets/*.cpp, templates/cpt.cpp, and debuggers/codebook_debug.h
into cppSnippets.code-snippets (for VS Code & Antigravity IDE) and vjudge_codebook.md (for VJudge).
"""

import os
import re
import sys
import json
import shutil
import argparse
import subprocess
from pathlib import Path

# Paths
REPO_ROOT = Path(__file__).resolve().parent.parent
SNIPPETS_DIR = REPO_ROOT / "snippets"
OUTPUT_FILE = REPO_ROOT / "cppSnippets.code-snippets"
OUTPUT_CODEBOOK = REPO_ROOT / "vjudge_codebook.md"

EXTRA_SNIPPET_FILES = [
    REPO_ROOT / "templates" / "cpt.cpp",
    REPO_ROOT / "debuggers" / "codebook_debug.h",
]

EDITOR_SNIPPET_DIRS = [
    Path.home() / ".config" / "Code" / "User" / "snippets",
    Path.home() / ".config" / "Antigravity IDE" / "User" / "snippets",
    Path.home() / ".config" / "Antigravity" / "User" / "snippets",
]


def generate_anchor(title: str) -> str:
    """Normalizes title into a clean markdown slug."""
    slug = title.strip().lower()
    slug = re.sub(r"[^\w\s-]", "", slug)
    slug = re.sub(r"[\s]+", "-", slug)
    return slug


def snippet_from_file(file_path: Path):
    """Builds snippet entry dict from a .cpp or .h file."""
    try:
        rel_path = file_path.relative_to(SNIPPETS_DIR)
        category = rel_path.parts[0] if len(rel_path.parts) > 1 else "general"
    except ValueError:
        category = file_path.parent.name
    prefix = file_path.stem

    with open(file_path, "r", encoding="utf-8", errors="replace") as f:
        body = [line.rstrip("\r\n") for line in f]

    return {
        "prefix": prefix,
        "scope": "cpp",
        "description": f"[{category}] {prefix}",
        "body": body,
    }


def build_vjudge_codebook(snippets_dict: dict) -> str:
    """Assembles Table of Contents and formatted codeblocks into a single Markdown file."""
    categories = {}
    for key, snip in snippets_dict.items():
        desc = snip.get("description", "")
        if desc.startswith("[") and "]" in desc:
            cat = desc[1:desc.index("]")]
        else:
            cat = "general"
        categories.setdefault(cat, []).append((key, snip))

    priority = ["templates", "debuggers"]
    sorted_cats = sorted(
        categories.keys(),
        key=lambda c: (priority.index(c) if c in priority else 999, c),
    )

    lines = [
        "### 📖 Competitive Programming Codebook",
        "",
        "> Auto-generated from local snippets, templates, and debuggers.",
        "> **Tip for Lab PCs during contests:** Use `Ctrl + F` to search snippet prefixes directly.",
        "",
        "#### 📑 Table of Contents",
        "",
    ]

    # Generate TOC
    for cat in sorted_cats:
        lines.append(f"- **{cat}**")
        items = sorted(categories[cat], key=lambda x: x[0])
        for key, snip in items:
            anchor = generate_anchor(key)
            lines.append(f"  - [{key}](#{anchor})")
        lines.append("")

    # Generate content sections
    for cat in sorted_cats:
        lines.append("---")
        lines.append(f"#### {cat}")
        lines.append("")
        items = sorted(categories[cat], key=lambda x: x[0])
        for key, snip in items:
            lines.append(f"##### {key}")
            lines.append("```cpp")
            lines.extend(snip.get("body", []))
            lines.append("```")
            lines.append("")

    return "\n".join(lines).strip() + "\n"


def save_snippets(snippets_dict):
    """Saves dictionary to OUTPUT_FILE sorted by key and updates OUTPUT_CODEBOOK."""
    sorted_dict = {k: snippets_dict[k] for k in sorted(snippets_dict.keys())}

    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(sorted_dict, f, indent=4, ensure_ascii=False)
    print(f"Updated snippets file: {OUTPUT_FILE.relative_to(REPO_ROOT)}")

    codebook_md = build_vjudge_codebook(sorted_dict)
    with open(OUTPUT_CODEBOOK, "w", encoding="utf-8") as f:
        f.write(codebook_md)
    print(f"Updated VJudge codebook: {OUTPUT_CODEBOOK.relative_to(REPO_ROOT)}")


def full_build():
    """Scans all snippet and extra files and builds both editor snippets and VJudge codebook."""
    snippets = {}
    if not SNIPPETS_DIR.exists():
        print(f"Error: {SNIPPETS_DIR} does not exist.")
        sys.exit(1)

    for root, _, files in os.walk(SNIPPETS_DIR):
        for fname in sorted(files):
            if fname.endswith((".cpp", ".h")):
                fpath = Path(root) / fname
                key = fpath.stem
                snippets[key] = snippet_from_file(fpath)

    # Include extra snippet files (e.g. templates/cpt.cpp, debuggers/codebook_debug.h)
    for extra_file in EXTRA_SNIPPET_FILES:
        if extra_file.exists():
            snippets[extra_file.stem] = snippet_from_file(extra_file)

    save_snippets(snippets)
    print(f"Successfully compiled {len(snippets)} snippets.")
    return snippets


def incremental_update():
    """Updates only changed/added/deleted snippets based on git diff/status."""
    if not OUTPUT_FILE.exists() or not OUTPUT_CODEBOOK.exists():
        return full_build()

    extra_rel_paths = [str(p.relative_to(REPO_ROOT)) for p in EXTRA_SNIPPET_FILES]
    diff_targets = ["snippets/"] + extra_rel_paths

    # Get git diff --cached (staged) files, or fall back to unstaged if empty
    res = subprocess.run(
        ["git", "diff", "--cached", "--name-status"] + diff_targets,
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    diff_output = res.stdout.strip()

    if not diff_output:
        # Check unstaged status
        res = subprocess.run(
            ["git", "status", "--porcelain"] + diff_targets,
            cwd=REPO_ROOT,
            capture_output=True,
            text=True,
        )
        diff_output = res.stdout.strip()

    if not diff_output:
        # Nothing changed
        return

    # Load existing snippets
    try:
        with open(OUTPUT_FILE, "r", encoding="utf-8") as f:
            snippets = json.load(f)
    except Exception:
        return full_build()

    changed = False
    for line in diff_output.splitlines():
        parts = line.strip().split()
        if len(parts) < 2:
            continue
        status = parts[0]
        # In case of rename: R100 old new
        if status.startswith("R") and len(parts) >= 3:
            old_path = Path(parts[1])
            new_path = Path(parts[2])
            if old_path.suffix in [".cpp", ".h"]:
                snippets.pop(old_path.stem, None)
                changed = True
            if new_path.suffix in [".cpp", ".h"] and (REPO_ROOT / new_path).exists():
                snippets[new_path.stem] = snippet_from_file(REPO_ROOT / new_path)
                changed = True
            continue

        file_rel = Path(parts[1])
        if file_rel.suffix not in [".cpp", ".h"]:
            continue

        key = file_rel.stem
        full_path = REPO_ROOT / file_rel

        if status == "D":
            if key in snippets:
                del snippets[key]
                changed = True
                print(f"Removed snippet: {key}")
        elif full_path.exists():
            snippets[key] = snippet_from_file(full_path)
            changed = True
            print(f"Updated snippet: {key}")

    if changed:
        save_snippets(snippets)


def setup_symlinks():
    """Creates symlinks from editor user snippet directories to OUTPUT_FILE."""
    if not OUTPUT_FILE.exists():
        full_build()

    target = OUTPUT_FILE.resolve()

    for snip_dir in EDITOR_SNIPPET_DIRS:
        if not snip_dir.parent.parent.exists():
            # Editor not installed, skip
            continue

        snip_dir.mkdir(parents=True, exist_ok=True)
        link_path = snip_dir / "cppSnippets.code-snippets"

        # Check existing
        if link_path.is_symlink():
            current_target = link_path.resolve()
            if current_target == target:
                print(f"Already linked: {link_path} -> {target}")
                continue
            else:
                link_path.unlink()
        elif link_path.exists():
            backup = snip_dir / "cppSnippets.code-snippets.bak"
            print(f"Backing up existing file: {link_path} -> {backup}")
            shutil.move(link_path, backup)

        link_path.symlink_to(target)
        print(f"Created symlink: {link_path} -> {target}")


def main():
    parser = argparse.ArgumentParser(description="Sync snippets to VS Code / Antigravity IDE and export VJudge codebook")
    parser.add_argument("--symlink", action="store_true", help="Set up editor symlinks")
    parser.add_argument("--only-changed", action="store_true", help="Incrementally update changed files")
    args = parser.parse_args()

    if args.symlink:
        setup_symlinks()
    elif args.only_changed:
        incremental_update()
    else:
        full_build()


if __name__ == "__main__":
    main()
