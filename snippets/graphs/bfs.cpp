const int N = 1e5 + 10;
vector<int> g[N];
int dist[N], parent[N];

void bfs(int src, int n) {
    fill(dist, dist + n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    parent[src] = -1;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }
}

vector<int> get_path(int target) {
    if (dist[target] == -1) return {};
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}