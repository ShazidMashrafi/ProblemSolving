struct SCC {
    int n, timer = 0, scc_cnt = 0;
    vector<int> tin, low, comp, st;
    vector<bool> in_stack;
    vector<vector<int>> sccs;

    SCC(int _n, auto& g)
        : n(_n), tin(n + 1, 0), low(n + 1, 0), comp(n + 1, 0), in_stack(n + 1, false) {
        auto dfs = [&](auto& self, int u) -> void {
            tin[u] = low[u] = ++timer;
            st.push_back(u);
            in_stack[u] = true;

            for (int v : g[u]) {
                if (!tin[v]) {
                    self(self, v);
                    low[u] = min(low[u], low[v]);
                } else if (in_stack[v]) {
                    low[u] = min(low[u], tin[v]);
                }
            }

            if (low[u] == tin[u]) {
                sccs.push_back({});
                scc_cnt++;
                while (true) {
                    int v = st.back();
                    st.pop_back();
                    in_stack[v] = false;
                    comp[v] = scc_cnt;
                    sccs.back().push_back(v);
                    if (u == v) break;
                }
            }
        };

        for (int i = 1; i <= n; ++i) {
            if (!tin[i]) dfs(dfs, i);
        }
    }
};
