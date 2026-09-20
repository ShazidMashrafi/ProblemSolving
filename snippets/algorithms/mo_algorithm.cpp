const int BLOCK = 450;

struct Query {
    int l, r, id;
    bool operator<(const Query& other) const {
        int b1 = l / BLOCK, b2 = other.l / BLOCK;
        if (b1 != b2) return b1 < b2;
        return (b1 & 1) ? r < other.r : r > other.r;
    }
};

int cur_ans = 0;
int freq[1000005];

void add(int idx) {
}

void remove(int idx) {
}

vector<int> mo(vector<Query>& queries) {
    sort(queries.begin(), queries.end());
    vector<int> ans(queries.size());
    int cur_l = 0, cur_r = -1;

    for (const auto& q : queries) {
        while (cur_l > q.l) add(--cur_l);
        while (cur_r < q.r) add(++cur_r);
        while (cur_l < q.l) remove(cur_l++);
        while (cur_r > q.r) remove(cur_r--);
        ans[q.id] = cur_ans;
    }
    return ans;
}
