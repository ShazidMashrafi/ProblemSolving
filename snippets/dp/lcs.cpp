struct LCS {
    string ans;
    int len = 0;

    LCS(auto& s, auto& t) {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (s[i] == t[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
                else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }

        int i = n, j = m;
        while (i > 0 && j > 0) {
            if (s[i - 1] == t[j - 1]) {
                ans += s[i - 1];
                --i; --j;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }
        reverse(ans.begin(), ans.end());
        len = ans.size();
    }
};