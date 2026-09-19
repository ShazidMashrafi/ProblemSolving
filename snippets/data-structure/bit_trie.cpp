struct BitTrie {
    static const int BITS = 30; // 60 for ll
    struct Node {
        int next[2] = {};
        int cnt = 0;
    };
    vector<Node> t = {Node()};

    void clear() { t.assign(1, Node()); }

    void insert(int x) {
        int u = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (!t[u].next[b]) { t.emplace_back(); t[u].next[b] = t.size() - 1; }
            u = t[u].next[b];
            t[u].cnt++;
        }
    }

    bool erase(int x) {
        int u = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (!t[u].next[b] || t[t[u].next[b]].cnt == 0) return false;
            u = t[u].next[b];
        }
        u = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            u = t[u].next[(x >> i) & 1];
            t[u].cnt--;
        }
        return true;
    }

    int max_xor(int x) {
        int u = 0, res = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            int want = 1 - b;
            if (t[u].next[want] && t[t[u].next[want]].cnt > 0) {
                res |= (1 << i);
                u = t[u].next[want];
            } else {
                u = t[u].next[b];
            }
        }
        return res;
    }

    int min_xor(int x) {
        int u = 0, res = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            if (t[u].next[b] && t[t[u].next[b]].cnt > 0) {
                u = t[u].next[b];
            } else {
                res |= (1 << i);
                u = t[u].next[1 - b];
            }
        }
        return res;
    }

    // Count elements v such that (x ^ v) < k
    int count_xor_lt(int x, int k) {
        int u = 0, res = 0;
        for (int i = BITS - 1; i >= 0; --i) {
            int b = (x >> i) & 1;
            int kb = (k >> i) & 1;
            if (kb) {
                if (t[u].next[b]) res += t[t[u].next[b]].cnt;
                u = t[u].next[1 - b];
            } else {
                u = t[u].next[b];
            }
            if (!u) break;
        }
        return res;
    }
};