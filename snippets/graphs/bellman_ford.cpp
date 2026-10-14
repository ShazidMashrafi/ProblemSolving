struct Edge {
    int u, v;
    ll w;
};

struct Bellman {
    ll INF = 1e18;
    vector<ll> dist;
    bool neg_cycle = false;

    Bellman(int n, int src, auto& edges) : dist(n + 1, INF) {
        dist[src] = 0;
        for (int i = 1; i <= n - 1; ++i) {
            for (auto [u, v, w] : edges) {
                if (dist[u] < INF && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        for (auto [u, v, w] : edges) {
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                neg_cycle = true;
                break;
            }
        }
    }
};