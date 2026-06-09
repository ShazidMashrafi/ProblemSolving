void dfs(int v, int parent)
{
    for(int child : g[v])
    {
        if(child==parent)
            continue;
        depth[child]=depth[v]+1;
        dfs(child,v);
    }
}
int main()
{
    // Take input
    dfs(1,-1);
    int mx_depth=-1,mx_depth_node;
    for(int i=1; i<=n; ++i)
    {
        if(mx_depth<depth[i])
        {
            mx_depth=depth[i];
            mx_depth_node=i;
        }
        depth[i]=0;
    }
    dfs(mx_depth_node,-1);
    mx_depth=-1;
    for(int i=1; i<=n; ++i)
    {
        if(mx_depth<depth[i])
        {
            mx_depth=depth[i];
        }
    }
    cout<<mx_depth<<endl;
}
