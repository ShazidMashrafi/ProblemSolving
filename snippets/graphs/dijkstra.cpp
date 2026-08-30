const int N = 1e5 + 10;
const long long INF = 1e18;
vector<pair<int, int>> g[N]; // {neighbor, weight}
long long dist[N];
int parent[N];

void dijkstra(int src, int n) {
    fill(dist, dist + n + 1, INF);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    dist[src] = 0;
    parent[src] = -1;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;

        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
}