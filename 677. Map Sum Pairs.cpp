class MapSum {
public:
    /** Initialize your data structure here. */
    class trie
    {
        public:
        vector<trie*> t;
        int csum;
        int wordVal;
        trie()
        {
            this->t.assign(26,nullptr);
            this->csum = 0;
            this->wordVal = 0;
        }
    };
    trie* root = nullptr;
    
    MapSum() 
    {
        this->root = new trie();
    }
    
    void insert(string key, int val) 
    {
        trie* curr = root;
        for(char c : key)
        {
            if(!curr->t[c-'a'])
                curr->t[c-'a'] = new trie();
            curr = curr->t[c-'a'];
        }
        
        int x = curr->wordVal;
        curr = root;
        for(char c : key)
        {
            if(!curr->t[c-'a'])
                curr->t[c-'a'] = new trie();
            curr = curr->t[c-'a'];
            curr->csum += val - x;
        }
        curr->wordVal = val;
    }
    
    int sum(string prefix) 
    {
        trie* curr = root;
        for(char c : prefix)
        {
            if(!curr->t[c-'a'])
                return 0;
            curr = curr->t[c-'a'];
        }
        return curr->csum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */