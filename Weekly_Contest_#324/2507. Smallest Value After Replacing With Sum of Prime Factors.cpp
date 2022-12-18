class Solution {
public:
    int smallestValue(int n) 
    {
        if(n == 4) return 4;
        long sum = 0;
        
        bool fl = true;
        while(fl)
        {
            fl = false;
            for(int i = 2; i*i <= n; i++)
            {
                while(n % i == 0)
                {
                    sum += i;
                    n /= i;
                    fl = true;
                }
            }
            if(n > 1)
                sum += n;
            n = sum;
            sum = 0;
        }
        
        return n;
    }
};
