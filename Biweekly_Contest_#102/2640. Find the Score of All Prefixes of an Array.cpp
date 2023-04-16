class Solution {
public:
    
    #define ll long long
    vector<long long> findPrefixScore(vector<int>& nums) 
    {
        int n = nums.size();
        vector<ll> ans(n);
        
        ll mx = 0;
        for(int i = 0; i < n; i++)
        {
            mx = max(mx, (ll)nums[i]);
            ans[i] = mx + (ll)nums[i] + (i? ans[i-1] : 0ll);
        }
        
        return ans;
    }
};
