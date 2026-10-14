// requires binpow(base, exp, mod)
struct Comb {
    int n, mod;
    vector<ll> fact, inv;

    Comb(int n = 1e6 + 5, int mod = 1e9 + 7) : n(n), mod(mod), fact(n), inv(n) {
        fact[0] = inv[0] = 1;
        for (int i = 1; i < n; ++i) fact[i] = fact[i - 1] * i % mod;
        inv[n - 1] = binpow(fact[n - 1], mod - 2, mod);
        for (int i = n - 2; i >= 1; --i) inv[i] = inv[i + 1] * (i + 1) % mod;
    }

    ll nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * inv[r] % mod * inv[n - r] % mod;
    }

    ll nPr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * inv[n - r] % mod;
    }
};