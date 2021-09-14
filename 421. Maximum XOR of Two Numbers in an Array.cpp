class Solution {
public:
    
    class trie
    {
        public:
        vector<trie*> oz;
        trie()
        {
            this->oz.assign(2,nullptr);
        }
    };
    trie *t = new trie();
    
    void insert(int x)
    {
        trie *tmp = t;
        for(int i = 31; i >= 0; i--)
        {
            int pol = ((1 << i) & x)? 1 : 0;
            if(!tmp->oz[pol])
                tmp->oz[pol] = new trie();
            tmp = tmp->oz[pol];
        }
    }
    
    int findMaximumXOR(vector<int>& nums) 
    {
        for(int x : nums)
            insert(x);
        
        int ans = 0;
        for(int x : nums)
        {
            trie *tmp = t;
            int currans = 0;
            for(int i = 31; i >= 0; i--)
            {
                int pol = ((1 << i) & x)? 1 : 0;
                if(tmp->oz[pol^1])
                {
                    currans += (1 << i);
                    tmp = tmp->oz[pol^1];
                }
                else tmp = tmp->oz[pol];
            }
            ans = max(ans, currans);
        }
        return ans;
    }
};