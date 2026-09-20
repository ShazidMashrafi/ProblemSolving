// upper_bound for non-decreasing
vector<int> lis(const vector<int>& a) {
    int n = a.size();
    vector<int> tails, tail_idx, parent(n, -1);

    for (int i = 0; i < n; ++i) {
        int pos = lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin();
        if (pos == (int)tails.size()) {
            tails.push_back(a[i]);
            tail_idx.push_back(i);
        } else {
            tails[pos] = a[i];
            tail_idx[pos] = i;
        }
        if (pos > 0) parent[i] = tail_idx[pos - 1];
    }

    vector<int> res;
    for (int cur = tail_idx.empty() ? -1 : tail_idx.back(); cur != -1; cur = parent[cur])
        res.push_back(cur);
    reverse(res.begin(), res.end());
    return res;
}