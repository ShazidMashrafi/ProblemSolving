vector<vector<int>>adj;
vector<int>color;
bool dfs(int curr, int col) {
    color[curr] = col;
    for(auto i: adj[curr]) {
        if(color[i] == -1) {
            if(!dfs(i, col^1)) { // if false for next vertex
                return false;
            }
        } else {
            if(color[curr] == color[i]) return false;
        }
    }
    return true;
}
void Bipartite_Graph_Coloring() {
    // adj.resize(n+1, vector<int>()); -> in solve
    // color.assign(n+1, -1);-> in solve
    if(dfs(1, 0)) cout<<"Bipartite\n";
    else cout<<"Not Bipartite\n";
}
