struct BFS {
    vector<int> dist, par;

    BFS(int n, int src, auto& g) : dist(n + 1, -1), par(n + 1, -1) {
        queue<int> q;
        dist[src] = 0;
        q.push(src);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) {
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    par[v] = u;
                    q.push(v);
                }
            }
        }
    }

    vector<int> get_path(int target) {
        if (dist[target] == -1) return {};
        vector<int> path;
        for (int v = target; v != -1; v = par[v]) path.push_back(v);
        reverse(path.begin(), path.end());
        return path;
    }
};