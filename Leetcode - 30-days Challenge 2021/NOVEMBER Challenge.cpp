
// DAY 1 (130. Surrounded Regions)

void dfs(int i, int j, int n, int m, vector<vector<char>> &arr)
{
    if (i == -1 || j == -1 || i == n || j == m || arr[i][j] == 'X' || arr[i][j] == '#')
        return;

    arr[i][j] = '#';
    dfs(i + 1, j, n, m, arr);
    dfs(i, j + 1, n, m, arr);
    dfs(i - 1, j, n, m, arr);
    dfs(i, j - 1, n, m, arr);
}

void solve(vector<vector<char>> &board)
{
    int n = board.size(), m = board[0].size();

    for (int i = 0; i < n; i++)
    {
        if (board[i][0] == 'O')
            dfs(i, 0, n, m, board);
        if (board[i][m - 1] == 'O')
            dfs(i, m - 1, n, m, board);
    }
    for (int i = 0; i < m; i++)
    {
        if (board[0][i] == 'O')
            dfs(0, i, n, m, board);
        if (board[n - 1][i] == 'O')
            dfs(n - 1, i, n, m, board);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 'O')
                board[i][j] = 'X';
            else if (board[i][j] == '#')
                board[i][j] = 'O';
        }
    }
}