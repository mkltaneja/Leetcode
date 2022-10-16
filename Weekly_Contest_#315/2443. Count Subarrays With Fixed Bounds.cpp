class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) 
    {
        long long lastmn = 0, lastmx = 0;
        long long mn = INT_MAX, mx = -1;
        long long x = 0;
        long long ans = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] == minK) lastmn = i+1;
            if(nums[i] == maxK) lastmx = i+1;
            if(nums[i] < minK || nums[i] > maxK) 
            {
                lastmn = 0, lastmx = 0;
                x = i+1;
            }
            if(lastmn && lastmx) 
                ans += min(lastmn-x, lastmx-x);
        }
        
        return ans;
    }
};
