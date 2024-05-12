
// Time Complexity = O(n^2 * 26)
// Space Complexity = O(n + 1004)

class Solution {
public:
    
    int dp[1005];
    bool isValid(vector<int> &mp)
    {
        int prev = -1;
        for(int x : mp)
        {
            if(x == 0) continue;
            if(prev == -1)
                prev = x;
            else if(x != prev)
                return false;
        }
        return true;
    }
    
    int dfs(int i, int n, string &s)
    {
        if(i == n)
            return 0;
        if(dp[i] != -1)
            return dp[i];
        
        int minAns = INT_MAX;
        vector<int> mp(26,0);
        for(int j = i; j < n; j++)
        {
            mp[s[j]-'a']++;
            if(isValid(mp))
            {
                int nxt = dfs(j+1, n, s);
                minAns = min(minAns, nxt + 1);
            }
        }
        return dp[i] = minAns;
    }
    
    int minimumSubstringsInPartition(string s) 
    {
        int n = s.size();
        memset(dp, -1, sizeof(dp));
        return dfs(0, n, s);
    }
};
