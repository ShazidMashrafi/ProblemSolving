// requires DSU (data-structures/dsu.cpp)
struct Edge {
    int u, v;
    ll w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

pair<ll, vector<Edge>> kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    ll total_weight = 0;
    vector<Edge> mst_edges;

    for (const auto& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            total_weight += edge.w;
            mst_edges.push_back(edge);
        }
    }
    return {total_weight, mst_edges};
}
