const int N = 1e5 + 10;
vector<int> g[N];
int color[N]; // -1: unvisited, 0/1: color

bool dfs_bipartite(int u, int c = 0) {
    color[u] = c;
    for (int v : g[u]) {
        if (color[v] == -1) {
            if (!dfs_bipartite(v, c ^ 1)) return false;
        } else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

bool is_bipartite(int n) {
    fill(color, color + n + 1, -1);
    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1 && !dfs_bipartite(i, 0)) return false;
    }
    return true;
}
