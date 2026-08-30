const int N = 1e5 + 10;
vector<int> g[N];
int tin[N], low[N], timer;
bool in_stack[N];
vector<int> st;
vector<vector<int>> sccs;
int comp[N], scc_cnt;
int n, m;

void tarjan_dfs(int u) {
    tin[u] = low[u] = ++timer;
    st.push_back(u);
    in_stack[u] = true;

    for (int v : g[u]) {
        if (!tin[v]) {
            tarjan_dfs(v);
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
}

int main() {
    // take input of graph.
    for (int i = 1; i <= n; ++i) {
        if (!tin[i]) tarjan_dfs(i);
    }
}
