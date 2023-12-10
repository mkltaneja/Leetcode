
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k) 
    {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end());
        vector<int> mxi;
        long long ans = 0;
        
        for(long long i = 0, j = 0; i < n; i++)
        {
            if(nums[i] == mx)
            {
                mxi.push_back(i);
                if(mxi.size() - j > k) j++;
            }
            if(mxi.size() >= k)
                ans += (long long)mxi[j] + 1;
        }
        
        return ans;
    }
};
