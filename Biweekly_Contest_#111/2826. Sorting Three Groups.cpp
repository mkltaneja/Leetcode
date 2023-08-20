class Solution {
public:
    
    int dfs(int i, int p, int n, vector<int> &nums, vector<vector<int>> &dp)
    {
        if(i == n)
            return 0;
        if(dp[i][p] != -1)
            return dp[i][p];
        
        int cnt = INT_MAX;
        for(int x = p; x <= 3; x++)
            cnt = min(cnt, dfs(i+1, x, n, nums, dp) + (x != nums[i]));
        
        return dp[i][p] = cnt;
    }
    
    int minimumOperations(vector<int>& nums) 
    {
        int mn = 0;
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return dfs(0, 1, n, nums, dp);
    }
};
