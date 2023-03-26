class Solution {
public:
    
    #define ll long long
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) 
    {
        sort(nums.begin(), nums.end());
        ll sum = 0;
        int n = nums.size();
        vector<ll> psum(n);
        int i = 0;
        for(int x : nums)
        {
            sum += x;
            psum[i++] = sum;
        }
        
        vector<ll> ans;
        for(int x : queries)
        {
            int ub = upper_bound(nums.begin(), nums.end(), x) - nums.begin();
            ll s1 = (ub)? psum[ub-1] : 0;
            ll s2 = psum[n-1] - ((ub)? psum[ub-1] : 0);
            ans.push_back(((ll)ub * x - s1) + (s2 - (ll)(n - ub) * x));
        }
        
        return ans;
    }
};
