
// Time Complexity = O((sqrt(n) * log(log(sqrt(n)))) + sqrt(n))

class Solution {
public:
    
    int getCnt(int n)
    {
        if(n <= 1)
            return n;
        int x = sqrt(n);
        
        vector<bool> isPrime(x + 1, true);

        isPrime[0] = isPrime[1] = false;

        for (int p = 2; p * p <= x; p++)
            if (isPrime[p])
                for (int i = p * p; i <= x; i += p)
                    isPrime[i] = false;

        int primeCount = 0;
        for (int p = 2; p <= x; p++)
            if (isPrime[p])
                primeCount++;
        
        return n - primeCount;
    }
    
    int nonSpecialCount(int l, int r)
    {
        int lcnt = getCnt(l-1);
        int rcnt = getCnt(r);
        return rcnt - lcnt;
    }
};
