
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
