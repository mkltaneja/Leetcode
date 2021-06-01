
const double eps = 1e-8;
int minSkips(vector<int> &dist, int speed, int hoursBefore)
{
    int n = dist.size();
    vector<vector<double>> dp(n, vector<double>(n, 0));

    for (int i = 1; i < n; i++)
    {
        double t = (double)dist[i - 1] / speed;
        // Note:- j will represent a skip
        for (int j = 0; j <= i; j++)
        {
            dp[i][j] = INT_MAX;
            // If we don't take a skip, but take a break
            // Note:- We subtracted the term by "eps", as "t" may have precesion of more than allowed numbers, so the value will be                                 rounded off and the last precesion number after decimal may be increased by 1, and if it keeps on doing this, then                           our answer will keep on increasing, so we need to sutract it by indefinitely small value.
            if (j < i)
                dp[i][j] = ceil(dp[i - 1][j] + t - eps);
            // If we take a skip
            if (j)
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + t);
        }
    }
    // Note:- dist[n-1] is remaining because there will be n-1 skips at max, so we will just take the answer of taking a break ->[i-1][j]
    double t = (double)dist[n - 1] / speed;
    for (int j = 0; j < n; j++)
        if (dp[n - 1][j] + t <= hoursBefore)
            return j;
    return -1;
}