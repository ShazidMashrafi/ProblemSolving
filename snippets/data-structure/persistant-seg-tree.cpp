struct Node { // segment tree with pointers
    int sum;
    Node *l, *r;
    Node (int _sum, Node *_l, Node *_r) {
        sum = _sum;
        l = _l;
        r = _r;
    }
};

struct segTree { //persistent segment tree
    int size = 1;
    vector<Node*> roots;
    segTree(int n) {
        while (size < n) size <<= 1;
        Node *root = new Node(0, nullptr, nullptr);
        roots.pb(root);
    }
    void build(vector<int> &v, Node *curr, int lx, int rx) {
        if (rx - lx == 1) { // 0 - 1, 1 - 2, 2 - 3 ...
            if (lx < size(v)) {
                curr->sum = v[lx];
            }
            curr->l = nullptr;
            curr->r = nullptr;
            return;
        }
        curr->l = new Node(0, nullptr, nullptr);
        curr->r = new Node(0, nullptr, nullptr);
        int mid = (lx + rx) / 2;
        build(v, curr->l, lx, mid);
        build(v, curr->r, mid, rx);
        curr->sum = curr->l->sum + curr->r->sum;
        debug(curr->sum)
    }
    void build(vector<int> &v, int root) { build(v, roots[root], 0, size); }
    void build(int root) { 
        roots.pb(new Node(roots[root]->sum, roots[root]->l, roots[root]->r));
    }
    void set(int indx, int val, Node *curr, int lx, int rx) { // O(logn)
        if (rx - lx == 1) { // range is l ... (r - 1)
            curr->sum = val;
            return;
        }
        int mid = (lx + rx) / 2;
        if (indx < mid) {
            curr->l = new Node(curr->l->sum, curr->l->l, curr->l->r);
            set(indx, val, curr->l, lx, mid);
        } else {
            curr->r = new Node(curr->r->sum, curr->r->l, curr->r->r);
            set(indx, val, curr->r, mid, rx);
        }
        curr->sum = curr->l->sum + curr->r->sum;
        debug(curr->sum)
    }
    void set(int indx, int val, int root) { set(indx, val, roots[root], 0, size); }
    int sum(int l, int r, Node *curr, int lx, int rx) { // O(logn)
        if (rx <= l || lx >= r) return 0;
        if (lx >= l && rx <= r) return curr->sum;
        int mid = (lx + rx) / 2;
        int left = sum(l, r, curr->l, lx, mid);
        int right = sum(l, r, curr->r, mid, rx);
        return left + right;
    }
    int sum(int l, int r, int root) { return sum(l, r, roots[root], 0, size); }
};