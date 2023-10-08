class Solution {
public:
    
    int dfs(int i, int x, int n, vector<int> &idx, vector<int> &dp)
    {
        if(i >= n) return 0;
        if(dp[i] != -1)
            return dp[i];
        
        int withX = dfs(i+1, x, n, idx, dp) + x;
        int withoutX = i+1 < n? (dfs(i+2, x, n, idx, dp) + 2*(idx[i+1] - idx[i])) : INT_MAX;
        return dp[i] = min(withX, withoutX);
    }
    
    int minOperations(string s1, string s2, int x) 
    {
        int n = s1.size();
        vector<int> idx;
        for(int i = 0; i < n; i++)
            if(s1[i] != s2[i])
                idx.push_back(i);
        n = idx.size();
        if(n & 1) return -1;
        
        vector<int> dp(n, -1);
        return dfs(0, x, n, idx, dp) / 2;
    }
};
