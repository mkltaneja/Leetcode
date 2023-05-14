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

// APPROACH 2 (Simplified)

class Solution {
public:
    vector<int> circularGameLosers(int n, int k) 
    {
        vector<int> vis(n);
        for(int i = 1, x = 0; i <= n; i++)
        {
            if(vis[x]) break;
            vis[x] = 1;
            x = (x + i*k) % n;
        }
        
        vector<int> ans;
        for(int i = 0; i < n; i++)
            if(!vis[i])
                ans.push_back(i+1);
        
        return ans;
    }
};
