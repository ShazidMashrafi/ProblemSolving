const int N = 1e5 + 10;
vector<int> g[N];
int depth[N], height[N], sub_size[N];
int n;

void dfs_tree(int u, int p = 0) {
    depth[u] = depth[p] + 1;
    height[u] = 0;
    sub_size[u] = 1;

    for (int v : g[u]) {
        if (v == p) continue;
        dfs_tree(v, u);
        height[u] = max(height[u], height[v] + 1);
        sub_size[u] += sub_size[v];
    }
}

int main() {
    // take input of tree.
    dfs_tree(1, 0);
}
