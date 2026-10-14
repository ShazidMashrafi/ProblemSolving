struct Tree {
    vector<int> dep, h, sz, par;

    Tree(int n, int root, auto& g)
        : dep(n + 1, 0), h(n + 1, 0), sz(n + 1, 1), par(n + 1, 0) {
        auto dfs = [&](auto& self, int u, int p) -> void {
            par[u] = p;
            dep[u] = dep[p] + 1;
            for (int v : g[u]) {
                if (v == p) continue;
                self(self, v, u);
                h[u] = max(h[u], h[v] + 1);
                sz[u] += sz[v];
            }
        };
        dfs(dfs, root, 0);
    }
};
