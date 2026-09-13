#!/usr/bin/env python3
"""
sync_snippets.py - Compiles snippets/*.cpp into cppSnippets.code-snippets
and sets up symlinks for VS Code and Antigravity IDE.
"""

import os
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

EDITOR_SNIPPET_DIRS = [
    Path.home() / ".config" / "Code" / "User" / "snippets",
    Path.home() / ".config" / "Antigravity IDE" / "User" / "snippets",
    Path.home() / ".config" / "Antigravity" / "User" / "snippets",
]


def snippet_from_file(file_path: Path):
    """Builds snippet entry dict from a .cpp file."""
    rel_path = file_path.relative_to(SNIPPETS_DIR)
    category = rel_path.parts[0] if len(rel_path.parts) > 1 else "general"
    prefix = file_path.stem

    with open(file_path, "r", encoding="utf-8", errors="replace") as f:
        body = [line.rstrip("\r\n") for line in f]

    return {
        "prefix": prefix,
        "scope": "cpp",
        "description": f"[{category}] {prefix}",
        "body": body,
    }


def full_build():
    """Scans all .cpp files in snippets/ and builds cppSnippets.code-snippets."""
    snippets = {}
    if not SNIPPETS_DIR.exists():
        print(f"Error: {SNIPPETS_DIR} does not exist.")
        sys.exit(1)

    for root, _, files in os.walk(SNIPPETS_DIR):
        for fname in sorted(files):
            if fname.endswith(".cpp"):
                fpath = Path(root) / fname
                key = fpath.stem
                snippets[key] = snippet_from_file(fpath)

    save_snippets(snippets)
    print(f"Successfully compiled {len(snippets)} snippets to {OUTPUT_FILE.relative_to(REPO_ROOT)}")
    return snippets


def incremental_update():
    """Updates only changed/added/deleted snippets based on git diff/status."""
    if not OUTPUT_FILE.exists():
        return full_build()

    # Get git diff --cached (staged) files, or fall back to unstaged if empty
    res = subprocess.run(
        ["git", "diff", "--cached", "--name-status", "snippets/"],
        cwd=REPO_ROOT,
        capture_output=True,
        text=True,
    )
    diff_output = res.stdout.strip()

    if not diff_output:
        # Check unstaged status
        res = subprocess.run(
            ["git", "status", "--porcelain", "snippets/"],
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
            if old_path.name.endswith(".cpp"):
                snippets.pop(old_path.stem, None)
                changed = True
            if new_path.name.endswith(".cpp") and (REPO_ROOT / new_path).exists():
                snippets[new_path.stem] = snippet_from_file(REPO_ROOT / new_path)
                changed = True
            continue

        file_rel = Path(parts[1])
        if not file_rel.name.endswith(".cpp"):
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
        print(f"Incrementally updated {OUTPUT_FILE.relative_to(REPO_ROOT)}")


def save_snippets(snippets_dict):
    """Saves dictionary to OUTPUT_FILE sorted by key."""
    sorted_dict = {k: snippets_dict[k] for k in sorted(snippets_dict.keys())}
    with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
        json.dump(sorted_dict, f, indent=4, ensure_ascii=False)


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
            backup = snip_dir / f"cppSnippets.code-snippets.bak"
            print(f"Backing up existing file: {link_path} -> {backup}")
            shutil.move(link_path, backup)

        link_path.symlink_to(target)
        print(f"Created symlink: {link_path} -> {target}")


def main():
    parser = argparse.ArgumentParser(description="Sync snippets to VS Code / Antigravity IDE")
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
