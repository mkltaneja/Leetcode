
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    bool canAliceWin(vector<int>& nums)
    {
        int s = 0, d = 0;
        for(int num : nums)
        {
            if(num / 10 == 0)
                s += num;
            else d += num;
        }
        return max(s, d) > min(s, d);
    }
};
