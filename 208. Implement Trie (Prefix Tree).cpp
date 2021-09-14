class Trie {
public:
    
    class node
    {
        public:
        vector<node*> tree;
        bool wordEnd;
        node()
        {
            this->tree.assign(26, nullptr);
            this->wordEnd = false;
        }
    };
    
    /** Initialize your data structure here. */
    
    node* root;
    Trie() 
    {
        this->root = new node();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) 
    {
        node* tmp = root;
        for(char c : word)
        {
            if(!tmp->tree[c-'a'])
                tmp->tree[c-'a'] = new node();
            tmp = tmp->tree[c-'a'];
        }
        tmp->wordEnd = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) 
    {
        node* tmp = root;
        for(char c : word)
        {
            if(!tmp->tree[c-'a']) return false;
            tmp = tmp->tree[c-'a'];
        }
        return tmp->wordEnd;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix)
    {
        node* tmp = root;
        for(char c : prefix)
        {
            if(!tmp->tree[c-'a']) return false;
            tmp = tmp->tree[c-'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */