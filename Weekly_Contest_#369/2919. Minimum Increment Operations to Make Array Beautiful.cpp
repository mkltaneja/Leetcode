class Solution {
public:
    
    #define ll long long
    long long minIncrementOperations(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<ll> dp(3);
        for(int i = 0; i < 3; i++)
            dp[i] = max(0, k - nums[i]);
        for(int i = 3; i < n; i++)
        {
            vector<ll> ndp(3);
            ndp[0] = dp[1];
            ndp[1] = dp[2];
            ndp[2] = min({dp[0], dp[1], dp[2]}) + (ll)max(0, k - nums[i]);
            
            dp = ndp;
        }
        
        return min({dp[0], dp[1], dp[2]});
    }
};
