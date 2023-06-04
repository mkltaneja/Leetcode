class Solution {
public:
    
    int mod = 1e9 + 7;
    int dp[30][300][2];
    
    int getCountHelper(int i, int curSum, bool isMaxNum, string &num, int minSum, int maxSum)
    {
        if(i == num.size())
            return curSum >= minSum && curSum <= maxSum;
        if(dp[i][curSum][isMaxNum] != -1)
            return dp[i][curSum][isMaxNum];
        
        int st = 0, end = isMaxNum? (num[i]-'0') : 9;
        int ans = 0;
        for(int x = st; x <= end; x++)
            ans = (ans % mod + getCountHelper(i+1, curSum + x, (isMaxNum && x == end)? true : false, num, minSum, maxSum) % mod) % mod;
        
        return dp[i][curSum][isMaxNum] = ans % mod;
    }
    
    int getCount(int i, int curSum, bool isMaxNum, string &num, int minSum, int maxSum)
    {
        memset(dp, -1, sizeof(dp));
        return getCountHelper(i, curSum, isMaxNum, num, minSum, maxSum);
    }
    
    int count(string num1, string num2, int min_sum, int max_sum) 
    {
        int ans = getCount(0, 0, true, num2, min_sum, max_sum) - getCount(0, 0, true, num1, min_sum, max_sum);
        int num1Sum = 0;
        for(char c : num1)
            num1Sum += c-'0';
        ans = (ans + (num1Sum >= min_sum && num1Sum <= max_sum)) % mod;
        return ans % mod;
    }
};
