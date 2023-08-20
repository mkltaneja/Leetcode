class Solution {
public:
    
    int dp[10][2][22][2][11][11];
    
    int dfs(int i, int st, int curr, bool prevSmall, int odds, int evens, string num, int k)
    {
        if(i == num.size()) 
            return odds == evens && curr == 0;
        
        if(dp[i][st][curr][prevSmall][odds][evens] != -1)
            return dp[i][st][curr][prevSmall][odds][evens];
        
        int ans = 0;
        if(st == 1) ans = dfs(i+1, 1, curr, 1, odds, evens, num, k);
        
        int mul = 1;
        for(int j = i+1; j < num.size(); j++)
            mul *= 10;
        
        for(int x = st; x <= 9; x++)
        {
            if(prevSmall || x < num[i]-'0')
                ans += dfs(i+1, 0, (x*mul + curr) % k, true, odds+(x&1), evens+(x&1^1), num, k);
            else if(x == num[i]-'0')
                ans += dfs(i+1, 0, (x*mul + curr) % k, false, odds+(x&1), evens+(x&1^1), num, k);
        }
        return dp[i][st][curr][prevSmall][odds][evens] = ans;
    }
    
    int solve(int num, int k)
    {
        memset(dp, -1, sizeof(dp));
        string numStr = to_string(num);
        
        return dfs(0, 1, 0, false, 0, 0, numStr, k);
    }
    
    int numberOfBeautifulIntegers(int low, int high, int k) 
    {
        return solve(high, k) - solve(low-1, k);
    }
};
