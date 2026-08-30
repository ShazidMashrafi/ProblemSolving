const int N = 1005;
int dist[N][N];
int n, m;

int dx[] = {0, 0, 1, -1, 1, 1, -1, -1}; // first 4 for 4-dir
int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

bool valid(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void multi_source_bfs(const vector<pair<int, int>>& sources) {
    memset(dist, -1, sizeof(dist));
    queue<pair<int, int>> q;

    for (auto [x, y] : sources) {
        dist[x][y] = 0;
        q.push({x, y});
    }

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) { // change 4 to 8 for 8-dir
            int nx = x + dx[i], ny = y + dy[i];
            if (valid(nx, ny) && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}