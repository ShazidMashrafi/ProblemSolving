struct Bipartite {
    vector<int> color; // 0 or 1, -1: unvisited
    bool ok = true;

    Bipartite(int n, auto& g) : color(n + 1, -1) {
        auto dfs = [&](auto& self, int u, int c) -> bool {
            color[u] = c;
            for (int v : g[u]) {
                if (color[v] == -1) {
                    if (!self(self, v, c ^ 1)) return false;
                } else if (color[v] == color[u]) {
                    return false;
                }
            }
            return true;
        };

        for (int i = 1; i <= n; ++i) {
            if (color[i] == -1 && !dfs(dfs, i, 0)) {
                ok = false;
                break;
            }
        }
    }
};
