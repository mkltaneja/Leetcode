// DAY 1 (Max Area of Island)=============================================================

int dfs(int i, int j, int n, int m, vector<vector<int>> &grid)
{
    if (i == -1 || j == -1 || i == n || j == m || !grid[i][j])
        return 0;

    int area = 0;
    grid[i][j] = 0;

    return dfs(i + 1, j, n, m, grid) +
           dfs(i, j + 1, n, m, grid) +
           dfs(i - 1, j, n, m, grid) +
           dfs(i, j - 1, n, m, grid) + 1;
}

int maxAreaOfIsland(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int maxarea = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j])
                maxarea = max(maxarea, dfs(i, j, n, m, grid));
    return maxarea;
}

// DAY 2 (Interleaving Strings)=================================================================================

// APPROACH 1 (Backtracking -- Form "s2" using backtracking and at the base case check whether remaining string is equal to s1) --> <O(n^m) [n = s3.size(), m = s2.size()]
// TLE

bool check(int bi, int ci, string &a, string &b, string &c, vector<bool> &vis)
{
    if (bi == b.size())
    {
        string aa = "", bb = "";
        for (int i = 0; i < c.size(); i++)
        {
            if (!vis[i])
                aa += c[i];
            else
                bb += c[i];
        }
        cout << aa << ", " << bb << endl;
        if (aa == a)
            return true;
        return false;
    }
    for (int i = ci; i < c.size(); i++)
    {
        if (c[i] == b[bi] && !vis[i])
        {
            vis[i] = true;
            if (check(bi + 1, i + 1, a, b, c, vis))
                return true;
            vis[i] = false;
        }
    }
    return false;
}

bool isInterleave(string s1, string s2, string s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;
    vector<bool> vis(s3.size(), false);

    return check(0, 0, s1, s2, s3, vis);
}

// APPROACH 2
// Method 1 (Brute Force) --> O(2^(n+m))
// TLE

bool check(int ai, int bi, int ci, string &a, string &b, string &c)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c);

    return (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    if (s3.size() != s1.size() + s2.size())
        return false;

    return check(0, 0, 0, s1, s2, s3);
}

// Method 2 (Memoized) Sub-metod 1--> O(nm*n*m)
// AC

bool check(int ai, int bi, int ci, string &a, string &b, string &c, vector<vector<vector<int>>> &dp)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());
    if (dp[ai][bi][ci] != -1)
        return dp[ai][bi][ci];

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c, dp);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c, dp);

    return dp[ai][bi][ci] = (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    int n = s1.size();
    int m = s2.size();
    int nm = s3.size();
    if (n + m != nm)
        return false;

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(nm + 1, -1)));
    return check(0, 0, 0, s1, s2, s3, dp);
}

// Sub-method 2 --> O(n*m) [Space and time OPTIMIZED]

bool check(int ai, int bi, int ci, string &a, string &b, string &c, vector<vector<int>> &dp)
{
    if (ci == c.size())
        return (ai == a.size() && bi == b.size());
    if (dp[ai][bi] != -1)
        return dp[ai][bi];

    bool af = false, bf = false;
    if (ai < a.size() && c[ci] == a[ai])
        af = check(ai + 1, bi, ci + 1, a, b, c, dp);
    if (bi < b.size() && c[ci] == b[bi])
        bf = check(ai, bi + 1, ci + 1, a, b, c, dp);

    return dp[ai][bi] = (af || bf);
}

bool isInterleave(string s1, string s2, string s3)
{
    int n = s1.size();
    int m = s2.size();
    int nm = s3.size();
    if (n + m != nm)
        return false;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return check(0, 0, 0, s1, s2, s3, dp);
}

// DAY 5 (Maximum Performance of a Team)===========================================================================

#define f first
#define s second
#define mod 1000000007
#define ull unsigned long long
int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency, int k)
{
    vector<pair<int, int>> effspd(n);
    for (int i = 0; i < n; i++)
        effspd[i] = {efficiency[i], speed[i]};
    sort(effspd.rbegin(), effspd.rend()); // Sorting in reverse order

    priority_queue<int> pq;
    ull totalspeed = 0;
    ull maxperf = 0;
    for (int i = 0; i < n; i++)
    {
        int eff = effspd[i].f;
        int spd = effspd[i].s;
        pq.push(-spd); // Making the behaviour as min priority queue

        if (pq.size() > k)
        {
            totalspeed += spd + pq.top();
            pq.pop();
        }
        else
            totalspeed += spd;

        maxperf = max(maxperf, totalspeed * eff);
    }
    return maxperf % mod;
}

