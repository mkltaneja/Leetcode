class Solution {
public:
    
    vector<int> closestPrimes(int left, int right) 
    {
        vector<int> primes, isPrime(right+1, 1);
        isPrime[0] = isPrime[1] = 0;
        for(int i = 2; i*i <= right; i++)
        {
            if(!isPrime[i]) continue;
            for(int j = i*i; j <= right; j += i)
                isPrime[j] = 0;
        }
        for(int i = left; i <= right; i++)
            if(isPrime[i])
                primes.push_back(i);
        
        int minDiff = INT_MAX;
        vector<int> ans = {-1, -1};
        for(int i = 1; i < primes.size(); i++)
        {
            if(primes[i] - primes[i-1] < minDiff)
            {
                minDiff = primes[i] - primes[i-1];
                ans = {primes[i-1], primes[i]};
            }
        }
        
        return ans;
    }
};
