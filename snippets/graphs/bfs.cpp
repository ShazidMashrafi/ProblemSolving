const int N = 1e5 + 10;
vector<int> g[N];
int dist[N], parent[N];

void bfs(int src) {
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[src] = 0;
    parent[src] = 0;
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