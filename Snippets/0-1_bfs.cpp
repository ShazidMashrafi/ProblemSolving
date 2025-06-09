const int N = 1e5+10;
const int INF = 1e9+10;
vector<pair<int,int>>g[N];
vector<int>level(N,INF);
int n,m;
int bfs()
{
    deque<int>q;
    q.push_back(1);
    level[1]=0;
    while(!q.empty())
    {
        int vertex = q.front();
        q.pop_front();

        for(auto child : g[vertex])
        {
            int v=child.first;
            int wt=child.second;
            if(level[vertex]+wt<level[v])
            {
                level[v]=level[vertex]+wt;
                if(wt==1)
                    q.push_back(v);
                else
                    q.push_front(v);
            }
        }
    }
    if(level[n]==INF) return -1;
    return level[n];
}
int main()
{
    cin>>n>>m;
    for(int i=0; i<m; ++i)
    {
        int x,y;
        cin>>x>>y;
        if(x==y)    
            continue;
        g[x].push_back({y,0}); 
        g[y].push_back({x,1}); 
    } 
    cout<<bfs()<<endl;
}
