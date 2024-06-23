
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    ll dp[100005][2];
    
    ll dfs(int i, ll pol, int n, vector<int>& nums)
    {
        if(i == n)
            return 0;
        if(dp[i][pol == -1? 0 : 1] != LLONG_MIN)
            return dp[i][pol == -1? 0 : 1];
        
        ll x = dfs(i+1, pol*(-1), n, nums) + (nums[i] * pol);
        ll y = dfs(i+1, -1, n, nums) + (nums[i] * 1);
        
        return dp[i][pol == -1? 0 : 1] = max(x, y);
    }
    
    long long maximumTotalCost(vector<int>& nums)
    {
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            dp[i][0] = LLONG_MIN;
            dp[i][1] = LLONG_MIN;
        }

        ll ans = 0;
        return dfs(0, 1, n, nums);
    }
};
