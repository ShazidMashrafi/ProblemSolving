struct DSU {
    vector<int> par, sz;
    int comps;

    DSU(int n = 0) : par(n + 1), sz(n + 1, 1), comps(n) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int u) {
        return par[u] == u ? u : par[u] = find(par[u]);
    }

    bool same(int u, int v) {
        return find(u) == find(v);
    }

    bool unite(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        par[v] = u;
        sz[u] += sz[v];
        comps--;
        return true;
    }

    int size(int u) {
        return sz[find(u)];
    }
};