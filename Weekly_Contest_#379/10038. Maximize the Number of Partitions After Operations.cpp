
// Time = O(2 * n * 2^k * k)
// Space = O(2 * n * 2^k * k)

class Solution {
public:
    
    #define ll long long
    unordered_map<ll,int> cache;
    
    int dfs(int i, bool used, ll mask, int uniCnt, string &s, int k)
    {
        if(i == s.size())
            return 1;
        
        int key = i*1000 + used*100 + mask*10 + uniCnt;
        if(cache.count(key))
            return cache[key];
        
        int partitions = 0;
        
        ll cmask = (1ll << (s[i] - 'a'));
        if(mask & cmask)
            partitions = dfs(i+1, used, mask, uniCnt, s, k);
        else
        {
            if(uniCnt + 1 <= k)
                partitions = dfs(i+1, used, (mask | cmask), uniCnt + 1, s, k);
            else partitions = dfs(i+1, used, cmask, 1, s, k) + 1;
        }
        
        if(!used)
        {
            for(int c = 'a'; c <= 'z'; c++)
            {
                if(c == s[i]) continue;
                
                ll cmask2 = (1ll << (c - 'a'));
                if((mask & cmask2))
                    partitions = max(partitions, dfs(i+1, true, mask, uniCnt, s, k));
                else
                {
                    if(uniCnt + 1 <= k)
                        partitions = max(partitions, dfs(i+1, true, (mask | cmask2), uniCnt + 1, s, k));
                    else partitions = max(partitions, dfs(i+1, true, cmask2, 1, s, k) + 1);
                }
            }
        }
        
        return cache[key] = partitions;
    }
    
    int maxPartitionsAfterOperations(string s, int k) 
    {
        if(s.size() == 0) return 0;
        return dfs(0, false, 0ll, 0, s, k);
    }
};
