const int N = 1e3+10;
const int MAX = 1e9+10;

int val[N][N];
int vis[N][N];
int level[N][N];
int n,m;

vector<pair<int,int>>moves = {
    {0,1}, {0,-1}, {1,0}, {-1,0},
    {1,1}, {1,-1}, {-1,1}, {-1,-1}
};

bool valid(int i, int j)
{
    return i>=0 && j>=0 && i<n && j<m;
}

int bfs()
{   
    int mx=0;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
            mx=max(mx,val[i][j]);
    }
    queue<pair<int,int>> q;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            if(mx==val[i][j])
            {
                q.push({i,j});
                level[i][j]=0;
                vis[i][j]=1;
            }
        }
    }
    int ans = 0;
    while(!q.empty())
    {
        auto v =  q.front();
        int vx = v.first;
        int vy = v.second;
        q.pop();
        for(auto move:moves)
        {
            int x = move.first + vx;
            int y = move.second + vy;
            if(valid(x,y) && !vis[x][y])
            {
                q.push({x,y});
                level[x][y]=level[vx][vy]+1;
                vis[x][y]=1;
                ans = max(ans,level[x][y]);
            }
        }
    }
    return ans;
}

void reset()
{
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {
            vis[i][j] = 0;
            level[i][j] = MAX;
        }
    }
}

void solve()
{
    cin>>n>>m;
    reset();
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<m; ++j)
        {    
            cin >> val[i][j];
        }
    }
    cout<<bfs()<<endl;
}

int main()
{
    int TC;
    cin >> TC;
    while (TC--) 
    {
        cin>>n>>m;
        reset();
        for(int i=0; i<n; ++i)
        {
            for(int j=0; j<m; ++j)
            {    
                cin >> val[i][j];
            }
        }
        cout<<bfs()<<endl;
    }
}
