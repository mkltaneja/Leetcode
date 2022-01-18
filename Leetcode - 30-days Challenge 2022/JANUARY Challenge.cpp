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

// DAY 9 (1041. Robot Bounded In Circle)==================================================================

bool isRobotBounded(string instructions)
{
    vector<vector<int>> dir = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int idx = 0, x = 0, y = 0;
    vector<int> d = dir[idx], di = d;
    for (int i = 0; i < 4; i++)
    {
        for (char c : instructions)
        {
            if (c == 'R')
                idx = ++idx % 4;
            else if (c == 'L')
                idx = (--idx + 4) % 4;
            else
                x += d[0], y += d[1];

            d = dir[idx];
        }

        if (d == di && (x == 0 && y == 0))
            return true;
    }
    return false;
}

// DAY 10 (67. Add Binary)================================================================

string addBinary(string a, string b)
{
    string c = "";
    int n = a.size(), m = b.size();
    int carry = 0;
    while (n || m)
    {
        int x = n ? a[--n] - '0' : 0;
        int y = m ? b[--m] - '0' : 0;
        int z = x + y + carry;
        c = char((z % 2) + '0') + c;
        carry = z / 2;
    }
    c = (carry ? "1" : "") + c;

    return c;
}

// DAY 11 (1022. Sum of Root To Leaf Binary Numbers)=========================================================

int dfs(int sum, TreeNode *node)
{
    if (!node)
        return 0;
    sum = sum * 2 + node->val;
    if (!node->left && !node->right)
        return sum;
    return dfs(sum, node->left) + dfs(sum, node->right);
}

int sumRootToLeaf(TreeNode *root)
{
    return dfs(0, root);
}

// DAY 12 (701. Insert into a Binary Search Tree)============================================================================

// APPROACH 1 (Recursively)

TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);

    if (val < root->val)
        root->left = insertIntoBST(root->left, val);
    else
        root->right = insertIntoBST(root->right, val);

    return root;
}

// APPROACH 2 (Iteratively)

TreeNode *insertIntoBST(TreeNode *root, int val)
{
    if (!root)
        return new TreeNode(val);
    TreeNode *node = root;
    while (true)
    {
        if (val < node->val)
        {
            if (node->left)
                node = node->left;
            else
            {
                node->left = new TreeNode(val);
                break;
            }
        }
        else
        {
            if (node->right)
                node = node->right;
            else
            {
                node->right = new TreeNode(val);
                break;
            }
        }
    }
    return root;
}

// DAY 13 (452. Minimum Number of Arrows to Burst Balloons)===============================================================================

int findMinArrowShots(vector<vector<int>> &points)
{
    sort(points.begin(), points.end());
    int arrows = 1;
    int end = points[0][1];
    for (int i = 1; i < points.size(); i++)
    {
        if (points[i][0] > end)
        {
            end = points[i][1];
            arrows++;
        }
        else
            end = min(end, points[i][1]);
    }
    return arrows;
}

// DAY 14 (8. String to Integer (atoi))=================================================================

bool isnum(char c)
{
    return (c >= '0' && c <= '9');
}

int myAtoi(string s)
{
    int n = s.size();
    int i = 0;
    while (i < n && s[i] == ' ')
        i++;
    int sign = 1;
    if (i < n && (s[i] == '-' || s[i] == '+'))
        sign = (s[i] == '-') ? -1 : 1, i++;
    long ans = 0;
    while (i < n && isnum(s[i]))
    {
        ans *= 10;
        if (sign == 1)
            ans += s[i] - '0';
        else
            ans -= s[i] - '0';
        if (ans >= INT_MAX)
            return INT_MAX;
        if (ans <= INT_MIN)
            return INT_MIN;
        i++;
    }

    return ans;
}

// DAY 15 (1345. Jump Game IV)==============================================================================

// APPROACH 1 (DFS) --> O(n^n)
// TLE

