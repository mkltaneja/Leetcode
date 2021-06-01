// Recursion
// TLE
int count_rec(string &s, int vidx, vector<int> &dp)
{
    if (vidx == s.size())
        return 1;

    char ch = s[vidx];
    if (ch == '0')
        return 0;
    int count = 0;
    count += count_rec(s, vidx + 1, dp);

    if (vidx < s.size() - 1)
    {
        int num = (s[vidx] - '0') * 10 + (s[vidx + 1] - '0');
        if (num <= 26)
            count += count_rec(s, vidx + 2, dp);
    }
    return count;
}

int numDecodings(string s)
{
    if (s.size() == 0)
        return 0;
    vector<int> dp(s.size() + 1, 0);

    return count_rec(s, 0, dp);
}

// Memoization

int count_rec(string &s, int vidx, vector<int> &dp)
{
    if (vidx == s.size())
        return dp[vidx] = 1;

    if (dp[vidx] != -1)
        return dp[vidx];

    char ch = s[vidx];
    if (ch == '0')
        return dp[vidx] = 0;
    int count = 0;
    count += count_rec(s, vidx + 1, dp);

    if (vidx < s.size() - 1)
    {
        int num = (s[vidx] - '0') * 10 + (s[vidx + 1] - '0');
        if (num <= 26)
            count += count_rec(s, vidx + 2, dp);
    }
    return dp[vidx] = count;
}

int numDecodings(string s)
{
    if (s.size() == 0)
        return 0;
    vector<int> dp(s.size() + 1, -1);

    return count_rec(s, 0, dp);
}