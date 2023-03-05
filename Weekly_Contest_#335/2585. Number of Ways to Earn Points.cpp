class Solution {
public:
    
    int mod = 1e9 + 7;
    int waysToReachTarget(int target, vector<vector<int>>& types) 
    {
        int n = types.size();
        vector<int> dp(target+1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; i++)
        {
            int cnt = types[i][0];
            int x = types[i][1];
            for(int t = target; t >= 0; t--)
            {
                for(int j = 1; j <= cnt && t - (x*j) >= 0; j++)
                    dp[t] = (dp[t] % mod + (dp[t - (x*j)] % mod)) % mod;
            }
        }
        
        return dp[target];
    }
};
