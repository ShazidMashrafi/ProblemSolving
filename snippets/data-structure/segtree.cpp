template <typename T>
struct SegTree {
    int n;
    vector<T> tree;
    T neutral = 0; // INT_MAX for min, -INT_MAX for max, 0 for sum and gcd
    T merge(T a, T b) {
        return a + b; // min(a,b) or max(a,b) or gcd(a,b)
    }
    SegTree() : n(0) {}
    void build(const vector<T>& arr) {
        n = arr.size();
        tree.assign(2 * n, neutral);
        for (int i = 0; i < n; i++) tree[n + i] = arr[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
    void update(int p, T val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = merge(tree[p], tree[p ^ 1]);
        }
    }

    // from l to r - 1
    T query(int l, int r) {
        T resL = neutral, resR = neutral;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]);
            if (r & 1) resR = merge(tree[--r], resR);
        }
        return merge(resL, resR);
    }
};

int main()
{
    int n; cin >> n;
    vector<int>arr(n);
    for(auto &x : arr) cin >> x;
    SegTree<int> sg;
    sg.build(arr);
    
    sg.update(idx, val); 
    sg.query(l, r);
}
