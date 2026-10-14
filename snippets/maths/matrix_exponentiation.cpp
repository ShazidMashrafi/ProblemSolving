struct Mat {
    int n;
    vector<vector<ll>> a;

    Mat(int n) : n(n), a(n, vector<ll>(n, 0)) {}

    static Mat id(int n) {
        Mat res(n);
        for (int i = 0; i < n; ++i) res.a[i][i] = 1;
        return res;
    }

    Mat mul(auto& o, ll m = 1e9 + 7) const {
        Mat res(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    res.a[i][j] = (res.a[i][j] + a[i][k] * o.a[k][j]) % m;
                }
            }
        }
        return res;
    }

    Mat pow(ll p, ll m = 1e9 + 7) {
        Mat res = Mat::id(n), base = *this;
        while (p > 0) {
            if (p & 1) res = res.mul(base, m);
            base = base.mul(base, m);
            p >>= 1;
        }
        return res;
    }
};
