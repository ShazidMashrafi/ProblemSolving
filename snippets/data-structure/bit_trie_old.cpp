class Trie {
private:
    struct TrieNode {
        TrieNode* children[2];
        
        TrieNode() {
            for (int i = 0; i < 2; i++)
                children[i] = nullptr;
        }
    };
    
    TrieNode* root;
    static const int MAX_BITS = 31;
    
public:
    Trie() {
        root = new TrieNode();
    }
    
    void insert(int num) {
        TrieNode* node = root;
        for(int i = MAX_BITS; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if(!node->children[bit])
                node->children[bit] = new TrieNode();
            node = node->children[bit];
        }
    }
};