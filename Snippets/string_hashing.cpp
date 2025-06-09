// This is the polynomial hash function
// hash(s) = s[0] + (s[1] * p) + (s[i] * p\^2) + ... + (s[n - 1] * p\^(n-1))
int N = 1e6 + 9; 
const int MOD1 = 127657753, MOD2 = 987654319;
const int base1 = 137, base2 = 277;
vector<pair<int, int>>pw(N), inv_pw(N);

int BE(int x, int y, int mod){ // O(logn)
    int res = 1;
    x %= mod;
    if(x < 0) x += mod;
    while(y > 0){
        if(y & 1) res = (1LL * res * x) % mod; // MOD
        y >>= 1; // -> y /= 2;
        x = (1LL * x * x) % mod; // MOD
    } // MOD for larger numbers
    return res;
}

void precal_pow() { // O(N)
    pw[0] = {1, 1};
    inv_pw[0] = {1, 1};
    int inv_base1 = BE(base1, MOD1 - 2, MOD1);
    int inv_base2 = BE(base2, MOD2 - 2, MOD2);
    for(int i = 1; i < N; i++) {
        pw[i].first = (1LL * pw[i - 1].first * base1) % MOD1;
        pw[i].second = (1LL * pw[i - 1].second * base2) % MOD2;
        inv_pw[i].first = (1LL * inv_pw[i - 1].first * inv_base1) % MOD1;
        inv_pw[i].second = (1LL * inv_pw[i - 1].second * inv_base2) % MOD2;
    }
}

struct Hashing {
    int n;
    string s; // 0 - indexed
    vector<pair<int, int>> hs; // 1 - indexed
    Hashing() {}
    Hashing(string _s) { // O(n)
        n = size(_s);
        s = _s;
        hs.emplace_back(0, 0);
        for(int i = 0; i < n; i++) {
            pair<int, int> p;
            p.first = (hs[i].first + (1LL * pw[i].first * s[i]) % MOD1) % MOD1;
            p.second = (hs[i].second + (1LL * pw[i].second * s[i]) % MOD2) % MOD2;
            hs.push_back(p);
        }
    }
    pair<int, int> get_hash(int l, int r) { // 1 - indexed          // O(1)
        assert(1 <= l && l <= r && r <= n); // will cause RE
        pair<int, int> ans;
        ans.first = ((hs[r].first - hs[l - 1].first + MOD1) * 1LL * inv_pw[l - 1].first) % MOD1;
        ans.second = ((hs[r].second - hs[l - 1].second + MOD2) * 1LL * inv_pw[l - 1].second) % MOD2;
        return ans;
    }
    pair<int, int> get_hash() { // gets full string hash            // O(1)
        return get_hash(1, n);
    }
};

    // Same as String Hashing, only change in hashing struct
    struct Hashing {
    int n;
    string s; // 0 - indexed
    vector<pair<int, int>> hs, rhs; // 1 - indexed
    Hashing() {}
    Hashing(string &_s) {
        n = size(_s);
        s = _s;
        hs.emplace_back(0, 0);
        rhs.emplace_back(0, 0);
        for(int i = 0; i < n; i++) {
            pair<int, int> p, rp;
            p.first = (hs[i].first + (1LL * pw[i].first * s[i]) % MOD1) % MOD1;
            p.second = (hs[i].second + (1LL * pw[i].second * s[i]) % MOD2) % MOD2;
            hs.push_back(p);
            
            rp.first = (rhs[i].first + (1LL * pw[i].first * s[n - i - 1]) % MOD1) % MOD1;
            rp.second = (rhs[i].second + (1LL * pw[i].second * s[n - i - 1]) % MOD2) % MOD2;
            rhs.push_back(rp);
        }
    }
    pair<int, int> get_hash(int l, int r) { // 1 - indexed
        assert(1 <= l && l <= r && r <= n); // will cause RE
        pair<int, int> ans;
        ans.first = ((hs[r].first - hs[l - 1].first + MOD1) * 1LL * inv_pw[l - 1].first) % MOD1;
        ans.second = ((hs[r].second - hs[l - 1].second + MOD2) * 1LL * inv_pw[l - 1].second) % MOD2;
        return ans;
    }
    pair<int, int> get_rev_hash(int _l, int _r) { // 1 - indexed
        int l = n - _r + 1; 
        int r = n - _l + 1;
        assert(1 <= l && l <= r && r <= n); // will cause RE
        pair<int, int> ans;
        ans.first = ((rhs[r].first - rhs[l - 1].first + MOD1) * 1LL * inv_pw[l - 1].first) % MOD1;
        ans.second = ((rhs[r].second - rhs[l - 1].second + MOD2) * 1LL * inv_pw[l - 1].second) % MOD2;
        return ans;
    }
    pair<int, int> get_hash() { // gets full string hash
        return get_hash(1, n);
    }
    bool is_palindrome(int l, int r) {
        return (get_hash(l, r) == get_rev_hash(l, r));
    }
};