// DAY 6 (Longest Consecutive Sequence)============================================================================

int longestConsecutive(vector<int> &nums)
{
    unordered_map<int, int> m;
    int ans = 0;
    for (int x : nums)
    {
        if (m.count(x))
            continue;
        if (m.count(x - 1) && m.count(x + 1)) // Number is being added to the 2 sets (left and right)
        {
            int len = m[x - m[x - 1]] + m[x + m[x + 1]] + 1;
            m[x - m[x - 1]] = len;
            m[x + m[x + 1]] = len;
            m[x] = len;
            ans = max(ans, len);
        }
        else if (m.count(x - 1)) //Number is being added to the left set
        {
            int len = ++m[x - m[x - 1]];
            ans = max(ans, len);
            m[x] = len;
        }
        else if (m.count(x + 1)) // Number is being added to the right set
        {
            int len = ++m[x + m[x + 1]];
            ans = max(ans, len);
            m[x] = len;
        }
        else // Number is making a new set
            ans = max(ans, ++m[x]);
    }
    return ans;
}

// DAY 7 (Min Cost Climbing Stairs)=============================================================

int minCoststairs(int n, vector<int> &cost, vector<int> &dp)
{
    for (int i = n - 1; i >= 0; i--)
    {
        int one = (i + 1 < n) ? dp[i + 1] : 0;
        int two = (i + 2 < n) ? dp[i + 2] : 0;
        dp[i] = min(one, two) + cost[i];
    }
    return min(dp[0], dp[1]);
}

int minCostClimbingStairs(vector<int> &cost)
{
    int n = cost.size();
    vector<int> dp(n + 1, 0);
    return minCoststairs(n, cost, dp);
}

// DAY 8 (Contruct Binary Tree from Preorder and Inorder Traversal)=================================================================

TreeNode *build(int l1, int r1, int l2, int r2, vector<int> &pre, unordered_map<int, int> &m)
{
    if (l1 > r1 || l2 > r2)
        return nullptr;
    if (l2 == r2)
        return new TreeNode(pre[l1], nullptr, nullptr);

    int i = m[pre[l1]];
    TreeNode *root = new TreeNode(pre[l1]);

    int count = (i - l2);

    root->left = build(l1 + 1, l1 + count, l2, i - 1, pre, m);
    root->right = build(l1 + count + 1, r1, i + 1, r2, pre, m);

    return root;
}

TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
{
    unordered_map<int, int> m;
    for (int i = 0; i < inorder.size(); i++)
        m[inorder[i]] = i;
    TreeNode *root = build(0, preorder.size() - 1, 0, inorder.size() - 1, preorder, m);
    return root;
}

// DAY 9 (Jump Game 6)==========================================================================

// APPROACH 1 (Bottom up DP) --> O(n*k)
// TLE

int maxResult(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> dp(n, INT_MIN);
    dp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        for (int j = 1; j <= k && (i + j) < n; j++)
            dp[i] = max(dp[i], dp[i + j] + nums[i]);
    return dp[0];
}

// APPROACH 2 (OPTIMIZED DP (with deque)) --> O(n)
// [Remove the numbers which are surely not gonna contribute in the maximum (the smaller numbers) every time we push the current index in the deque]

int maxResult(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> dp(n, INT_MIN);
    dp[n - 1] = nums[n - 1];

    deque<int> que;
    que.push_back(n - 1);

    for (int i = n - 2; i >= 0; i--)
    {
        if (que.front() - i > k)
            que.pop_front();

        dp[i] = dp[que.front()] + nums[i];

        while (!que.empty() && dp[que.back()] <= dp[i])
            que.pop_back();

        que.push_back(i);
    }
    return dp[0];
}

// DAY 10 (My Calender 1)==================================================================================
class MyCalendar
{
public:
#define f first
#define s second
    set<pair<int, int>> events;
    MyCalendar()
    {
    }

