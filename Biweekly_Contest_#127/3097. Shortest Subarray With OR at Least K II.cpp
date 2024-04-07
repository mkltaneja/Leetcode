
// Time Complexity = O(n*32)
// Space Complexity = O(32)

class Solution {
public:
    int minimumSubarrayLength(vector<int>& nums, int k) 
    {
        int ans = INT_MAX;
        vector<int> bits(32, 0);
        for(int l = 0, r = 0, x = 0; r < nums.size(); r++)
        {
            x |= nums[r];
            for(int i = 0; i < 32; i++)
                bits[i] += (nums[r] & (1 << i))? 1 : 0;
            while(l <= r && x >= k)
            {
                ans = min(ans, r-l+1);
                for(int i = 0; i < 32; i++)
                {
                    bits[i] -= (nums[l] & (1 << i))? 1 : 0;
                    if(bits[i] == 0)
                        x &= ~(1 << i);
                }
                l++;
            }
        }
        
        return ans == INT_MAX? -1 : ans;
    }
};
