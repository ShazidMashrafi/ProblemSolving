ll binpow(ll a, ll b, ll mod = 1e9 + 7) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

ll modInverse(ll a, ll m = 1e9 + 7) {
    return binpow(a, m - 2, m);
}