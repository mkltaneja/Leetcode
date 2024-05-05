
// Time Complexity = O(n + MX)
// Space Complexity = O(1)

class Solution {
public:
    
    int MOD = 1e9 + 7;
    #define ll long long
    
    ll findTotalCostWithPairs(ll ops, ll maxDiff, ll cost1, ll cost2)
    {
        ll rem = ops - maxDiff;
        if(rem < maxDiff)
            return (rem * cost2) + ((maxDiff - rem) * cost1);
        
        return (ops / 2) * cost2 + ((ops & 1)? cost1 : 0);
    }
    
    int minCostToEqualizeArray(vector<int>& nums, int cost1, int cost2)
    {
        int n = nums.size();
        ll sum = accumulate(nums.begin(), nums.end(), 0ll);
        ll mx = *max_element(nums.begin(), nums.end());
        ll mn = *min_element(nums.begin(), nums.end());
        ll ops = n*mx - sum;
        
        if(2*cost1 <= cost2)
            return (ops * cost1) % MOD;
        
        ll ans = LLONG_MAX;
        
        for(ll maxEle = mx; maxEle <= 2*mx; maxEle++)
        {
            ll maxDiff = maxEle - mn;
            ops = maxEle * n - sum;
            ans = min(ans, findTotalCostWithPairs(ops, maxDiff, cost1, cost2));
        }
        
        return ans % MOD;
    }
};
