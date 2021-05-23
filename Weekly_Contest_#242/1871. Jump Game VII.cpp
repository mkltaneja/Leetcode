
// APPROACH 1 (BFS) --> O(n^2)
// TLE

bool canReach(string s, int minJump, int maxJump)
{
    if (s[s.size() - 1] == '1')
        return false;
    queue<int> que;
    que.push(0);
    vector<bool> vis(s.size());
    while (!que.empty())
    {
        int j = que.front();
        que.pop();
        if (j == s.size() - 1)
            return true;
        for (int i = j + minJump; i < s.size() && i <= j + maxJump; i++)
            if (s[i] == '0' && !vis[i])
                vis[i] = true, que.push(i);
    }
    return false;
}

// APPROACH 2 (DFS using DP) --> O(n^2)
// TLE

bool dfs(int i, int n, int minj, int maxj, string &s, vector<int> &dp)
{
    if (i == n)
        return dp[i] = true;
    if (i + minj > n)
        return false;
    if (dp[i] != -1)
        return dp[i];
    for (int j = i + minj; j <= n && j <= i + maxj; j++)
        if (s[j] == '0')
            if (dfs(j, n, minj, maxj, s, dp))
                return dp[j] = true;
    return dp[i] = false;
}

bool canReach(string s, int minJump, int maxJump)
{
    if (s[s.size() - 1] == '1')
        return false;
    vector<int> dp(s.size(), -1);
    return dfs(0, s.size() - 1, minJump, maxJump, s, dp);
}

// APPROACH 3 (Range Query Sum Approach) --> O(n)
// AC

bool canReach(string s, int minJump, int maxJump)
{
    if (s[s.size() - 1] == '1')
        return false;
    vector<int> ways(2 * s.size() + 1, 0);
    int psum = 0;
    ways[0] = 1;
    ways[1] = -1;
    for (int i = 0; i < s.size(); i++)
    {
        psum += ways[i];
        if (psum == 0 || s[i] == '1')
            continue;
        ways[i + minJump]++;
        ways[i + maxJump + 1]--;
    }
    return (psum > 0);
}