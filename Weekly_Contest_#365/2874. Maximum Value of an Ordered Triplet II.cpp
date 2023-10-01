class Solution {
public:
    #define ll long long
    long long maximumTripletValue(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> mx1(n), mx2(n);
        for(int i = 0; i < n; i++)
        {
            mx1[i] = max((i? mx1[i-1] : 0), nums[i]);
            mx2[n-i-1] = max((i? mx2[n-i] : 0), nums[n-i-1]);
        }
        
        ll maxAns = -1;
        for(int i = 1; i < n-1; i++)
            maxAns = max(maxAns, ((ll)mx1[i-1] - nums[i]) * (ll)mx2[i+1]);
        
        return max(0ll, maxAns);
    }
};
