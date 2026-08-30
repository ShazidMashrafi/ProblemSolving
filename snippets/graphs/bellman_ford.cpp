const int N = 1005;
const long long INF = 1e18;

struct Edge {
    int u, v;
    long long w;
};

long long dist[N];

// Returns true if a negative cycle is reachable from src
bool bellman_ford(int src, int n, const vector<Edge>& edges) {
    fill(dist, dist + n + 1, INF);
    dist[src] = 0;

    for (int i = 1; i <= n - 1; ++i) {
        for (const auto& [u, v, w] : edges) {
            if (dist[u] < INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (const auto& [u, v, w] : edges) {
        if (dist[u] < INF && dist[u] + w < dist[v]) {
            return true;
        }
    }
    return false;
}