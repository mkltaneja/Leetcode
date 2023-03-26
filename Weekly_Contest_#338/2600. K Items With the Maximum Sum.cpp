class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) 
    {
        int ans = 0;
        ans += min(k, numOnes);
        k -= min(k, numOnes);
        k -= min(k, numZeros);
        if(k) ans -= min(k, numNegOnes);
        
        return ans;
    }
};
