
int uniquePaths(int n, int m)
{
    vector<vector<int>> paths(n, vector<int>(m, 0));
    paths[n - 1][m - 1] = 1;

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1 && j == m - 1)
                continue;
            int dans = (i == n - 1) ? 0 : paths[i + 1][j];
            int rans = (j == m - 1) ? 0 : paths[i][j + 1];

            paths[i][j] = dans + rans;
        }
    }

    return paths[0][0];
}