
// Time Complexity = O(n*n*k)
// Space Complexity = O(505 * 505 * 30)

class Solution {
public:
    
    int dp[505][505][30];
    int dfs(int i, int previ, int k, int n, vector<int> &nums)
    {
        if(k == -1)
            return -1;
        if(i == n)
            return 0;
        if(dp[i][previ][k] != -1)
            return dp[i][previ][k];
        
        int l1 = dfs(i+1, i+1, k - (previ && nums[i] != nums[previ-1]), n, nums) + 1;
        int l2 = dfs(i+1, previ, k, n, nums);
        
        return dp[i][previ][k] = max(l1, l2);
    }
    
    int maximumLength(vector<int>& nums, int k) 
    {
        memset(dp, -1, sizeof(dp));
        int n = nums.size();
        
        int maxLen = 0, cnt = 0;
        
        return dfs(0, 0, k, n, nums);
    }
};
