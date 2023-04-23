class Solution {
public:
    int minOperations(vector<int>& nums) 
    {
        int n = nums.size();
        int g = 0, ones = 0;
        for(int x : nums)
        {
            g = __gcd(g, x);
            ones += x == 1;
        }
        if(g > 1) return -1;
        if(ones) return n - ones;
        
        int ans = 2*n;
        for(int i = 0; i < n; i++)
        {
            int g = nums[i];
            for(int j = i+1; j < n; j++)
            {
                g = __gcd(g, nums[j]);
                if(g == 1) ans = min(ans, (n - i - 1) + j);
            }
        }
        
        return ans;
    }
};
