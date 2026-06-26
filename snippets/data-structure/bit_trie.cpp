const int MAXBIT = 30;
class BitTrie {
public:
    vector<array<int, 2>> children;
    vector<int> data;
    
    int createNode() {
        children.pb({-1, -1});
        data.pb(0);
        return sz(children) - 1;
    }
    
    BitTrie() {
        createNode();
    }

    void insert(int num) {
        int node = 0;
        for(int i = MAXBIT - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(children[node][bit] == -1) 
                children[node][bit] = createNode();
            node = children[node][bit];
        }
        data[node]++;
    }

    bool search(int num) {
        int node = 0;
        for(int i = MAXBIT - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(children[node][bit] == -1) return false;
            node = children[node][bit];
        }
        return data[node] > 0;
    }
};