struct Mo {
    int B;
    struct Query {
        int l, r, id, b;
        bool operator<(Query o) const {
            if (b != o.b) return b < o.b;
            return (b & 1) ? r < o.r : r > o.r;
        }
    };

    int cur_ans = 0;
    vector<int> freq;

    Mo(int max_val = 1e6 + 5) : freq(max_val, 0) {}

    void add(int idx) {
        // update freq and cur_ans
    }

    void remove(int idx) {
        // update freq and cur_ans
    }

    vector<int> solve(auto& queries, int n) {
        B = max(1, (int)(n / sqrt(max(1, (int)queries.size()))));
        for (auto& q : queries) q.b = q.l / B;
        sort(queries.begin(), queries.end());

        vector<int> ans(queries.size());
        int cur_l = 0, cur_r = -1;
        for (auto& q : queries) {
            while (cur_l > q.l) add(--cur_l);
            while (cur_r < q.r) add(++cur_r);
            while (cur_l < q.l) remove(cur_l++);
            while (cur_r > q.r) remove(cur_r--);
            ans[q.id] = cur_ans;
        }
        return ans;
    }
};
