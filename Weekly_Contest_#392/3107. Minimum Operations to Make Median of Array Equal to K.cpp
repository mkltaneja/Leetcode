
// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long minOperationsToMakeMedianK(vector<int>& nums, int k) 
    {
        int n = nums.size();
        ll ans = 0;
        sort(nums.begin(), nums.end());
        int medi = n / 2;
        
        if(k < nums[medi])
            for(int i = medi; i >= 0 && nums[i] > k; i--)
                ans += 1ll * abs(nums[i] - k);
        else
            for(int i = medi; i < n && nums[i] < k; i++)
                ans += 1ll * abs(nums[i] - k);
        
        return ans;
    }
};
