class Solution {
public:
    
    bool isPrime(int x)
    {
        for(int i = 2; i*i <= x; i++)
            if(x % i == 0)
                return false;
        return x > 1? true : false;
    }
    
    int diagonalPrime(vector<vector<int>>& nums) 
    {
        int ans = 0;
        for(int i = 0; i < nums.size(); i++)
        {
            if(isPrime(nums[i][i]))
                ans = max(ans, nums[i][i]);
            if(isPrime(nums[i][nums[i].size()-i-1]))
                ans = max(ans, nums[i][nums[i].size()-i-1]);
        }
        
        return ans;
    }
};
