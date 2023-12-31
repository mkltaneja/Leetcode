
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) 
    {
        int evens = 0;
        for(int x : nums)
            evens += (x & 1) == 0;
        return evens >= 2;
    }
};
