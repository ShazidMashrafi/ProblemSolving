struct Manacher {
    int n;
    string ms;
    vector<int> p;
    Manacher(const string &s) {
        ms = "^#";
        for (char c : s) { ms += c; ms += '#'; }
        ms += '$';
        n = ms.size();
        p.assign(n, 0);
        int l = 1, r = 1;
        for (int i = 1; i < n - 1; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while (ms[i - p[i]] == ms[i + p[i]]) p[i]++;
            if (i + p[i] > r) { l = i - p[i]; r = i + p[i]; }
        }
    }
    // 0-indexed [l, r] in original string
    bool is_palindrome(int l, int r) {
        return p[l + r + 2] - 1 >= r - l + 1;
    }
    // returns {start_idx, max_len} in original string
    pair<int, int> longest_palindrome() {
        int mx = 0, center = 0;
        for (int i = 1; i < n - 1; i++) {
            if (p[i] > mx) { mx = p[i]; center = i; }
        }
        int len = mx - 1;
        return {(center - len) / 2, len};
    }
};