    bool book(int start, int end)
    {
        auto itr = events.lower_bound({start, end});
        if (itr != events.end() && (*itr).f < end)
            return false;
        if (itr != events.begin() && (*--itr).s > start)
            return false;

        events.insert({start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

//  DAY 11 (Stone Game VII)=====================================================================================

// METHOD 1 (Memoized)
int mindiff(int i, int j, int tsum, vector<int> &stones, vector<vector<int>> &dp)
{
    if (i == j)
        return 0;
    if (i + 1 == j)
        return max(stones[i], stones[j]);

    if (dp[i][j] != -1)
        return dp[i][j];

    int left = mindiff(i + 1, j, tsum - stones[i], stones, dp);
    int right = mindiff(i, j - 1, tsum - stones[j], stones, dp);

    return dp[i][j] = max((tsum - stones[i] - left), (tsum - stones[j] - right));
}

int stoneGameVII(vector<int> &stones)
{
    int n = stones.size();
    int tsum = 0;
    for (int x : stones)
        tsum += x;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return mindiff(0, n - 1, tsum, stones, dp);
}

// METHOD 2 (Tabulated)

int stoneGameVII(vector<int> &stones)
{
    int n = stones.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = n - 2; i >= 0; i--)
    {
        int tsum = stones[i];
        for (int j = i + 1; j < n; j++)
        {
            tsum += stones[j];

            int left = tsum - stones[i] - dp[i + 1][j];
            int right = tsum - stones[j] - dp[i][j - 1];

            dp[i][j] = max(left, right);
        }
    }

    return dp[0][n - 1];
}

// DAY 12 (Minimum Number of Refueling Stops)===========================================================================

int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
{
    int n = stations.size();
    priority_queue<int> pq;
    int i = 0;
    int cnt = 0;
    while (startFuel < target)
    {
        while (i < n && stations[i][0] <= startFuel)
            pq.push(stations[i++][1]);

        if (pq.empty())
            return -1;

        startFuel += pq.top();
        cnt++;
        pq.pop();
    }
    if (target > startFuel)
        return -1;
    return cnt;
}

// DAY 13 (Palindrome Pairs)===================================================================================

// APPROACH 1 (Brute Force) --> O(n^2)

bool ispal(string s)
{
    for (int i = 0; i < s.size() / 2; i++)
        if (s[i] != s[s.size() - i - 1])
            return false;
    return true;
}

vector<vector<int>> palindromePairs(vector<string> &words)
{
    int n = words.size();
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                continue;
            if (ispal(words[i] + words[j]))
                ans.push_back({i, j});
        }
    }
    return ans;
}

// APPROACH 2 (OPTIMIZED Using map) --> O(n*m) [n = words.size(), m = words[i][j].size()]

bool ispal(int i, int j, string &s)
{
    while (i < j)
        if (s[i++] != s[j--])
            return false;
    return true;
}

vector<vector<int>> palindromePairs(vector<string> &words)
{
    int n = words.size();

    unordered_map<string, int> m;
    for (int i = 0; i < n; i++)
        m[words[i]] = i;

    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        if (words[i] == "")
        {
            for (int j = 0; j < n; j++)
                if (j != i && ispal(0, words[j].size() - 1, words[j]))
                    ans.push_back({i, j}), ans.push_back({j, i});
        }
        else
        {
            string tmp = words[i];
            reverse(tmp.begin(), tmp.end());
            if (m.count(tmp) && m[tmp] != i)
                ans.push_back({i, m[tmp]});

            for (int j = 1; j < tmp.size(); j++)
            {
                if (ispal(0, j - 1, tmp))
                {
                    string s1 = tmp.substr(j, tmp.size() - j);
                    if (m.count(s1))
                        ans.push_back({i, m[s1]});
                }

                if (ispal(j, tmp.size() - 1, tmp))
                {
                    string s2 = tmp.substr(0, j);
                    if (m.count(s2))
                        ans.push_back({m[s2], i});
                }
            }
        }
    }
    return ans;
}

// DAY 14 (Maximum Units on a Truck)===========================================================================

int maximumUnits(vector<vector<int>> &boxTypes, int truckSize)
{
    sort(boxTypes.begin(), boxTypes.end(), [](auto const &a, auto const &b)
         { return a[1] > b[1]; });
    int ans = 0;
    for (int i = 0; i < boxTypes.size(); i++)
    {
        int boxes = min(boxTypes[i][0], truckSize);
        ans += boxes * boxTypes[i][1];

        truckSize -= boxes;
        if (truckSize == 0)
            break;
    }
    return ans;
}

// DAY 15 (Matchsticks to Square)=========================================================================================

// APPROACH 1 (Brute Force) --> O(4^n)
// TLE

bool dfs(long i, long a, long b, long c, long d, vector<int> &arr)
{
    if (i == arr.size())
    {
        if (a == b && b == c && c == d)
            return true;
        return false;
    }

    return dfs(i + 1, a + arr[i], b, c, d, arr) ||
           dfs(i + 1, a, b + arr[i], c, d, arr) ||
           dfs(i + 1, a, b, c + arr[i], d, arr) ||
           dfs(i + 1, a, b, c, d + arr[i], arr);
}

