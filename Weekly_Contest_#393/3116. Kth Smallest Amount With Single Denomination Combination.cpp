
// Time Complexity = O(n * sqrt(n))
// Space Complexity = O(1)

class Solution {
public:
    
    bool isPrime(int x)
    {
        for(int i = 2; i*i <= x; i++)
            if(x % i == 0)
                return false;
        return x > 1;
    }
    
    int checkFirstPrime(int n, vector<int> &nums)
    {
        for(int i = 0; i < n; i++)
            if(isPrime(nums[i]))
                return i;
        return -1;
    }
    
    int maximumPrimeDifference(vector<int>& nums)
    {
        int n = nums.size();
        int minPrimeIdx = checkFirstPrime(n, nums);
        reverse(nums.begin(), nums.end());
        int maxPrimeIdx = n - checkFirstPrime(n, nums) - 1;
        
        return maxPrimeIdx - minPrimeIdx;
    }
};
