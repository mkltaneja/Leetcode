
// APPROACH 1 (DFS with String path DP)=================================================

// Time Complexity = O(logk * logk)
// Space Complexity = O(logk * logk)

class Solution {
public:
    
    unordered_map<string, int> dp;
    
    int dfs(int i, int p, int j, int k)
    {
        if(i == k || i == k+1)
            return 1;
        if(i > k+1 || i < 0)
            return 0;
        string curr = to_string(i) + to_string(p) + to_string(j);
        if(dp.count(curr))
            return dp[curr];
        
        int ways = dfs(i + (1 << j), 0, j+1, k);
        if(p == 0)
            ways += dfs(i - 1, 1, j, k);
        
        return dp[curr] = ways;
    }
    
    int waysToReachStair(int k) 
    {
        if(k == 0 || k == 1)
            return (1 << (k+1));
        if(k == 2)
            return 4;
        
        int ans = dfs(1, 0, 0, k);
        return ans;
    }
};

// APPROACH 2 (BFS + DP)===========================================================================================

// Time Complexity = O(30 * logk)
// Space Complexity = O(logk)

class Solution {
public:
    
    #define ll long long
    
    int waysToReachStair(int k) 
    {
        unordered_map<ll,int> dp;
        int ans = (k <= 1);
        dp[1] = 1;
        
        for(int jump = 0; jump <= 30; jump++)
        {
            unordered_map<ll,int> dp2;
            for(auto p : dp)
            {
                ll x = p.first;
                int currAns = p.second;
                dp2[x + (1ll << jump)] += currAns;
                dp2[(x - 1) + (1ll << jump)] += currAns;
            }
            swap(dp, dp2);
            ans += (dp.count(k)? dp[k] : 0) + (dp.count(k+1)? dp[k+1] : 0);
        }
        
        return ans;
    }
};
