struct Trie {
    struct Node {
        int next[26] = {};
        int cnt = 0, end = 0;
    };
    vector<Node> t = {Node()};

    void clear() { t.assign(1, Node()); }

    void insert(const string& s) {
        int u = 0;
        for (char c : s) {
            int b = c - 'a';
            if (!t[u].next[b]) { t.emplace_back(); t[u].next[b] = t.size() - 1; }
            u = t[u].next[b];
            t[u].cnt++;
        }
        t[u].end++;
    }

    int count(const string& s, bool exact = false) {
        int u = 0;
        for (char c : s) {
            int b = c - 'a';
            if (!t[u].next[b]) return 0;
            u = t[u].next[b];
        }
        return exact ? t[u].end : t[u].cnt;
    }

    bool erase(const string& s) {
        if (!count(s, true)) return false;
        int u = 0;
        for (char c : s) {
            u = t[u].next[c - 'a'];
            t[u].cnt--;
        }
        t[u].end--;
        return true;
    }
};