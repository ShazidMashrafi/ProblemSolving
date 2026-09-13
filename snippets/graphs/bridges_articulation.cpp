const int N = 1e5 + 10;
vector<int> g[N];
int tin[N], low[N], timer;
bool is_cut[N];
vector<pair<int, int>> bridges;

void dfs_tarjan(int u, int p = 0) {
    tin[u] = low[u] = ++timer;
    int children = 0;

    for (int v : g[u]) {
        if (v == p) continue; // multi-edges: skip by edge_id
        if (tin[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs_tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) bridges.push_back({u, v});
            if (low[v] >= tin[u] && p != 0) is_cut[u] = true;
            children++;
        }
    }
    if (p == 0 && children > 1) is_cut[u] = true;
}

void find_bridges_and_cuts(int n) {
    timer = 0;
    bridges.clear();
    fill(tin, tin + n + 1, 0);
    fill(low, low + n + 1, 0);
    fill(is_cut, is_cut + n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (!tin[i]) dfs_tarjan(i);
    }
}
