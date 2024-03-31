
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long countAlternatingSubarrays(vector<int>& nums) 
    {
        ll ans = 0;
        int n = nums.size();
        for(ll i = 0, j = 0; i < n; i++)
        {
            if(i && nums[i] == nums[i-1])
                j = i;
            ans += i-j+1;
        }
        return ans;
    }
};
