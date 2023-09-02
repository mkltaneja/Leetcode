class Solution {
public:
    
    int MOD = 1e9 + 7;
    int countKSubsequencesWithMaxBeauty(string s, int k) 
    {
        int n = s.size();
        
        vector<int> map(26, 0);
        int uni = 0;
        for(char c : s)
            if(map[c-'a']++ == 0)
                uni++;
        
        if(k > uni) return 0;
        
        sort(map.rbegin(), map.rend());
        
        long ans = 1;
        int lastCnt = 0, lastVal = map[k-1];
        int rem = 0;
        for(int i = 0; i < map.size(); i++)
        {
            if(map[i] < lastVal) break;
            if(map[i] != lastVal)
                ans = ans * map[i] % MOD;
            else 
            {
                lastCnt++;
                rem += i < k;
            }
        }
        
        vector<long> dp(lastCnt+1, 0);
        dp[0] = 1;
        for(int i = 1; i <= lastCnt; i++)
        {
            for(int j = i; j >= 1; j--)
                dp[j] = (dp[j] + dp[j-1] * lastVal) % MOD;
        }
        
        return ans * dp[rem] % MOD;
    }
};
