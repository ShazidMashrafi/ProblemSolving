struct MergeSortTree {
    int n;
    vector<vector<int>> tree;

    MergeSortTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(arr, 1, 0, n - 1);
    }

    void build(const vector<int>& arr, int p, int l, int r) {
        if (l == r) { tree[p] = {arr[l]}; return; }
        int mid = (l + r) / 2;
        build(arr, 2 * p, l, mid);
        build(arr, 2 * p + 1, mid + 1, r);
        merge(tree[2 * p].begin(), tree[2 * p].end(),
              tree[2 * p + 1].begin(), tree[2 * p + 1].end(),
              back_inserter(tree[p]));
    }

    // Count elements <= x in range [ql, qr]
    int count_le(int ql, int qr, int x, int p, int l, int r) {
        if (ql <= l && r <= qr) {
            return upper_bound(tree[p].begin(), tree[p].end(), x) - tree[p].begin();
        }
        int mid = (l + r) / 2, res = 0;
        if (ql <= mid) res += count_le(ql, qr, x, 2 * p, l, mid);
        if (qr > mid)  res += count_le(ql, qr, x, 2 * p + 1, mid + 1, r);
        return res;
    }
    int count_le(int ql, int qr, int x) { return count_le(ql, qr, x, 1, 0, n - 1); }
};