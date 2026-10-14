struct Topo {
    vector<int> order;
    bool dag = true;

    Topo(int n, auto& g) {
        vector<int> in(n + 1, 0);
        for (int u = 1; u <= n; ++u) {
            for (int v : g[u]) in[v]++;
        }

        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (in[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);

            for (int v : g[u]) {
                if (--in[v] == 0) q.push(v);
            }
        }

        if ((int)order.size() < n) dag = false;
    }
};
