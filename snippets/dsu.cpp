class DSU
{
    private:
    vector<int> par;
    vector<int> size;
    public:
    DSU(int n)
    {
        par = vector<int>(n);
        iota(par.begin(), par.end(), 0);
        size = vector<int>(n, 1);
    }
    int find(int u)
    {
        if(par[u] != par[par[u]])
            par[u] = find(par[par[u]]);        
        return par[u];
    }
    bool connected(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) 
            return true;
        return false;
    }
    bool join(int u, int v)
    {
        u = find(u);
        v = find(v);
        if(u == v) 
            return false;
        if(size[u] <= size[v])
        {
            size[v] += size[u];
            par[u] = v;
        }
        else
        {
            size[u] += size[v];
            par[v] = u;
        }
        return true;
    }
};
void solve()
{
    int n, m;
    cin >> n >> m;
    DSU dsu(n);
    for(int i = 0; i < n; ++i)
    {
        int v, u; cin >> v >> u;
        dsu.join(v, u);
    }
}
