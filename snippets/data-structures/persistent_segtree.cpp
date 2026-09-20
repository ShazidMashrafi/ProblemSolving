struct PersistentSegTree {
    struct Node {
        int l = 0, r = 0;
        int count = 0;
    };
    int n;
    vector<Node> tree;
    vector<int> roots;

    PersistentSegTree(int n = 0) : n(n) {
        tree.emplace_back();
        roots.push_back(0);
    }

    int update(int prev_root, int l, int r, int pos, int val) {
        int cur = tree.size();
        tree.push_back(tree[prev_root]);
        tree[cur].count += val;
        if (l == r) return cur;
        int mid = (l + r) / 2;
        if (pos <= mid)
            tree[cur].l = update(tree[prev_root].l, l, mid, pos, val);
        else
            tree[cur].r = update(tree[prev_root].r, mid + 1, r, pos, val);
        return cur;
    }
    void update(int pos, int val) {
        roots.push_back(update(roots.back(), 0, n - 1, pos, val));
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (!node || ql > r || qr < l) return 0;
        if (ql <= l && r <= qr) return tree[node].count;
        int mid = (l + r) / 2;
        return query(tree[node].l, l, mid, ql, qr) + query(tree[node].r, mid + 1, r, ql, qr);
    }
    int query(int version, int ql, int qr) {
        return query(roots[version], 0, n - 1, ql, qr);
    }

    int kth(int node_l, int node_r, int l, int r, int k) {
        if (l == r) return l;
        int mid = (l + r) / 2;
        int left_count = tree[tree[node_r].l].count - tree[tree[node_l].l].count;
        if (k <= left_count)
            return kth(tree[node_l].l, tree[node_r].l, l, mid, k);
        else
            return kth(tree[node_l].r, tree[node_r].r, mid + 1, r, k - left_count);
    }
    int kth(int version_l, int version_r, int k) {
        return kth(roots[version_l], roots[version_r], 0, n - 1, k);
    }
};