const int N = 1e6 + 5;
const int MOD = 1e9 + 7;
ll fact[N], invFact[N];

// requires binpow(base, exp, mod)
void init_fact() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < N; ++i) fact[i] = fact[i - 1] * i % MOD;
    invFact[N - 1] = binpow(fact[N - 1], MOD - 2, MOD);
    for (int i = N - 2; i >= 1; --i) invFact[i] = invFact[i + 1] * (i + 1) % MOD;
}

ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}

ll nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invFact[n - r] % MOD;
}