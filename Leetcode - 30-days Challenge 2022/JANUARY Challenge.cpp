// DAY 1 (312. Burst Balloons)====================================================================

int maxCoins(vector<int> &nums)
{
    vector<vector<int>> dp(nums.size() + 2, vector<int>(nums.size() + 2, 0));
    // (nums.size() + 2) is for handling the -1 and nums.size(),
    // so the convention will be l+1, r+1 everywhere
    for (int len = 2; len <= nums.size() + 1; len++)
    {
        for (int l = -1, r = l + len; r <= nums.size(); l++, r++)
        {
            int currans = 0;
            for (int i = l + 1; i < r; i++)
            {
                int lans = l == -1 ? 1 : nums[l];
                int rans = r == nums.size() ? 1 : nums[r];
                int lmax = l == -1 ? 1 : dp[l][i];
                int rmax = r == nums.size() ? 1 : dp[i][r];
                currans = max(currans, dp[l + 1][i + 1] + lans * nums[i] * rans + dp[i + 1][r + 1]);
            }
            dp[l + 1][r + 1] = currans;
        }
    }

    return dp[0][nums.size() + 1];
}

// DAY 2 (1010. Pairs of Songs With Total Durations Divisible by 60)=====================================================================

int numPairsDivisibleBy60(vector<int> &time)
{
    int n = time.size();
    unordered_map<int, int> m;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int mod = time[i] % 60;
        ans += m[(60 - mod) % 60];
        m[mod]++;
    }
    return ans;
}

// DAY 3 (997. Find the Town Judge)================================================================================

int findJudge(int n, vector<vector<int>> &trust)
{
    vector<int> tcnt(n, 0);
    for (vector<int> v : trust)
    {
        tcnt[v[1] - 1]++;
        tcnt[v[0] - 1]--;
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (tcnt[i] == n - 1)
        {
            if (ans)
                return -1;
            ans = i + 1;
        }
    }

    return ans ? ans : -1;
}

// DAY 4 (1009. Complement of Base 10 Integer)========================================================================

int bitwiseComplement(int n)
{
    if (n == 0)
        return 1;

    int ans = 0;
    int cnt = 0;
    while (n)
    {
        ans |= ((n & 1 ^ 1) << cnt++);
        n >>= 1;
    }

    return ans;
}

// DAY 5 (131. Palindrome Partitioning)========================================================================================

vector<vector<string>> ans;
void dfs(int i, string &s, vector<vector<int>> &ispal, vector<string> &curr)
{
    if (i == s.size())
        ans.push_back(curr);

    for (int j = i; j < s.size(); j++)
    {
        if (s[i] == s[j] && (j - i <= 2 || ispal[i + 1][j - 1]))
        {
            ispal[i][j] = 1;
            curr.push_back(s.substr(i, j - i + 1));
            dfs(j + 1, s, ispal, curr);
            curr.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    int n = s.size();
    vector<vector<int>> ispal(n, vector<int>(n));

    vector<string> curr;
    dfs(0, s, ispal, curr);

    return ans;
}

// DAY 6 (1094. Car Pooling)========================================================================

bool carPooling(vector<vector<int>> &trips, int capacity)
{
    int people[1001] = {0};

    int mxd = 0;
    for (vector<int> v : trips)
    {
        people[v[2]] -= v[0];
        people[v[1]] += v[0];
        mxd = max(mxd, v[2]);
    }
    for (int i = 0; i <= mxd; i++)
    {
        people[i] += i ? people[i - 1] : 0;
        if (people[i] > capacity)
            return false;
    }

    return true;
}

// DAY 7 (382. Linked List Random Node)=========================================================================
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    vector<int> nodes;
    Solution(ListNode *head)
    {
        ListNode *node = head;
        while (node)
        {
            this->nodes.push_back(node->val);
            node = node->next;
        }
    }

    int getRandom()
    {
        return nodes[rand() % nodes.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(head);
 * int param_1 = obj->getRandom();
 */

//  DAY 8 (1463. Cherry Pickup II)===============================================================================

// APPROACH 1 (4D DP - Memoization)

int dfs(int i1, int j1, int i2, int j2, int n, int m, vector<vector<int>> &grid, vector<vector<vector<vector<int>>>> &dp)
{
    if (j1 == -1 || i1 == n || j1 == m || j2 == -1 || i2 == n || j2 == m)
        return 0;

    if (dp[i1][j1][i2][j2] != -1)
        return dp[i1][j1][i2][j2];

    int x1 = grid[i1][j1];
    int x2 = grid[i2][j2];

    int ans = INT_MIN;
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            ans = max(ans, dfs(i1 + 1, j1 + x, i2 + 1, j2 + y, n, m, grid, dp));
    return dp[i1][j1][i2][j2] = ans + x1 + ((i1 == i2 && j1 == j2) ? 0 : x2);
}

int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<vector<int>>>> dp(n, vector<vector<vector<int>>>(m, vector<vector<int>>(n, vector<int>(m, -1))));
    return dfs(0, 0, 0, m - 1, n, m, grid, dp);
}

// APPROACH 2 (3D DP)

// METHOD 1 (Memoization)

int dfs(int i, int j1, int j2, int n, int m, vector<vector<int>> &grid, vector<vector<vector<int>>> &dp)
{
    if (i == n || j1 == -1 || j1 == m || j2 == -1 || j2 == m)
        return 0;

    if (dp[i][j1][j2] != -1)
        return dp[i][j1][j2];

    int ans = INT_MIN;
    for (int x = -1; x <= 1; x++)
        for (int y = -1; y <= 1; y++)
            ans = max(ans, dfs(i + 1, j1 + x, j2 + y, n, m, grid, dp));
    return dp[i][j1][j2] = ans + grid[i][j1] + ((j1 == j2) ? 0 : grid[i][j2]);
}

int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(m, -1)));
    return dfs(0, 0, m - 1, n, m, grid, dp);
}

// METHOD 2 (Tabulation)=====================================================

int cherryPickup(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(m, 0)));

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j1 = 0; j1 < m; j1++)
        {
            for (int j2 = 0; j2 < m; j2++)
            {
                dp[i][j1][j2] = grid[i][j1] + ((j1 == j2) ? 0 : grid[i][j2]);
                if (i == n - 1)
                    continue;
                int ans = INT_MIN;
                for (int x = -1; x <= 1; x++)
                    for (int y = -1; y <= 1; y++)
                        ans = max(ans, (j1 + x == -1 || j1 + x == m || j2 + y == -1 || j2 + y == m) ? 0 : dp[i + 1][j1 + x][j2 + y]);
                dp[i][j1][j2] += ans;
            }
        }
    }

    return dp[0][0][m - 1];
}