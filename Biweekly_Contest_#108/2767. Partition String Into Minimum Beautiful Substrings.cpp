
// APPROACH 1 (Subsequence Method)

class Solution {
public:
    
    bool isPowerOf5(int x)
    {
        while(x > 1)
        {
            if(x % 5) return false;
            x /= 5;
        }
        return x == 1;
    }
    
    int ans = INT_MAX;
    void dfs(int i, int x, int n, string &s, int cnt)
    {
        if(i == n)
        {
            bool chk = (isPowerOf5(x));
            if(!chk) return;
            ans = min(ans, cnt + chk);
            return;
        }
        if(x == 0 && s[i] == '0') return;
        
        x = (x << 1) | (s[i]-'0');
        
        bool check = isPowerOf5(x);
        if(check)
            dfs(i+1, 0, n, s, cnt+1);
        dfs(i+1, x, n, s, cnt);
    }
    
    int minimumBeautifulSubstrings(string s) 
    {
        int n = s.size();
        dfs(0, 0, n, s, 0);
        return ans == INT_MAX? -1 : ans;
    }
};

// APPROACH 2 (Using DP) [OPTIMIZED]

class Solution {
public:
    
    int ans = INT_MAX;
    unordered_set<int> p5;    
    int dfs(int i, int n, string &s, vector<int> &dp)
    {
        if(i == n)
            return 0;
        if(s[i] == '0')
            return 1e6;
        if(dp[i] != -1) return dp[i];

        int ans = 1e6, x = 0;
        for(int j = i; j < n; j++)
        {
            x = (x << 1) | (s[j]-'0');
            if(p5.count(x))
                ans = min(ans, dfs(j+1, n, s, dp) + 1);
        }
        
        return dp[i] = ans;
    }
    
    int minimumBeautifulSubstrings(string s) 
    {
        int n = s.size();
        int x = 1;
        while(x < 1e6)
        {
            p5.insert(x);
            x *= 5;
        }
        
        vector<int> dp(20, -1);
        int ans = dfs(0, n, s, dp);
        return ans >= 1e6? -1 : ans;
    }
};
