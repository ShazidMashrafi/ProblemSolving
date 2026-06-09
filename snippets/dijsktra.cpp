const int N = 1e5+10;
const int INF = 1e9+10;
vector<pair<int,int>> g[N];
void dijkstra(int v, int n)
{
    vector<int>vis(N,0);
    vector<int>dis(N,INF);
    set<pair<int,int>>st;
    st.insert({0,v});
    dis[v]=0;
    while(st.size())
    {
        auto node = *st.begin();
        int v =  node.second;
        int d = node.first;
        st.erase(st.begin());
        if(vis[v])  
            continue;
        vis[v] = 1;
        for(auto child : g[v])
        {
            int child_v =  child.first;
            int wt =  child.second;
            if(d + wt < dis[child_v])
            {
                dis[child_v] = d + wt;
                st.insert({dis[child_v],child_v});
            }
        }
    }
}
int main()
{
    int n,m;
    cin>>n>>m;
    for(int i=0; i<m; ++i)
    {
        int x,y,wt;
        cin>>x>>y>>wt;
        g[x].push_back({y,wt});
    }
    int v;
    cin>>v;
    dijkstra(v,n);
}
