// lambda DFS
auto dfs = [&](auto& self, int u, int p) -> void {
    for (int v : g[u]) {
        if (v == p) continue;
        self(self, v, u);
    }
};
dfs(dfs, 1, 0);