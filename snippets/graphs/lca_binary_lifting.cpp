const int N = 1e5 + 10;
const int LOGN = 20;
vector<int> g[N];
int up[N][LOGN], depth[N];
int n;

void dfs_lca(int u, int p = 0, int d = 0) {
    depth[u] = d;
    up[u][0] = p;
    for (int j = 1; j < LOGN; ++j) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : g[u]) {
        if (v != p) dfs_lca(v, u, d + 1);
    }
}

int get_lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);

    for (int j = LOGN - 1; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v])
            u = up[u][j];
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

int main() {
    // take input of tree.
    dfs_lca(1, 1, 0); // root = 1
}
