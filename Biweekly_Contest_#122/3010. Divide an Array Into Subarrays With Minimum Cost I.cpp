// APPROACH 1

// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int minimumCost(vector<int>& nums) 
    {
        int mn1 = 100, mn2 = 100;
        for(int i = 1; i < nums.size(); i++)
        {
            if(nums[i] < mn1)
                mn2 = mn1, mn1 = nums[i];
            else mn2 = min(mn2, nums[i]);
        }
        
        return nums[0] + mn1 + mn2;
    }
};

// APPROACH 2

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

class Solution {
public:
    int minimumCost(vector<int>& nums) 
    {
        sort(nums.begin()+1, nums.end());
        
        return nums[0] + nums[1] + nums[2];
    }
};
