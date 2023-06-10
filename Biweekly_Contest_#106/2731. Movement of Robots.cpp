class Solution {
public:
    
    int mod = 1e9 + 7;
    int sumDistance(vector<int>& nums, string s, int d) 
    {
        int n = s.size();
        vector<long> pos(n);
        for(int i = 0; i < n; i++)
            pos[i] = s[i] == 'R'? nums[i] + d : nums[i] - d;
        sort(pos.begin(), pos.end());
        
        long ans = 0, sumpos = 0;
        for(int i = n-1; i >= 0; i--)
        {
            ans = (ans % mod + (sumpos - (pos[i] % mod * (n - 1 - i) % mod) % mod) % mod) % mod;
            sumpos = (sumpos % mod + pos[i] % mod) % mod;
        }
        
        return (ans + mod) % mod;
    }
};
