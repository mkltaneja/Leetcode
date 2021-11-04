
// DAY 1 (130. Surrounded Regions)========================================================================

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

// DAY 2 (980. Unique Paths III)=============================================================================

int dfs(int i, int j, int empty, int n, int m, vector<vector<int>> &arr)
{
    if (i == n || j == m || i == -1 || j == -1 || arr[i][j] == -1)
        return 0;
    if (arr[i][j] == 2)
    {
        if (empty == 0)
            return 1;
        return 0;
    }

    arr[i][j] = -1;
    int ans = dfs(i + 1, j, empty - 1, n, m, arr) +
              dfs(i, j + 1, empty - 1, n, m, arr) +
              dfs(i - 1, j, empty - 1, n, m, arr) +
              dfs(i, j - 1, empty - 1, n, m, arr);
    arr[i][j] = 0;

    return ans;
}

int uniquePathsIII(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int si, sj, empty = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
                si = i, sj = j;
            else if (grid[i][j] == 0)
                empty++;
        }
    }
    return dfs(si, sj, empty + 1, n, m, grid);
}

// DAY 3 (129. Sum Root to Leaf Numbers)========================================================================================

int ans = 0;
void dfs(TreeNode *node, int x)
{
    if (!node)
        return;
    if (!node->left && !node->right)
    {
        ans += x * 10 + node->val;
        return;
    }
    dfs(node->left, x * 10 + node->val);
    dfs(node->right, x * 10 + node->val);
}

int sumNumbers(TreeNode *root)
{
    dfs(root, 0);
    return ans;
}

// DAY 4 (404. Sum of Left Leaves)=================================================================================

int sumOfLeftLeaves(TreeNode *root)
{
    if (!root)
        return 0;
    int tot = sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);

    return tot + ((root->left && !root->left->left && !root->left->right) ? root->left->val : 0);
}