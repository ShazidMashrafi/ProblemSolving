const int N = 1e5 + 10;
vector<int> g[N];
bool vis[N];

void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (!vis[v]) dfs(v);
    }
}