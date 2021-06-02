// DAY 1 (Max Area of Island)=============================================================

int dfs(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    if (i == -1 || j == -1 || i == n || j == m || !grid[i][j])
        return 0;

    int area = 0;
    grid[i][j] = 0;

    return dfs(i + 1, j, n, m, grid) +
           dfs(i, j + 1, n, m, grid) +
           dfs(i - 1, j, n, m, grid) +
           dfs(i, j - 1, n, m, grid) + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int maxarea = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                maxarea = max(maxarea, dfs(i, j, n, m, grid));
    return maxarea;
}

// DAY 2 (Interleaving Strings)=================================================================================

// APPROACH 1 (Backtracking -- Form "s2" using backtracking and at the base case check whether remaining string is equal to s1) --> <O(n^m) [n = s3.size(), m = s2.size()]
// TLE

bool check(int bi, int ci, string &a, string &b, string &c, vector<bool> &vis)
{
    if (bi == b.size())
    {
        string aa = "", bb = "";
        for (int i = 0; i < c.size(); i++)
        {
            if (!vis[i])
                aa += c[i];
            else
                bb += c[i];
        }
        cout << aa << ", " << bb << endl;
        if (aa == a)
            return true;
        return false;
    }
    for (int i = ci; i < c.size(); i++)
    {
        if (c[i] == b[bi] && !vis[i])
        {
            vis[i] = true;
            if (check(bi + 1, i + 1, a, b, c, vis))
                return true;
            vis[i] = false;
        }
    }
    return false;
}

bool isInterleave(string s1, string s2, string s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;
    vector<bool> vis(s3.size(), false);

    return check(0, 0, s1, s2, s3, vis);
}

// APPROACH 2
// Method 1 (Brute Force) --> O(2^(n+m))
// TLE

bool check(int ai, int bi, int ci, string &a, string &b, string &c)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c);

    return (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;

    return check(0, 0, 0, s1, s2, s3);
}

// Method 2 (Memoized) Sub-metod 1--> O(nm*n*m)
// AC

bool check(int ai, int bi, int ci, string &a, string &b, string &c, vector<vector<vector<int>>> &dp)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());
    if (dp[ai][bi][ci] != -1)
        return dp[ai][bi][ci];

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c, dp);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c, dp);

    return dp[ai][bi][ci] = (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    int n = s1.size();
    int m = s2.size();
    int nm = s3.size();
    if (n + m != nm)
        return false;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(nm + 1, -1)));
    return check(0, 0, 0, s1, s2, s3, dp);
}

// Sub-method 2 --> O(n*m) [Space and time OPTIMIZED]

bool check(int ai, int bi, int ci, string &a, string &b, string &c, vector<vector<int>> &dp)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());
    if (dp[ai][bi] != -1)
        return dp[ai][bi];

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c, dp);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c, dp);

    return dp[ai][bi] = (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    int n = s1.size();
    int m = s2.size();
    int nm = s3.size();
    if (n + m != nm)
        return false;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return check(0, 0, 0, s1, s2, s3, dp);
}