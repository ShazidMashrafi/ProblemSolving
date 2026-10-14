struct MSBFS {
    int n, m;
    vector<vector<int>> dist;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    MSBFS(int _n, int _m, auto& src)
        : n(_n), m(_m), dist(n, vector<int>(m, -1)) {
        queue<pair<int, int>> q;
        for (auto [x, y] : src) {
            dist[x][y] = 0;
            q.push({x, y});
        }

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int i = 0; i < 4; ++i) { // change to 8 for 8-dir
                int nx = x + dx[i], ny = y + dy[i];
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
    }
};