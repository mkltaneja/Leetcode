
// Time = O(n*logn), Space = O(n)

class Solution {
public:
    vector<int> numberGame(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> arr;
        sort(nums.begin(), nums.end());
        for(int i = 1; i < n; i+=2)
        {
            arr.push_back(nums[i]);
            arr.push_back(nums[i-1]);
        }
        return arr;
    }
};
