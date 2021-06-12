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