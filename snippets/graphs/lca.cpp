struct LCA {
    int n, LOGN;
    vector<int> depth;
    vector<vector<int>> up;

    LCA(int _n, int root, auto& g) : n(_n), depth(n + 1, 0) {
        LOGN = __lg(n) + 2;
        up.assign(n + 1, vector<int>(LOGN, 0));

        auto dfs = [&](auto& self, int u, int p, int d) -> void {
            depth[u] = d;
            up[u][0] = p;
            for (int j = 1; j < LOGN; ++j) {
                up[u][j] = up[up[u][j - 1]][j - 1];
            }
            for (int v : g[u]) {
                if (v != p) self(self, v, u, d + 1);
            }
        };
        dfs(dfs, root, 0, 1);
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int j = LOGN - 1; j >= 0; --j) {
            if (depth[u] - (1 << j) >= depth[v]) u = up[u][j];
        }
        if (u == v) return u;
        for (int j = LOGN - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    int get_dist(int u, int v) {
        return depth[u] + depth[v] - 2 * depth[get_lca(u, v)];
    }

    int kth_ancestor(int u, int k) {
        for (int j = 0; j < LOGN; ++j) {
            if (k & (1 << j)) u = up[u][j];
        }
        return u;
    }
};
