const int MOD1 = 127657753, MOD2 = 987654319;
const int base1 = 137, base2 = 277;
const int MAXN = 1e6 + 9;
vector<pair<int, int>> pw(MAXN), inv_pw(MAXN);

// requires binpow(base, exp, mod)
void precal_pow() {
    if (pw[0].first != 0) return;
    pw[0] = inv_pw[0] = {1, 1};
    int inv_b1 = binpow(base1, MOD1 - 2, MOD1);
    int inv_b2 = binpow(base2, MOD2 - 2, MOD2);
    for (int i = 1; i < MAXN; i++) {
        pw[i].first = (1LL * pw[i - 1].first * base1) % MOD1;
        pw[i].second = (1LL * pw[i - 1].second * base2) % MOD2;
        inv_pw[i].first = (1LL * inv_pw[i - 1].first * inv_b1) % MOD1;
        inv_pw[i].second = (1LL * inv_pw[i - 1].second * inv_b2) % MOD2;
    }
}

struct Hashing {
    int n;
    string s;
    vector<pair<int, int>> hs, rhs;
    Hashing() {}
    Hashing(const string &_s) {
        precal_pow();
        s = _s;
        n = s.size();
        hs.assign(n + 1, {0, 0});
        rhs.assign(n + 1, {0, 0});
        for (int i = 0; i < n; i++) {
            hs[i + 1].first = (hs[i].first + 1LL * pw[i].first * s[i]) % MOD1;
            hs[i + 1].second = (hs[i].second + 1LL * pw[i].second * s[i]) % MOD2;
            rhs[i + 1].first = (rhs[i].first + 1LL * pw[i].first * s[n - 1 - i]) % MOD1;
            rhs[i + 1].second = (rhs[i].second + 1LL * pw[i].second * s[n - 1 - i]) % MOD2;
        }
    }
    pair<int, int> get_hash(int l, int r) { // 1-indexed [l, r]
        pair<int, int> ans;
        ans.first = (1LL * (hs[r].first - hs[l - 1].first + MOD1) * inv_pw[l - 1].first) % MOD1;
        ans.second = (1LL * (hs[r].second - hs[l - 1].second + MOD2) * inv_pw[l - 1].second) % MOD2;
        return ans;
    }
    pair<int, int> get_rev_hash(int l, int r) { // 1-indexed [l, r]
        int rev_l = n - r + 1, rev_r = n - l + 1;
        pair<int, int> ans;
        ans.first = (1LL * (rhs[rev_r].first - rhs[rev_l - 1].first + MOD1) * inv_pw[rev_l - 1].first) % MOD1;
        ans.second = (1LL * (rhs[rev_r].second - rhs[rev_l - 1].second + MOD2) * inv_pw[rev_l - 1].second) % MOD2;
        return ans;
    }
    pair<int, int> get_hash() { return get_hash(1, n); }
    bool is_palindrome(int l, int r) { return get_hash(l, r) == get_rev_hash(l, r); }
};