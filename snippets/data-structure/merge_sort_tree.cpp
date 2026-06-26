struct Nodem
{
    vector<pair<int, int>> pref;
};

struct segTree {    
    int size = 1;
    vector<Nodem> tree;
    segTree(int n) {
        while (size < n) size <<= 1;
        // tree.assign(2 * size, 0LL);
        tree.resize(2 * size);
    }
    Nodem neutral;
    void merge(Nodem &curr, Nodem &left, Nodem &right) { // merge sort tree;
        int l = 0, r = 0, i = 0;
        while(l < size(left.pref) && r < size(right.pref)) {
            if (left.pref[l].first <= right.pref[r].first) {
                int prefed = (curr.pref.empty() ? left.pref[l].first : (curr.pref.back().second + left.pref[l].first));
                curr.pref.pb({left.pref[l].first, prefed});
                l++;
            } else {
                int prefed = (curr.pref.empty() ? right.pref[r].first : (curr.pref.back().second + right.pref[r].first));
                curr.pref.pb({right.pref[r].first, prefed});
                r++;
            }
            i++;
        }
        while(l < size(left.pref)) {
            int prefed = (curr.pref.empty() ? left.pref[l].first : (curr.pref.back().second + left.pref[l].first));
            curr.pref.pb({left.pref[l].first, prefed});
            l++;
        }
        while(r < size(right.pref)) {
            int prefed = (curr.pref.empty() ? right.pref[r].first : (curr.pref.back().second + right.pref[r].first));
            curr.pref.pb({right.pref[r].first, prefed});
            r++;
        }
    }
    void build(vector<int> &v, int curr, int lx, int rx) {
        if (rx - lx == 1) { // 0 - 1, 1 - 2, 2 - 3 ...
            if (lx < size(v)) {
                tree[curr].pref.pb({v[lx], v[lx]});
            }
            return;
        }
        int mid = (lx + rx) / 2;
        build(v, 2 * curr + 1, lx, mid);
        build(v, 2 * curr + 2, mid, rx);
        merge(tree[curr], tree[2 * curr + 1], tree[2 * curr + 2]);
    }
    void build(vector<int> &v) { build(v, 0, 0, size); }
    int get(int x, int l, int r, int curr, int lx, int rx) { // O(logn)
        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) {
            auto it = upper_bound(all(tree[curr].pref), make_pair(x, LLONG_MAX));
            if (it == tree[curr].pref.begin()) return 0;
            return prev(it)->second;
        };
        int mid = (lx + rx) / 2;
        int left = get(x, l, r, 2 * curr + 1, lx, mid);
        int right = get(x, l, r, 2 * curr + 2, mid, rx);
        return left + right;
    }
    int get(int x, int l, int r) { return get(x, l, r, 0, 0, size); }
};