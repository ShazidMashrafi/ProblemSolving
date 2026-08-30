const int N = 1e5 + 10;
const int INF = 1e9 + 10;
vector<pair<int, int>> g[N]; // {neighbor, weight}
int dist[N];

void bfs01(int src, int n) {
    fill(dist, dist + n + 1, INF);
    deque<int> dq;
    dist[src] = 0;
    dq.push_back(src);

    while (!dq.empty()) {
        int u = dq.front();
        dq.pop_front();

        for (auto [v, w] : g[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (w == 0) dq.push_front(v);
                else dq.push_back(v);
            }
        }
    }
}