class Allocator {
public:
    
    vector<int> mem;
    unordered_map<int,unordered_set<int>> mp;
    int n;
    Allocator(int n) 
    {
        this->n = n;
        this->mem.assign(n, 0);
    }
    
    int allocate(int size, int mID) 
    {
        int ans = -1;
        for(int i = 0; i < n; i++)
        {
            int j = i;
            while(j < n && j-i < size && mem[j] == 0) j++;
            if(j-i == size)
            {
                ans = i;
                while(j > i) 
                {
                    mem[--j] = mID;
                    mp[mID].insert(j);
                }
                break;
            }
            i = j;
        }
        
        return ans;
    }
    
    int free(int mID) 
    {
        int ans = mp[mID].size();
        for(int i : mp[mID])
            mem[i] = 0;
        mp[mID].clear();
        
        return ans;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
