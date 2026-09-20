struct LazySegTree {
    int n;
    vector<long long> tree, lazy;

    LazySegTree(int n = 0) : n(n), tree(4 * n, 0), lazy(4 * n, 0) {}

    void build(const vector<long long>& arr, int p, int l, int r) {
        if (l == r) { tree[p] = arr[l]; return; }
        int mid = (l + r) / 2;
        build(arr, 2 * p, l, mid);
        build(arr, 2 * p + 1, mid + 1, r);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
    void build(const vector<long long>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(arr, 1, 0, n - 1);
    }

    void apply(int p, int l, int r, long long val) {
        tree[p] += val * (r - l + 1);
        lazy[p] += val;
    }

    void push(int p, int l, int r) {
        if (!lazy[p]) return;
        int mid = (l + r) / 2;
        apply(2 * p, l, mid, lazy[p]);
        apply(2 * p + 1, mid + 1, r, lazy[p]);
        lazy[p] = 0;
    }

    void update(int ql, int qr, long long val, int p, int l, int r) {
        if (ql <= l && r <= qr) { apply(p, l, r, val); return; }
        push(p, l, r);
        int mid = (l + r) / 2;
        if (ql <= mid) update(ql, qr, val, 2 * p, l, mid);
        if (qr > mid)  update(ql, qr, val, 2 * p + 1, mid + 1, r);
        tree[p] = tree[2 * p] + tree[2 * p + 1];
    }
    void update(int ql, int qr, long long val) { update(ql, qr, val, 1, 0, n - 1); }

    long long query(int ql, int qr, int p, int l, int r) {
        if (ql <= l && r <= qr) return tree[p];
        push(p, l, r);
        int mid = (l + r) / 2;
        long long res = 0;
        if (ql <= mid) res += query(ql, qr, 2 * p, l, mid);
        if (qr > mid)  res += query(ql, qr, 2 * p + 1, mid + 1, r);
        return res;
    }
    long long query(int ql, int qr) { return query(ql, qr, 1, 0, n - 1); }
};