bool makesquare(vector<int> &matchsticks)
{
    return dfs(0, 0, 0, 0, 0, matchsticks);
}

// APPROACH 2 (Checking all four sides by Target sum approach) --> O(n^3)

bool target_sum(int idx, int len, int sidelen, int vis, int totlens, vector<int> &sticks)
{
    if (totlens == 3)
        return true;
    if (len == sidelen)
        return target_sum(0, 0, sidelen, vis, totlens + 1, sticks);
    if (idx == sticks.size())
        return false;

    for (int i = idx; i < sticks.size(); i++)
    {
        if (!(vis & (1 << i)) && (len + sticks[i] <= sidelen))
        {
            vis ^= (1 << i);
            if (target_sum(i + 1, len + sticks[i], sidelen, vis, totlens, sticks))
                return true;
            vis ^= (1 << i);
        }
    }
    return false;
}

bool makesquare(vector<int> &matchsticks)
{
    int n = matchsticks.size();
    long sum = 0;
    for (int x : matchsticks)
        sum += x;
    if (sum % 4)
        return false;

    int vis = 0;
    return target_sum(0, 0, sum / 4, vis, 0, matchsticks);
}

// DAY 16 (Generate Parenthesis)===================================================================================

void parenthesis(int x, int y, string s, vector<string> &ans)
{
    if (x == 0 && y == 0)
    {
        ans.push_back(s);
        return;
    }
    if (x == -1 || y == -1 || y < x)
        return;

    parenthesis(x - 1, y, s + '(', ans);
    parenthesis(x, y - 1, s + ')', ans);
}

vector<string> generateParenthesis(int n)
{
    vector<string> ans;
    parenthesis(n, n, "", ans);
    return ans;
}

// DAY 17 (Number of Subarrays with Bounded Maximum)=============================================================

int numSubarrayBoundedMax(vector<int> &nums, int left, int right)
{
    long ans = 0;
    int i = 0, j = 0;
    int lasti = -1;
    while (i < nums.size())
    {
        if (nums[i] > right)
        {
            j = i + 1;
            lasti = -1;
        }
        else if (nums[i] >= left && nums[i] <= right)
        {
            ans += (i - j + 1);
            lasti = i;
        }
        else if (lasti != -1)
            ans += (lasti - j + 1);
        i++;
    }
    return ans;
}

// DAY 18 (Range Sum Query - Mutable)======================================================

// APPROACH  -> Using Fenwick Trees
class NumArray
{
public:
    vector<int> nums;
    vector<int> fentree;
    int n;

    void updateFen(int i, int x)
    {
        while (i <= n)
        {
            fentree[i] += x;
            i += (i & -i);
        }
    }

    int Fensum(int i)
    {
        int sum = 0;
        while (i)
        {
            sum += fentree[i];
            i -= (i & -i);
        }
        return sum;
    }

    NumArray(vector<int> &nums)
    {
        this->n = nums.size();
        this->nums = nums;
        this->fentree.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
            updateFen(i, nums[i - 1]);
    }

    void update(int index, int val)
    {
        updateFen(index + 1, (val - nums[index]));
        nums[index] = val;
    }

