#include<bits/stdc++.h>
using namespace std;
#define ll 	long long
const int N=1e5+10;
vector<int>g[N];
bool vis[N];
bool dfs(int vertex,int parent)
{
    vis[vertex]=1;
    bool loop = false;
    for(int child : g[vertex])
    {
        if(vis[child] && child == parent) continue;
        if(vis[child])   return true;
        loop |= dfs(child,vertex);
    }
    return loop;
}
int main()
{
    int n,e; cin>>n>>e;
    for(int i=0; i<e; ++i)
    {
        int x,y;
        cin>>x>>y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    bool loop = false;
    for(int i=1; i<=n; ++i)
    {
        if(vis[i])  continue;
        if(dfs(i,0))
        {
            loop = true;
            break;
        }
    }
    cout<<loop<<endl;
}
