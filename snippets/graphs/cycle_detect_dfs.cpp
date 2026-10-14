struct Cycle {
    vector<int> vis; // 0: unvisited, 1: on stack, 2: done
    vector<int> cycle;
    bool has_cyc = false;

    Cycle(int n, auto& g) : vis(n + 1, 0) {
        vector<int> par(n + 1, -1);
        auto dfs = [&](auto& self, int u) -> bool {
            vis[u] = 1;
            for (int v : g[u]) {
                if (vis[v] == 1) {
                    cycle.push_back(v);
                    for (int cur = u; cur != v; cur = par[cur]) cycle.push_back(cur);
                    cycle.push_back(v);
                    reverse(cycle.begin(), cycle.end());
                    return true;
                }
                if (!vis[v]) {
                    par[v] = u;
                    if (self(self, v)) return true;
                }
            }
            vis[u] = 2;
            return false;
        };

        for (int i = 1; i <= n; ++i) {
            if (!vis[i] && dfs(dfs, i)) {
                has_cyc = true;
                break;
            }
        }
    }
};