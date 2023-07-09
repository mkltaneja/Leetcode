
// APPROACH 1 (DFS) --> Time = O(n), Space O(n)

class Solution {
public:
    
    int dfs(int i, int n, vector<vector<int>> &gp, vector<int> &dp)
    {
        if(i == n-1) return 0;
        if(dp[i] != -1) return dp[i];
        
        int ans = INT_MIN;
        for(int j : gp[i])
            ans = max(ans, dfs(j, n, gp, dp) + 1);
        return dp[i] = ans;
    }
    
    int maximumJumps(vector<int>& nums, int target) 
    {
        int n = nums.size();
        vector<vector<int>> gp(n);
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                if(abs(nums[j] - nums[i]) > target) continue;
                gp[i].push_back(j);
            }
        }
        vector<int> dp(n, -1);
        int ans = dfs(0, n, gp, dp);
        return (ans < 0 || ans > n)? -1 : ans;
    }
};

// APPROACH 2 (Tabulation) --> Time = O(n), Space = O(n) [OPTIMIZED]

class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) 
    {
        int n = nums.size();
        vector<int> dp(n, -1);
        dp[0] = 0;
        
        for(int i = 0; i < n; i++)
            for(int j = 0; j < i; j++)
                if(abs(nums[i] - nums[j]) <= target && dp[j] != -1)
                    dp[i] = max(dp[i], dp[j] + 1);
        
        return dp[n-1];
    }
};
