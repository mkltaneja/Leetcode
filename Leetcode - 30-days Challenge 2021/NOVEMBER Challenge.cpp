
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

// DAY 5 (441. Arranging Coins)=================================================================================================

int arrangeCoins(int n)
{
    int l = 1, r = INT_MAX;
    while (l < r)
    {
        long m = l + (r - l) / 2;
        if (m * (m + 1) / 2 == n)
            return m;
        if (m * (m + 1) / 2 < n)
            l = m + 1;
        else
            r = m;
    }
    return l - 1;
}

// DAY 6 (260. Single Number III)===================================================================================

vector<int> singleNumber(vector<int> &nums)
{
    long comb = 0;
    for (int x : nums)
        comb ^= x;
    long rsb = comb & -comb;
    int a = 0, b = 0;
    for (int x : nums)
    {
        if (x & rsb)
            a ^= x;
        else
            b ^= x;
    }
    return {a, b};
}

// DAY 7 (43. Multiply Strings)=====================================================================

string multiply(string num1, string num2)
{
    int n = num1.size(), m = num2.size();
    vector<int> prod(n + m);
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            int x = i + j;
            int y = i + j + 1;
            int sum = (num1[i] - '0') * (num2[j] - '0') + prod[y];
            prod[y] = sum % 10;
            prod[x] += sum / 10;
        }
    }

    string ans = "";
    for (int i = 0; i < n + m; i++)
    {
        if (prod[i] == 0 && ans.empty())
            continue;
        ans += prod[i] + '0';
    }

    return ans.empty() ? "0" : ans;
}

// DAY 8 (Unique Binary Search Trees)=============================================================================

// METHOD 1 (Memoized)

int dp[20];
int numTrees(int n)
{
    if (n <= 2)
        return n ? n : 1;
    if (dp[n])
        return dp[n];

    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans += numTrees(i - 1) * numTrees(n - i);

    return dp[n] = ans;
}

// METHOD 2 (Tabulized)

int numTrees(int n)
{
    vector<int> ans(n + 1);
    ans[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
            ans[i] += ans[j - 1] * ans[i - j];
    }
    return ans[n];
}

// DAY 9 (1178. Number of Valid Words for Each Puzzle)=====================================================================================

int toBit(string s)
{
    int mask = 0;
    for (char c : s)
        mask |= 1 << (c - 'a');

    return mask;
}

vector<int> findNumOfValidWords(vector<string> &words, vector<string> &puzzles)
{
    int n = puzzles.size();
    unordered_map<int, int> m;
    for (string s : words)
        m[toBit(s)]++;

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int first = (1 << (puzzles[i][0] - 'a'));
        int tot = m[first];

        int mask = toBit(puzzles[i].substr(1));
        int submask = mask;
        while (submask)
        {
            tot += m[submask | first];
            submask = (submask - 1) & mask;
        }
        ans[i] = tot;
    }
    return ans;
}