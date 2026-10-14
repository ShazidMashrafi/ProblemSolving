struct TreeDia {
    int dia = 0, u = 1, v = 1;

    TreeDia(int n, auto& g) {
        auto bfs = [&](int src) {
            vector<int> dist(n + 1, -1);
            queue<int> q;
            dist[src] = 0;
            q.push(src);
            int far = src;

            while (!q.empty()) {
                int x = q.front();
                q.pop();
                if (dist[x] > dist[far]) far = x;

                for (int y : g[x]) {
                    if (dist[y] == -1) {
                        dist[y] = dist[x] + 1;
                        q.push(y);
                    }
                }
            }
            return pair{far, dist[far]};
        };

        u = bfs(1).first;
        auto res = bfs(u);
        v = res.first;
        dia = res.second;
    }
};
