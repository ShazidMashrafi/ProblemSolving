struct DSU {
    vector<int> par, siz;
    int comps;

    DSU(int n) {
        par.resize(n + 1);
        iota(par.begin(), par.end(), 0);
        siz.assign(n + 1, 1);
        comps = n;
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
        if (siz[u] < siz[v]) swap(u, v);
        par[v] = u;
        siz[u] += siz[v];
        comps--;
        return true;
    }

    int size(int u) {
        return siz[find(u)];
    }
};