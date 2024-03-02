
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int minOperations(vector<int>& nums, int k) 
    {
        int total = 0;
        for(int i = 0; i < nums.size(); i++)
            if(nums[i] < k)
                total++;
        return total;
    }
};
