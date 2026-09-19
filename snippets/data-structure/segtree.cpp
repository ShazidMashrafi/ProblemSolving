template <typename T>
struct SegTree {
    int n;
    vector<T> tree;
    T neutral = 0; // min: INF, max: -INF, sum/gcd: 0

    T merge(T a, T b) {
        return a + b; // min(a,b), max(a,b), gcd(a,b)
    }

    SegTree(int n = 0, T def = 0) : n(n), neutral(def), tree(2 * n, def) {}

    SegTree(const vector<T>& arr, T def = 0) : neutral(def) {
        build(arr);
    }

    void build(const vector<T>& arr) {
        n = arr.size();
        tree.assign(2 * n, neutral);
        for (int i = 0; i < n; i++) tree[n + i] = arr[i];
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }

    void update(int p, T val) {
        for (tree[p += n] = val; p > 1; p >>= 1) {
            tree[p >> 1] = merge(tree[p & ~1], tree[p | 1]);
        }
    }

    void add(int p, T val) {
        update(p, merge(tree[p + n], val));
    }

    T query(int l, int r) {
        T resL = neutral, resR = neutral;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = merge(resL, tree[l++]);
            if (r & 1) resR = merge(tree[--r], resR);
        }
        return merge(resL, resR);
    }
};