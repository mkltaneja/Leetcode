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

// DAY 5 (Climbing Stairs)====================================================================

int climbStairs(int n)
{
    int a = 1, b = 1, ans = 1;
    while (--n)
    {
        a = b;
        b = ans;
        ans = a + b;
    }
    return ans;
}

// DAY 6 (Find All Duplicates in an Array)===============================================================

vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[abs(nums[i]) - 1] > 0)
            nums[abs(nums[i]) - 1] *= -1;
        else
            ans.push_back(abs(nums[i]));
    }
    return ans;
}

// DAY 7 (Word Search)===============================================================================

bool dfs(int i, int j, int k, int n, int m, vector<vector<char>> &board, string &s)
{
    if (k == s.size())
        return true;
    if (i == -1 || j == -1 || i == n || j == m || board[i][j] != s[k])
        return false;

    char c = board[i][j];
    board[i][j] = '#';
    if (dfs(i + 1, j, k + 1, n, m, board, s))
        return true;
    if (dfs(i, j + 1, k + 1, n, m, board, s))
        return true;
    if (dfs(i - 1, j, k + 1, n, m, board, s))
        return true;
    if (dfs(i, j - 1, k + 1, n, m, board, s))
        return true;
    board[i][j] = c;

    return false;
}

bool exist(vector<vector<char>> &board, string word)
{
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (dfs(i, j, 0, n, m, board, word))
                return true;
    return false;
}

// DAY 8 (Implement Trie (Prefix Tree))===============================================================================
class Trie
{
public:
    class Node
    {
    public:
        vector<Node *> t;
        bool wordEnd;
        Node()
        {
            this->t.assign(26, nullptr);
            this->wordEnd = false;
        }
    };

    Node *node;

    Trie()
    {
        this->node = new Node();
    }

    void insert(string word)
    {
        Node *curr = node;
        for (char c : word)
        {
            if (!curr->t[c - 'a'])
                curr->t[c - 'a'] = new Node();
            curr = curr->t[c - 'a'];
        }
        curr->wordEnd = true;
    }

    bool search(string word)
    {
        Node *curr = node;
        for (char c : word)
        {
            if (!curr->t[c - 'a'])
                return false;
            curr = curr->t[c - 'a'];
        }
        return curr->wordEnd;
    }

    bool startsWith(string prefix)
    {
        Node *curr = node;
        for (char c : prefix)
        {
            if (!curr->t[c - 'a'])
                return false;
            curr = curr->t[c - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// DAY 10 (Bitwise and Number Range)======================================================================

// APPROACH 1 (Find the last OFF bit for a particular ON bit) --> O(32)

int rangeBitwiseAnd(int left, int right)
{
    int ans = 0;
    int i = 0;
    while (i < 32)
    {
        if (right & (1 << i))
        {
            int offbit = right & ~(1 << i);
            offbit |= (1 << i) - 1;
            if (left > offbit)
                ans |= (1 << i);
        }
        i++;
    }

    return ans;
}

// APPROACH 2 (Find maximum common prefix) --> O(log(right))

int rangeBitwiseAnd(int left, int right)
{
    int x = 0;
    while (left != right)
    {
        left >>= 1;
        right >>= 1;
        x++;
    }
    return left << x;
}