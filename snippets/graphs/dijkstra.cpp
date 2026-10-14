struct Dijkstra {
    ll INF = 1e18;
    vector<ll> dist;
    vector<int> par;

    Dijkstra(int n, int src, auto& g) : dist(n + 1, INF), par(n + 1, -1) {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;

            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    par[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    vector<int> get_path(int target) {
        if (dist[target] == INF) return {};
        vector<int> path;
        for (int v = target; v != -1; v = par[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }
};