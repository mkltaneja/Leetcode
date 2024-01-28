
// Time Complexity = O(n*30)
// Space Complexity = O(1)

class Solution {
public:
    int minOrAfterOperations(vector<int>& nums, int k) 
    {
        int minAns = 0, offBitsMask = 0;
        for(int i = 30; i >= 0; i--)
        {
            int ops = 0, currMask = offBitsMask | (1 << i), currVal = 0;
            for(int x : nums)
            {
                if(currVal)
                    currVal &= currMask & x;
                else currVal = currMask & x;
                
                if(currVal) ops++;
            }
            if(ops <= k) offBitsMask |= (1 << i);
            else minAns |= (1 << i);
        }
        
        return minAns;
    }
};
