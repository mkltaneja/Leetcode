
// APPROACH 1 (Giving every choice and choosing Maximum)

// Time Complexity = O(n*k*n)
// Space Complexity = O(n*k)

class Solution {
public:
    
    #define ll long long
    
    ll dfs(int i, int turn, int k, vector<int> &nums, vector<vector<ll>> &dp)
    {
        if(k == 0) return 0;
        if(dp[i][k] != LLONG_MAX)
            return dp[i][k];
        
        ll sum = 0, currMax = LLONG_MIN;
        
        ll sign = (turn & 1)? 1 : -1;
        ll msum = LLONG_MIN;
        for(int j = i; j <= nums.size() - k; j++)
        {
            sum += (ll)nums[j];
            ll ret = dfs(j+1, (turn ^ 1), k-1, nums, dp);
            if(ret == LLONG_MIN) continue;
            if(turn)
                currMax = max(currMax, ret + (sum * k));
            else
                currMax = max(currMax, ret - (sum * k));
            
            if(sum * sign < 0)
                sum = 0;
        }
        return dp[i][k] = currMax;
    }
    
    long long maximumStrength(vector<int>& nums, int k) 
    {
        vector<ll> psum(nums.size(), 0);
        for(int i = 0; i < nums.size(); i++)
            psum[i] = nums[i] + (i? psum[i-1] : 0);
        vector<vector<ll>> dp(nums.size(), vector<ll>(k+1, LLONG_MAX));
        return dfs(0, 1, k, nums, dp);
    }
};
