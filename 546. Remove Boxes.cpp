
int dfs(int l, int r, int cnt, vector<int> &boxes, vector<vector<vector<int>>> &dp)
{
    if (l > r)
        return 0;
    if (dp[l][r][cnt])
        return dp[l][r][cnt];

    int ldash = l, cntdash = cnt;
    while (ldash <= r && boxes[ldash] == boxes[l])
    {
        ldash++;
        cntdash++;
    }

    int ans = dfs(ldash, r, 0, boxes, dp) + cntdash * cntdash;

    for (int i = ldash; i <= r; i++)
        if (boxes[i] == boxes[l])
            ans = max(ans, dfs(ldash, i - 1, 0, boxes, dp) + dfs(i, r, cntdash, boxes, dp));

    return dp[l][r][cnt] = ans;
}

int removeBoxes(vector<int> &boxes)
{
    int n = boxes.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, 0)));
    return dfs(0, boxes.size() - 1, 0, boxes, dp);
}