unordered_map<int, vector<int>> m;
int minjumps(int i, vector<int> &vis, vector<int> &arr)
{
    if (i == -1 || i == arr.size() || vis[i])
        return INT_MAX;
    if (i == arr.size() - 1)
        return 0;

    vis[i] = true;

    int minans = min({minjumps(i - 1, vis, arr),
                      minjumps(i + 1, vis, arr)});

    for (int x : m[arr[i]])
        minans = min(minans, minjumps(x, vis, arr));

    vis[i] = false;

    return minans == INT_MAX ? 0 : minans + 1;
}

int minJumps(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
        m[arr[i]].push_back(i);
    vector<int> vis(arr.size());
    return minjumps(0, vis, arr);
}

// APPROACH 2 (BFS) --> O(n^n), but MUCH OPTIMIZED (and passes all tc)

int minJumps(vector<int> &arr)
{
    unordered_map<int, vector<int>> m;
    int n = arr.size();
    for (int i = 0; i < n; i++)
        m[arr[i]].push_back(i);

    queue<int> que;
    que.push(n - 1);

    vector<int> vis(n);
    vis[n - 1] = true;

    int lvl = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            int i = que.front();
            que.pop();

            if (i == 0)
                return lvl;

            for (int d : {-1, 1})
            {
                if (i + d >= 0 && i + d < n && !vis[i + d])
                {
                    if (i + d == 0)
                        return lvl + 1;
                    vis[i + d] = true;
                    que.push(i + d);
                }
            }
            for (int x : m[arr[i]])
            {
                if (!vis[x])
                {

                    if (x == 0)
                        return lvl + 1;
                    vis[x] = true;
                    que.push(x);
                }
            }
        }
        lvl++;
    }
    return lvl;
}

// DAY 16 (849. Maximize Distance to Closest Person)======================================================================

// APPROACH 1 (Storing the minimum distances in an array) --> O(3*n) time, O(n) space

int maxDistToClosest(vector<int> &seats)
{
    int n = seats.size();
    vector<int> d(n, INT_MAX);
    for (int i = 0; i < n; i++)
        d[i] = seats[i] ? 0 : ((!i || d[i - 1] == INT_MAX) ? INT_MAX : (d[i - 1] + 1));
    for (int i = n - 2; i >= 0; i--)
        d[i] = min(d[i], d[i + 1] + 1);

    int ans = 0;
    for (int x : d)
        ans = max(ans, x);

    return ans;
}

// APPROACH 2 (Single Traversal -- Using the previous seat pointer) --> O(n) time, O(1) space

int maxDistToClosest(vector<int> &seats)
{
    int n = seats.size();
    int i = 0, pi = -1;
    int ans = 0;
    while (!seats[i])
        i++;
    while (i < n)
    {
        if (seats[i])
        {
            if (pi == -1)
                ans = max(ans, i);
            else
                ans = max(ans, (i - pi) / 2);
            pi = i;
        }
        i++;
    }
    return max(ans, i - pi - 1);
}

// DAY 17 (290. Word Pattern)==============================================================================

bool wordPattern(string pattern, string s)
{
    unordered_map<char, int> m1;
    unordered_map<string, int> m2;

    int j = 0;
    for (int i = 0; i < pattern.size(); i++)
    {
        if (j >= s.size())
            return false;
        char c = pattern[i];
        string ss = "";
        while (j < s.size() && s[j] != ' ')
            ss += s[j++];
        j++;
        if (!m1.count(c))
            m1[c] = i;
        if (!m2.count(ss))
            m2[ss] = i;

        if (m1[c] != m2[ss])
            return false;
    }

    return (j >= s.size());
}

// DAY 18 (605. Can Place Flowers)===================================================================================================

bool canPlaceFlowers(vector<int> &flowerbed, int n)
{
    int m = flowerbed.size();
    int avail = 0;
    int i = 0;
    while (i < m)
    {
        if (flowerbed[i] == 1)
        {
            i++;
            continue;
        }
        int j = i;
        int z = 0;
        while (j < m && flowerbed[j] == 0)
        {
            z++;
            j++;
        }
        if (i == 0 && j == m)
            avail += (z + 1) / 2;
        else if (i == 0 || j == m)
            avail += z / 2;
        else
            avail += (z - 1) / 2;
        i = j;
        if (avail >= n)
            return true;
    }
    return avail >= n;
}