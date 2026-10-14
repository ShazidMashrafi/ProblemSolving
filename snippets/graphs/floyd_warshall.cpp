struct Floyd {
    ll INF = 1e18;
    int n;
    vector<vector<ll>> dist;
    bool neg_cycle = false;

    Floyd(int _n, auto& adj_mat) : n(_n), dist(adj_mat) {
        for (int k = 1; k <= n; ++k) {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (dist[i][k] < INF && dist[k][j] < INF)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        for (int i = 1; i <= n; ++i) {
            if (dist[i][i] < 0) neg_cycle = true;
        }
    }
};