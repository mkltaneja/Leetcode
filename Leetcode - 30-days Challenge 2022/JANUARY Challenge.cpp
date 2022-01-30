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

// DAY 19 (142. Linked List Cycle II)========================================================================

ListNode *detectCycle(ListNode *head)
{
    ListNode *fast = head, *slow = head;
    bool loop = false;
    while (fast && fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (fast == slow)
        {
            loop = true;
            break;
        }
    }
    if (!loop)
        return NULL;

    slow = head;
    while (slow != fast)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return fast;
}

// DAY 20 (875. Koko Eating Bananas)================================================================================================

bool check(unsigned long k, int h, vector<int> &piles)
{
    unsigned long time = 0;
    for (int x : piles)
    {
        time += ceil(1.0 * x / k);
        if (time > h)
            return false;
    }
    return true;
}

int minEatingSpeed(vector<int> &piles, int h)
{
    unsigned long l = 1, r = 0;
    for (int x : piles)
        r += x;

    while (l < r)
    {
        unsigned long m = l + ((r - l) >> 1);
        bool res = check(m, h, piles);

        if (res)
            r = m;
        else
            l = m + 1;
    }
    return l;
}

// DAY 21 (134. Gas Station)======================================================================

int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int ans = 0;
    int currgas = 0, totgas = 0;
    for (int i = 0; i < gas.size(); i++)
    {
        int delta = gas[i] - cost[i];
        totgas += delta;
        currgas += delta;
        if (currgas < 0)
        {
            currgas = 0;
            ans = i + 1;
        }
    }
    return totgas < 0 ? -1 : ans % gas.size();
}

// DAY 22 (1510. Stone Game IV)======================================================

bool winnerSquareGame(int n)
{
    vector<bool> win(n + 1, false);

    for (int x = 1; x <= n; x++)
    {
        int m = 1;
        while (x - m * m >= 0 && win[x - m * m])
            m++;
        if (x - m * m < 0)
            win[x] = false;
        else
            win[x] = true;
    }
    return win[n];
}

// DAY 23 (1291. Sequential Digits)=====================================================================

vector<int> sequentialDigits(int low, int high)
{
    vector<int> ans;
    for (int i = 1; i < 9; i++)
    {
        long x = i;
        int j = i;
        while (x <= high && j <= 9)
        {
            if (x >= low)
                ans.push_back(x);
            x = x * 10 + ++j;
        }
    }
    sort(ans.begin(), ans.end());

    return ans;
}

// DAY 24 (520. Detect Capital)================================================================================

bool iscap(char &c)
{
    return c >= 'A' && c <= 'Z';
}

bool detectCapitalUse(string word)
{
    int cap = 0;
    for (int i = 0; i < word.size(); i++)
        if (iscap(word[i]))
            cap++;
    return !cap || (cap == word.size()) || (cap == 1 && iscap(word[0]));
}

// DAY 25 (941. Valid Mountain Array)=======================================================================================

bool validMountainArray(vector<int> &arr)
{
    int i = 0, j = arr.size() - 1;
    while (i < j && arr[i] < arr[i + 1])
        i++;
    while (j > i && arr[j] < arr[j - 1])
        j--;

    return i > 0 && i == j && j < arr.size() - 1;
}

// DAY 26 (1305. All Elements in Two Binary Search Trees)==========================================================================================

// METHOD 1 (Inorder DFS)

void inorder(TreeNode *node, vector<int> &in)
{
    if (!node)
        return;
    inorder(node->left, in);
    in.push_back(node->val);
    inorder(node->right, in);
}

vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
{
    vector<int> in1, in2;
    inorder(root1, in1);
    inorder(root2, in2);

    int n = in1.size(), m = in2.size();
    vector<int> ans(n + m);
    int i = 0, j = 0, k = 0;
    while (k < n + m)
    {
        int x = i < n ? in1[i] : INT_MAX;
        int y = j < m ? in2[j] : INT_MAX;
        if (x < y)
            ans[k++] = x, i++;
        else
            ans[k++] = y, j++;
    }

    return ans;
}

// METHOD 2 (Morris Inorder Traversal)

