class Solution {
public:
    int semiOrderedPermutation(vector<int>& nums) 
    {
        int pos1 = -1, posn = -1, n = nums.size();
        for(int i = 0; i < n; i++)
        {
            if(nums[i] == 1)
                pos1 = i;
            else if(nums[i] == n)
                posn = i;
        }
        return pos1 + (n-posn-1 - (posn < pos1));
    }
};
