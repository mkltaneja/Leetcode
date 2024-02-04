
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int returnToBoundaryCount(vector<int>& nums) 
    {
        int curr = 0, ans = 0;
        for(int x : nums)
        {
            curr += x;
            ans += curr == 0;
        }
        return ans;
    }
};
