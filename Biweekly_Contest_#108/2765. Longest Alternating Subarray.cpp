class Solution {
public:
    int alternatingSubarray(vector<int>& nums) 
    {
        int n = nums.size(), i = 0, maxLen = 0;
        
        while(i+1 < n)
        {
            int j = i;
            int x = nums[i+1] - nums[i];
            if(x != 1)
            {
                i++;
                continue;
            }
            while(j+1 < n && nums[j+1] - nums[j] == x)
            {
                x *= -1;
                j++;
            }
            maxLen = max(maxLen, j-i+1);
            if(j == i) i++;
            else i = j;
        }
        
        return maxLen >= 2? maxLen : -1;
    }
};
