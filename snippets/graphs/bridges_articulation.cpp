struct Bridges {
    int timer = 0;
    vector<int> tin, low;
    vector<bool> cut;
    vector<pair<int, int>> bridges;

    Bridges(int n, auto& g) : tin(n + 1, 0), low(n + 1, 0), cut(n + 1, false) {
        auto dfs = [&](auto& self, int u, int p) -> void {
            tin[u] = low[u] = ++timer;
            int children = 0;

            for (int v : g[u]) {
                if (v == p) continue; // for multigraph: skip edge_id instead of p
                if (tin[v]) {
                    low[u] = min(low[u], tin[v]);
                } else {
                    self(self, v, u);
                    low[u] = min(low[u], low[v]);
                    if (low[v] > tin[u]) bridges.push_back({u, v});
                    if (low[v] >= tin[u] && p != 0) cut[u] = true;
                    children++;
                }
            }
            if (p == 0 && children > 1) cut[u] = true;
        };

        for (int i = 1; i <= n; ++i) {
            if (!tin[i]) dfs(dfs, i, 0);
        }
    }
};
