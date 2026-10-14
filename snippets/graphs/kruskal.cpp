// requires DSU
struct Edge {
    int u, v;
    ll w;
    bool operator<(Edge o) const { return w < o.w; }
};

struct Kruskal {
    ll cost = 0;
    vector<Edge> mst;

    Kruskal(int n, auto& edges) {
        sort(edges.begin(), edges.end());
        DSU dsu(n);
        for (auto& e : edges) {
            if (dsu.unite(e.u, e.v)) {
                cost += e.w;
                mst.push_back(e);
            }
        }
    }
};
