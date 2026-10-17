import unittest
import sys
from pathlib import Path

# Add scripts directory to path
REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO_ROOT / "scripts"))

# Import functions from sync
from sync import generate_anchor, build_vjudge_codebook, snippet_from_file


class TestSyncSnippets(unittest.TestCase):
    def test_generate_anchor(self):
        self.assertEqual(generate_anchor("[graphs] 01_bfs"), "graphs-01_bfs")
        self.assertEqual(generate_anchor("[data-structures] segtree_lazy"), "data-structures-segtree_lazy")
        self.assertEqual(generate_anchor("Template: cpt"), "template-cpt")

    def test_build_vjudge_codebook(self):
        sample_snippets = {
            "01_bfs": {
                "prefix": "01_bfs",
                "scope": "cpp",
                "description": "[graphs] 01_bfs",
                "body": ["// 01 BFS code", "void solve() {}"],
            },
            "dsu": {
                "prefix": "dsu",
                "scope": "cpp",
                "description": "[data-structures] dsu",
                "body": ["// DSU code"],
            },
        }

        md = build_vjudge_codebook(sample_snippets)

        # Check Table of Contents existence
        self.assertIn("### 📖 Competitive Programming Codebook", md)
        self.assertIn("#### 📑 Table of Contents", md)

        # Check category headers and anchor links in TOC
        self.assertIn("- **data-structures**", md)
        self.assertIn("- **graphs**", md)
        self.assertIn("[dsu](#dsu)", md)
        self.assertIn("[01_bfs](#01_bfs)", md)

        # Check content sections
        self.assertIn("#### data-structures", md)
        self.assertIn("##### dsu", md)
        self.assertIn("```cpp\n// DSU code\n```", md)
        self.assertIn("#### graphs", md)
        self.assertIn("##### 01_bfs", md)
        self.assertIn("```cpp\n// 01 BFS code\nvoid solve() {}\n```", md)

    def test_snippet_from_file_with_cpt(self):
        cpt_path = REPO_ROOT / "templates" / "cpt.cpp"
        if cpt_path.exists():
            snip = snippet_from_file(cpt_path)
            self.assertEqual(snip["prefix"], "cpt")
            self.assertIn("body", snip)
            self.assertTrue(len(snip["body"]) > 0)


if __name__ == "__main__":
    unittest.main()

