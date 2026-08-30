const int N = 1e5 + 10;
vector<int> g[N];
int color[N]; // -1: uncolored
int n, m;

bool dfs(int u, int c = 0) {
    color[u] = c;
    for (int v : g[u]) {
        if (color[v] == -1) {
            if (!dfs(v, c ^ 1)) return false;
        } else if (color[v] == color[u]) {
            return false;
        }
    }
    return true;
}

int main() {
    // take input of graph.
    memset(color, -1, sizeof(color));

    bool ok = true;
    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1 && !dfs(i, 0)) {
            ok = false;
            break;
        }
    }
    cout << (ok ? "YES" : "NO") << "\n";
}
