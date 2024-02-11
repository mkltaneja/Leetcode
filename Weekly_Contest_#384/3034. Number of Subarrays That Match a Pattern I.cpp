
// Time Complexity = O(n * m)
// Space Complexity = O(1)

class Solution {
public:
    int countMatchingSubarrays(vector<int>& nums, vector<int>& pattern) 
    {
        int n = nums.size(), m = pattern.size();
        int ans = 0;
        for(int i = 0; i < n-1 && i+m < n; i++)
        {
            int fl = 1;
            for(int j = i; j-i < m && fl; j++)
            {
                if(pattern[j-i] == 1)
                {
                    if(nums[j+1] <= nums[j])
                        fl = 0;
                }
                else if(pattern[j-i] == -1)
                {
                    if(nums[j+1] >= nums[j])
                        fl = 0;
                }
                else
                {
                    if(nums[j+1] != nums[j])
                        fl = 0;
                }
            }
            ans += fl;
        }
        return ans;
    }
};
