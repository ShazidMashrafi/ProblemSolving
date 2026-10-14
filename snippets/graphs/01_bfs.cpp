struct BFS01 {
    int INF = 1e9 + 10;
    vector<int> dist, par;

    BFS01(int n, int src, auto& g) : dist(n + 1, INF), par(n + 1, -1) {
        deque<int> dq;
        dist[src] = 0;
        dq.push_back(src);
        while (!dq.empty()) {
            int u = dq.front(); dq.pop_front();
            for (auto [v, w] : g[u]) {
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    par[v] = u;
                    if (w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
    }

    vector<int> get_path(int target) {
        if (dist[target] >= INF) return {};
        vector<int> path;
        for (int v = target; v != -1; v = par[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }
};