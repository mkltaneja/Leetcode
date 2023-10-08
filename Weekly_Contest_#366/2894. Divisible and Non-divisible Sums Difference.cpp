class Solution {
public:
    int differenceOfSums(int n, int m) 
    {
        long sum1 = 0, sum2 = 0;
        for(long x = 1; x <= n; x++)
        {
            if(x % m == 0) sum1 += x;
            else sum2 += x;
        }
        
        return sum2 - sum1;
    }
};
