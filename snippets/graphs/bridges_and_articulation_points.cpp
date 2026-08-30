const int N = 1e5 + 10;
vector<int> g[N];
int tin[N], low[N], timer;
bool is_cut_vertex[N];
vector<pair<int, int>> bridges;
int n, m;

void dfs_tarjan(int u, int p = 0) {
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : g[u]) {
        if (v == p) continue;
        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                bridges.push_back({u, v});
            }
            if (low[v] >= tin[u] && p != 0) {
                is_cut_vertex[u] = true;
            }
            children++;
        }
    }
    if (p == 0 && children > 1) {
        is_cut_vertex[u] = true;
    }
}

int main() {
    // take input of graph.
    for (int i = 1; i <= n; ++i) {
        if (!tin[i]) dfs_tarjan(i);
    }
}
