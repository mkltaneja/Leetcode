class Solution {
public:
    
    #define ll long long
    long long countGood(vector<int>& nums, int k) 
    {
        int n = nums.size();
        unordered_map<ll,ll> count;
        ll p = 0, ans = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++)
        {
            sum += count[nums[i]]++;
            while(sum >= k)
                sum -= --count[nums[p++]];
            ans += p;
        }
        
        return ans;
    }
};
