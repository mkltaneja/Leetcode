// DAY 1 (Longest Common Subsequence)============================================================

int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size(), m = text2.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int im1 = i ? dp[i - 1][j] : 0;
            int jm1 = j ? dp[i][j - 1] : 0;
            int ijm1 = (i && j) ? dp[i - 1][j - 1] : 0;

            dp[i][j] = (text1[i] == text2[j]) ? max({ijm1 + 1, im1, jm1}) : max(im1, jm1);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

// DAY 2 (Dungeon Game)================================================================================

int calculateMinimumHP(vector<vector<int>> &dungeon)
{
    int n = dungeon.size(), m = dungeon[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[n - 1][m - 1] = (dungeon[n - 1][m - 1] <= 0) ? (-dungeon[n - 1][m - 1] + 1) : 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1 && j == m - 1)
                continue;

            int right = (j != m - 1) ? dp[i][j + 1] : INT_MAX;
            int down = (i != n - 1) ? dp[i + 1][j] : INT_MAX;

            dp[i][j] = max(-dungeon[i][j] + min(right, down), 1);
        }
    }

    return dp[0][0];
}

// DAY 3 (Jump Game)=================================================================================

bool canJump(vector<int> &nums)
{
    int maxjump = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        maxjump--;
        maxjump = max(maxjump, nums[i]);
        if (i != nums.size() - 1 && maxjump == 0)
            return false;
    }
    return true;
}

// DAY 4 (Island Perimeter)============================================================================

int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j])
            {
                ans += (i ? (grid[i - 1][j] == 0) : 1);
                ans += (j ? (grid[i][j - 1] == 0) : 1);
                ans += ((i != n - 1) ? (grid[i + 1][j] == 0) : 1);
                ans += ((j != m - 1) ? (grid[i][j + 1] == 0) : 1);
            }
        }
    }
    return ans;
}