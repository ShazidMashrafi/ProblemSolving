struct LIS {
    vector<int> idx;
    int len = 0;

    LIS(auto& a) {
        int n = a.size();
        vector<int> tail, t_idx, par(n, -1);
        for (int i = 0; i < n; ++i) {
            int p = lower_bound(tail.begin(), tail.end(), a[i]) - tail.begin(); // upper_bound for non-decreasing
            if (p == (int)tail.size()) {
                tail.push_back(a[i]);
                t_idx.push_back(i);
            } else {
                tail[p] = a[i];
                t_idx[p] = i;
            }
            if (p > 0) par[i] = t_idx[p - 1];
        }

        for (int c = t_idx.empty() ? -1 : t_idx.back(); c != -1; c = par[c])
            idx.push_back(c);
        reverse(idx.begin(), idx.end());
        len = idx.size();
    }
};