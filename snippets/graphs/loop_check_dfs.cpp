const int N = 1e5 + 10;
vector<int> g[N];
int vis[N]; // 0: unvisited, 1: in stack, 2: done
int n, m;

bool dfs(int u, int p = 0) {
    vis[u] = 1;
    for (int v : g[u]) {
        if (v == p) continue; // remove for directed
        if (vis[v] == 1) return true;
        if (!vis[v] && dfs(v, u)) return true;
    }
    vis[u] = 2;
    return false;
}

int main() {
    // take input of graph.

    bool loop = false;
    for (int i = 1; i <= n; ++i) {
        if (!vis[i] && dfs(i, 0)) {
            loop = true;
            break;
        }
    }
    cout << (loop ? "YES" : "NO") << "\n";
}