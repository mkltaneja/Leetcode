class Solution {
public:
    
    int mod = 1e9 + 7;
    int maxSum(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<int> bitCount(32, 0);
        for(int x : nums)
            for(int i = 0; i < 32; i++)
                bitCount[i] += ((x >> i) & 1);
        vector<int> top(n);
        for(int &x : top)
        {
            for(int i = 0; i < 32; i++)
            {
                if(bitCount[i])
                {
                    x |= (1 << i);
                    bitCount[i]--;
                }
            }
        }
        
        int ans = 0;
        for(int i = 0; i < k; i++)
            ans = (ans % mod + 1ll * top[i] * top[i] % mod) % mod;
        
        return ans;
    }
};