vector<int> morris_inorder(TreeNode *node)
{
    vector<int> in;
    while (node)
    {
        if (!node->left)
        {
            in.push_back(node->val);
            node = node->right;
            continue;
        }
        TreeNode *nodep1 = node->left;
        while (nodep1->right && nodep1->right != node)
            nodep1 = nodep1->right;
        if (!nodep1->right)
        {
            nodep1->right = node;
            node = node->left;
        }
        else
        {
            in.push_back(node->val);
            node = node->right;
            nodep1->right = nullptr;
        }
    }
    return in;
}

vector<int> getAllElements(TreeNode *root1, TreeNode *root2)
{
    vector<int> in1 = morris_inorder(root1);
    vector<int> in2 = morris_inorder(root2);

    int n = in1.size(), m = in2.size();
    vector<int> ans(n + m);
    int i = 0, j = 0, k = 0;
    while (k < n + m)
    {
        int x = i < n ? in1[i] : INT_MAX;
        int y = j < m ? in2[j] : INT_MAX;
        if (x < y)
            ans[k++] = x, i++;
        else
            ans[k++] = y, j++;
    }

    return ans;
}

// DAY 27 (421. Maximum XOR of Two Numbers in an Array)============================================================================

class trie
{
public:
    vector<trie *> on;
    trie()
    {
        this->on.assign(2, nullptr);
    }

    void insert(int x, trie *root)
    {
        trie *tmp = root;
        for (int i = 31; i >= 0; i--)
        {
            int idx = (x >> i & 1);
            if (!tmp->on[idx])
                tmp->on[idx] = new trie();
            tmp = tmp->on[idx];
        }
    }
};
trie *root = new trie();

int findMaximumXOR(vector<int> &nums)
{
    for (int x : nums)
    {
        root->insert(x, root);
    }

    int ans = 0;
    for (int x : nums)
    {
        int mx = 0;
        trie *tmp = root;
        for (int i = 31; i >= 0; i--)
        {
            int idx = (x >> i & 1 ^ 1);
            if (tmp->on[idx])
            {
                mx |= (1 << i);
                tmp = tmp->on[idx];
            }
            else
                tmp = tmp->on[idx ^ 1];
        }
        ans = max(ans, mx);
    }

    return ans;
}

// DAY 28 (211. Design Add and Search Words Data Structure)========================================================================================
class WordDictionary
{
public:
    class trie
    {
    public:
        vector<trie *> on;
        bool wordEnd;
        trie()
        {
            this->on.assign(26, nullptr);
            this->wordEnd = false;
        }
    };

    trie *root;
    WordDictionary()
    {
        this->root = new trie();
    }

    void addWord(string word)
    {
        trie *tmp = root;
        for (char c : word)
        {
            if (!tmp->on[c - 'a'])
                tmp->on[c - 'a'] = new trie();
            tmp = tmp->on[c - 'a'];
        }
        tmp->wordEnd = true;
    }

    bool dfs(int i, trie *curr, string &word)
    {
        if (i == word.size())
            return curr->wordEnd;
        if (word[i] == '.')
        {
            for (trie *itr : curr->on)
                if (itr && dfs(i + 1, itr, word))
                    return true;
            return false;
        }

        return curr->on[word[i] - 'a'] ? dfs(i + 1, curr->on[word[i] - 'a'], word) : false;
    }

    bool search(string word)
    {
        return dfs(0, root, word);
    }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

// DAY 29 (84. Largest Rectangle in Histogram)==========================================================================

int largestRectangleArea(vector<int> &heights)
{
    int n = heights.size();
    stack<int> st;
    st.push(-1);
    int ans = 0;
    for (int i = 0; i <= n; i++)
    {
        int x = (i == n) ? INT_MIN : heights[i];
        while (st.top() != -1 && x <= heights[st.top()])
        {
            int h = heights[st.top()];
            st.pop();
            ans = max(ans, h * (i - st.top() - 1));
        }
        st.push(i);
    }
    return ans;
}

// DAY 30 (189. Rotate Array)=============================================================================

// APPROACH 1 (Linear Space)

// METHOD 1 (Marking Visited indices)

void rotate(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<bool> vis(n, false);
    int viscnt = 0;

    k %= n;
    if (!k)
        return;
    int i = k, prev = nums[0];
    while (viscnt < n)
    {
        while (viscnt < n && !vis[i])
        {
            int curr = nums[i];
            nums[i] = prev;
            prev = curr;
            vis[i] = true;
            viscnt++;
            i = (i + k) % n;
        }
        prev = nums[++i % n];
        i = (i + k) % n;
    }
}