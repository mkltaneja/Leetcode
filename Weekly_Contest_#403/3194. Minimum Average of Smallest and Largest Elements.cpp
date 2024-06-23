
// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

class Solution {
public:
    double minimumAverage(vector<int>& nums) 
    {
        double averages = INT_MAX;
        sort(nums.begin(), nums.end());
        for(int i = 0, j = nums.size()-1; i < j; i++, j--)
            averages = min(averages, (nums[i] + nums[j]) / 2.0);
        return averages;
    }
};
