class WordDictionary {
public:
    /** Initialize your data structure here. */
    
    vector<WordDictionary*> tree;
    bool wordEnd;
    WordDictionary() 
    {
        this->tree.assign(26,nullptr);
        this->wordEnd = false;
    }
    
    void addWord(string word) 
    {
        WordDictionary* curr = this;
        for(char c : word)
        {
            if(!curr->tree[c-'a'])
                curr->tree[c-'a'] = new WordDictionary();
            curr = curr->tree[c-'a'];
        }
        curr->wordEnd = true;
    }
    
    bool dfs(int i, string &s, WordDictionary* curr)
    {
        for(int idx = i; idx < s.size(); idx++)
        {
            if(s[i] == '.')
            {
                for(int j = 0; j < 26; j++)
                    if(curr->tree[j] && dfs(i+1, s, curr->tree[j]))
                        return true;
                return false;
            }
            else 
            {
                if(curr->tree[s[i]-'a'])
                   return dfs(i+1, s, curr->tree[s[i]-'a']);
                else return false;
            }
        }
        return curr->wordEnd;
    }
    
    bool search(string word) 
    {
        return dfs(0, word, this);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */