class Solution {
public:
    bool primeSubOperation(vector<int>& nums) 
    {
        vector<int> isPrime(1005, 1);
        for(int i = 2; i <= 1000; i++)
        {
            if(!isPrime[i]) continue;
            for(int j = i*i; j <= 1000; j += i)
                isPrime[j] = 0;
        }
        
        vector<int> primes;
        for(int i = 2; i <= 1000; i++)
            if(isPrime[i])
                primes.push_back(i);
        
        int n = nums.size();
        int p = 0;
        for(int i = 0; i < n; i++)
        {
            int lb = (lower_bound(primes.begin(), primes.end(), nums[i] - p) - primes.begin()) - 1;
            if(lb == -1 && nums[i] <= p) 
                return false;
            p = nums[i];
            if(lb == -1) continue;
            p = nums[i] - primes[lb];
        }
        
        return true;
    }
};
