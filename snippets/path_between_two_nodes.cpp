vector<vector<int>>adj;
vector<int>parent;
vector<bool>vis;
int x, y;
void BFS(int initial) {
    queue<int>q;
    q.push(initial);
    while(!q.empty()) {
        int curr = q.front();
        vis[curr] = true;
        if(curr == y) return;
        for(auto i: adj[curr]) {
            if(!vis[i]) {
                q.push(i);
                parent[i] = curr;
            }
        }
        q.pop();
    }
}
void backtrack(vector<int>&v, int last) {
    while(last != -1) {
        v.pb(last);
        last = parent[last];
    }
    reverse(v.begin(), v.end());
}
void Path_Between_Two_Nodes(int x, int y) {
    // adj.resize(n+1, vector<int>()); -> in solve()
    BFS(x);
    vector<int>ans;
    backtrack(ans, y);
    for(int i = 0; i < size(ans); i++) cout<<ans[i]<<" ";
    cout<<endl;
} 
