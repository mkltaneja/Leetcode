
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int longestMonotonicSubarray(vector<int>& nums) 
    {
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i < n; )
        {
            int j = i+1;
            while(j < n && nums[j] > nums[j-1]) j++;
            ans = max(ans, j-i);
            i = j;
        }
        for(int i = 0; i < n; )
        {
            int j = i+1;
            while(j < n && nums[j] < nums[j-1]) j++;
            ans = max(ans, j-i);
            i = j;
        }
        return ans;
    }
};
