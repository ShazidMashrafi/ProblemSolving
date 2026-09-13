struct Node {
    int sum, inc;
};
struct segTree {
    int size = 1;
    vector<Node> tree;
    Node neutral = {0, 0};
    segTree(int n) {
        while (size < n) size <<= 1;
        tree.assign(2 * size, neutral);
    }
    void push(int curr, int lx, int rx) {
        if (tree[curr].inc == 0) return;
        int mid = (lx + rx) / 2;
        tree[2 * curr + 1].inc += tree[curr].inc;
        tree[2 * curr + 1].sum += tree[curr].inc * (mid - lx);
        tree[2 * curr + 2].inc += tree[curr].inc;
        tree[2 * curr + 2].sum += tree[curr].inc * (rx - mid);
        tree[curr].inc = 0;
    }
    void set(int inc, int l, int r, int curr, int lx, int rx) { // O(logn)
        if (rx <= l || lx >= r) return;
        if (lx >= l && rx <= r) {
            tree[curr].inc += inc;
            tree[curr].sum += inc * (rx - lx);
            return;
        }
        push(curr, lx, rx);
        int mid = (lx + rx) / 2;
        set(inc, l, r, 2 * curr + 1, lx, mid);
        set(inc, l, r, 2 * curr + 2, mid, rx);
        tree[curr].sum = tree[2 * curr + 1].sum + tree[2 * curr + 2].sum;
    }
    void set(int inc, int l, int r) {
        set(inc, l, r, 0, 0, size);
    }
    int get(int l, int r, int curr, int lx, int rx) { // O(logn)
        if (rx <= l || lx >= r) return 0; // neutral???
        if (lx >= l && rx <= r) {
            return tree[curr].sum;
        }
        push(curr, lx, rx);
        int mid = (lx + rx) / 2;
        int s1 = get(l, r, 2 * curr + 1, lx, mid);
        int s2 = get(l, r, 2 * curr + 2, mid, rx);
        // do we merge?
        return s1 + s2;
    }   
    int get(int l, int r) {
        return get(l, r, 0, 0, size);
    }
};
