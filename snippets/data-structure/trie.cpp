class Trie {
public:
    vector<array<int, 26>> children;
    vector<int> endCount;
    
    int createNode() {
        children.pb({});
        fill(all(children.back()), -1);
        endCount.pb(0);
        return sz(children) - 1;
    }
    
    Trie() {
        createNode();
    }

    void insert(string &word) {
        int node = 0;
        for(char ch : word) {
            int idx = ch - 'a';
            if(children[node][idx] == -1)
                children[node][idx] = createNode();
            node = children[node][idx];
        }
        endCount[node]++;
    }

    bool search(string &word) {
        int node = 0;
        for(char ch : word) {
            int idx = ch - 'a';
            if(children[node][idx] == -1) return false;
            node = children[node][idx];
        }
        return endCount[node] > 0;
    }
};