    int sumRange(int left, int right)
    {
        return Fensum(right + 1) - Fensum(left);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

// DAY 20 (Swim in Rising Water)==============================================================================

// APPROACH 1 (Brute Force DFS) --> O(4^(n^2))

int minans = INT_MAX;
int dfs(int i, int j, int n, int m, int mx, vector<vector<int>> &arr, vector<vector<bool>> &vis)
{
    if (i == n || j == m || i == -1 || j == -1 || vis[i][j])
        return INT_MAX;
    mx = max(mx, arr[i][j]);
    if (i == n - 1 && j == m - 1)
        return mx;

    vis[i][j] = true;

    int d = dfs(i + 1, j, n, m, mx, arr, dp, vis);
    int r = dfs(i, j + 1, n, m, mx, arr, dp, vis);
    int u = dfs(i - 1, j, n, m, mx, arr, dp, vis);
    int l = dfs(i, j - 1, n, m, mx, arr, dp, vis);

    vis[i][j] = false;

    return min({d, r, u, l});
}

int swimInWater(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    return dfs(0, 0, n, m, -1, grid, vis);
}

// APPROACH 2 (Using the given property -> value ranges from (0 to n*n-1)) --> O(n^4)

vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool dfs(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<bool>> &vis, int wlvl)
{
    if (i == -1 || j == -1 | i == n || j == m || grid[i][j] > wlvl || vis[i][j])
        return false;
    if (i == n - 1 && j == m - 1)
        return true;

    vis[i][j] = true;

    for (int d = 0; d < 4; d++)
        if (dfs(i + dir[d][0], j + dir[d][1], n, m, grid, vis, wlvl))
            return true;

    vis[i][j] = true;

    return false;
}

int swimInWater(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    int minans = max({grid[0][0], grid[n - 1][m - 1], 2 * (n - 1)});
    for (int wlvl = minans; wlvl < n * n; wlvl++)
    {
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        if (dfs(0, 0, n, m, grid, vis, wlvl))
            return wlvl;
    }
    return n * n;
}

// APPROACH 2 METHOD 2 (Using Binary Search) --> O(n^2*logn)

vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
bool dfs(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<bool>> &vis, int wlvl)
{
    if (i == -1 || j == -1 | i == n || j == m || grid[i][j] > wlvl || vis[i][j])
        return false;
    if (i == n - 1 && j == m - 1)
        return true;

    vis[i][j] = true;

    for (int d = 0; d < 4; d++)
        if (dfs(i + dir[d][0], j + dir[d][1], n, m, grid, vis, wlvl))
            return true;

    vis[i][j] = true;

    return false;
}

int swimInWater(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();

    int si = max({grid[0][0], grid[n - 1][m - 1], 2 * (n - 1)}), ei = n * n - 1;
    while (si <= ei)
    {
        int wlvl = (si + ei) >> 1;
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        if (dfs(0, 0, n, m, grid, vis, wlvl))
            ei = wlvl - 1;
        else
            si = wlvl + 1;
    }
    return si;
}

// DAY 21 (Pascal's Triangle)=======================================================================================

vector<vector<int>> generate(int numRows)
{
    vector<vector<int>> ans(numRows);
    ans[0].push_back(1);
    for (int i = 0; i < numRows - 1; i++)
    {
        ans[i + 1].assign(i + 2, 0);
        for (int j = 0; j < i + 1; j++)
        {
            ans[i + 1][j] += ans[i][j];
            ans[i + 1][j + 1] += ans[i][j];
        }
    }
    return ans;
}

// DAY 22 (Number of Matching Subsequences)==================================================================================

// APPROACH 1 (Brute Force -- Compare all words with s in O(n)) --> O(n*m*x) [n = s.size(), m = words.size(), x = words[i].size()]

bool isMatched(string &a, string &b)
{
    if (b.size() > a.size())
        return false;
    int j = 0;
    for (int i = 0; i < a.size() && j < b.size(); i++)
        if (a[i] == b[j])
            j++;
    return (j == b.size());
}

int numMatchingSubseq(string s, vector<string> &words)
{
    int ans = 0;
    for (string word : words)
        if (isMatched(s, word))
            ans++;
    return ans;
}

// APPROACH 2 (Optimized Brute Force --> Compare all words with the same character of words[i], in s) --> < O(n*m*x)

vector<vector<int>> chari;
bool isMatched(string &word)
{
    int lasti = -1;
    for (char c : word)
    {
        if (chari[c - 'a'].empty())
            return false;
        bool found = false;
        for (int i : chari[c - 'a'])
        {
            if (i > lasti)
            {
                lasti = i;
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int numMatchingSubseq(string s, vector<string> &words)
{
    chari.resize(26);
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
        chari[s[i] - 'a'].push_back(i);

    for (string word : words)
        if (isMatched(word))
            ans++;
    return ans;
}

// DAY 23 (Reverse Linked List 2)======================================================================================

ListNode* reverseBetween(ListNode* head, int left, int right) 
{
    int pos = 1;
    ListNode* curr = nullptr, *prev = nullptr, *forw = curr, *ptrleft = nullptr;
    ListNode *itr = head, *last = nullptr;
    while(itr)
    {
        if(pos == left && !ptrleft)
        {
            ptrleft = itr;
            curr = itr;
        }
        else if(!ptrleft)
            last = itr;
        
        if(curr)
        {
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
        }
        
        if(pos == right)
            break;
        
        if(ptrleft)
            itr = curr;
        else
            itr = itr->next;
        pos++;
    }
    ptrleft->next = curr;
    if(last)
        last->next = prev;
    
    return last? head : prev;
}