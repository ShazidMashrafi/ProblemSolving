const int N = 1e5 + 10;
vector<int> g[N];
int in_degree[N];
int n, m;

// Returns topological order, or empty vector if cycle exists
vector<int> kahn_toposort(int n) {
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) q.push(i);
    }

    vector<int> topo;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);

        for (int v : g[u]) {
            if (--in_degree[v] == 0) q.push(v);
        }
    }

    if ((int)topo.size() < n) return {}; // Cycle detected
    return topo;
}

int main() {
    // take input: g[u].push_back(v); in_degree[v]++;
    vector<int> order = kahn_toposort(n);
}
