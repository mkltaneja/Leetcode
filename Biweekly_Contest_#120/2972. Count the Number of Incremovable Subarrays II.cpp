
// Time = O(n*logn), Space = O(1)

class Solution {
public:
    
    #define ll long long
    long long incremovableSubarrayCount(vector<int>& nums) 
    {
        int n = nums.size();
        ll l = 0, r = n-1;
        ll ans = 0;
        while(l+1 < n && nums[l+1] > nums[l]) l++;
        while(r-1 >= 0 && nums[r-1] < nums[r]) r--;
        
        if(l == n-1)
            return 1ll * n * (n+1) / 2;
        
        ans += (ll)n - r + 1;
        for(int i = 0; i <= l; i++)
        {
            int ub = upper_bound(nums.begin() + r, nums.end(), nums[i]) - nums.begin();
            ans += (ll)n - ub + 1;
        }
        
        return ans;
    }
};
