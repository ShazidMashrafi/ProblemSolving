const int N = 505;
const long long INF = 1e18;
long long dist[N][N];

void init_floyd(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j)
            dist[i][j] = (i == j ? 0 : INF);
    }
}

void floyd_warshall(int n) {
    for (int k = 1; k <= n; ++k) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}

// Returns true if negative cycle exists
bool has_negative_cycle(int n) {
    for (int i = 1; i <= n; ++i)
        if (dist[i][i] < 0) return true;
    return false;
}