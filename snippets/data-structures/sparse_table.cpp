template <typename T>
struct SparseTable {
    int n;
    vector<vector<T>> st;

    T merge(T a, T b) {
        return min(a, b); // max(a, b), gcd(a, b), a & b
    }

    SparseTable(const vector<T>& arr) {
        n = arr.size();
        int k = __lg(n) + 1;
        st.assign(k, vector<T>(n));
        st[0] = arr;
        for (int j = 1; j < k; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = merge(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T query(int l, int r) {
        int j = __lg(r - l + 1);
        return merge(st[j][l], st[j][r - (1 << j) + 1]);
    }
};