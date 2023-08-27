class Solution {
public:
    
    int countBits(int x)
    {
        int bits = 0;
        while(x)
        {
            x -= x & -x;
            bits++;
        }
        return bits;
    }
    
    int minOperations(vector<int>& nums, int target) 
    {
        vector<int> bitCount(32);
        for(int x : nums)
            bitCount[countBits(x-1)]++;
        
        int ops = 0;
        for(int i = 0; i <= 30; i++)
        {
            if(target & (1 << i))
            {
                if(!bitCount[i])
                {
                    bool isPossible = false;
                    for(int j = i+1; j <= 30; j++)
                    {
                        if(!bitCount[j]) continue;

                        bitCount[j]--;
                        for(int k = i; k < j; k++)
                        {
                            bitCount[k]++;
                            ops++;
                        }
                        isPossible = true;
                        break;
                    }
                    if(!isPossible) return -1;
                }
                bitCount[i]--;
            }
            bitCount[i+1] += bitCount[i] / 2;
        }
        
        return ops;
    }
};
