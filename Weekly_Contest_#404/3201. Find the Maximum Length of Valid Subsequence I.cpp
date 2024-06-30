
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int maximumLength(vector<int>& nums)
    {
        int evens = 0, odds = 0, alts1 = 0, alts2 = 0, last1 = 0, last2 = 1;
        int ans = 0;
        for(int num : nums)
        {
            if(num & 1)
            {
                odds++;
                if(last1 & 1 ^ 1) alts1++, last1 ^= 1;
                if(last2 & 1 ^ 1) alts2++, last2 ^= 1;
            }
            else
            {
                evens++;
                if(last1 & 1) alts1++, last1 ^= 1;
                if(last2 & 1) alts2++, last2 ^= 1;
            }
        }
        
        return max({evens, odds, alts1, alts2});
    }
};
