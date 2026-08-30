const int N = 1e5 + 10;
vector<int> g[N];
int max_dist, farthest_node;
int n;

void dfs_far(int u, int p, int d) {
    if (d > max_dist) {
        max_dist = d;
        farthest_node = u;
    }
    for (int v : g[u]) {
        if (v != p) dfs_far(v, u, d + 1);
    }
}

int main() {
    // take input of tree.
    max_dist = -1;
    dfs_far(1, 0, 0);

    max_dist = -1;
    dfs_far(farthest_node, 0, 0);

    int diameter = max_dist;
}
