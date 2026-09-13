const int N = 1e5 + 10;
vector<int> g[N];
int vis[N]; // 0: unvisited, 1: stack, 2: done

bool dfs_cycle(int u, int p = 0) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue; // remove if directed
        if (vis[v] == 1) return true;
        if (!vis[v] && dfs_cycle(v, u)) return true;
    }
    vis[u] = 2;
    return false;
}

bool has_cycle(int n) {
    fill(vis, vis + n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && dfs_cycle(i, 0)) return true;
    }
    return false;
}