
// APPROACH 1 (Finding lb and ub with binary search everytime) --> time = O(n*logn)

class Solution {
public:

    #define ll long long
    long long countFairPairs(vector<int>& nums, int lower, int upper) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        ll ans = 0;
        for(int i = 0; i < n; i++)
        {
            int lb = lower_bound(nums.begin()+i+1, nums.end(), lower - nums[i]) - nums.begin();
            int ub = upper_bound(nums.begin()+i+1, nums.end(), upper - nums[i]) - nums.begin();
            if(lb == n || nums[i] + nums[lb] > upper) continue;
            ans += (ll)(ub - lb);
        }
        
        return ans;
    }
};

// APPROACH 2 (Finding lb and ub linearly) --> time = O(n) [OPTIMIZED]

class Solution {
public:

    #define ll long long
    long long countFairPairs(vector<int>& nums, int lower, int upper) 
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        ll ans = 0;
        for(int i = 0, lo = n-1, hi = n-1; i < n && hi > i; i++)
        {
            while(lo >= 0 && nums[i] + nums[lo] >= lower) lo--;
            while(hi > i && nums[i] + nums[hi] > upper) hi--;
            ans += hi - max(lo, i);
        }
        
        return ans;
    }
};
