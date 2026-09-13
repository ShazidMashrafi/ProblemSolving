const int N = 1e5 + 10;
vector<int> g[N];
int max_dist, farthest_node;

void dfs_far(int u, int p, int d) {
    if (d > max_dist) {
        max_dist = d;
        farthest_node = u;
    }
    for (int v : g[u]) {
        if (v != p) dfs_far(v, u, d + 1);
    }
}

int get_diameter(int root = 1) {
    max_dist = -1;
    dfs_far(root, 0, 0);
    max_dist = -1;
    dfs_far(farthest_node, 0, 0);
    return max_dist;
}
