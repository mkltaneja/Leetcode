// APPROACH 1 

class Solution {
public:
    vector<int> circularGameLosers(int n, int k) 
    {
        unordered_set<int> vis;
        long long x = 1, i = 1;
        while(!vis.count(x))
        {
            vis.insert(x);
            x = x + (i++)*k;
            if(x > n) x %= n;
            if(x == 0) x = n;
        }
        
        vector<int> ans;
        for(int j = 1; j <= n; j++)
            if(!vis.count(j))
                ans.push_back(j);
        
        return ans;
    }
};
