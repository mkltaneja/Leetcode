// DAY 1 (Array Nesting)=============================================================================

int arrayNesting(vector<int> &nums)
{
    int maxcycle = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        int size = 0, j = i;
        while (nums[j] != -1)
        {
            int nxt = nums[j];
            nums[j] = -1;
            j = nxt;
            size++;
        }
        maxcycle = max(maxcycle, size);
    }
    return maxcycle;
}

// DAY 2 (Unique Binary Search Trees 2)=========================================================================

vector<TreeNode *> makeTree(int st, int end, vector<vector<vector<TreeNode *>>> &dp)
{
    if (st > end)
        return {nullptr};
    if (st == end)
        return dp[st][end] = {new TreeNode(st)};
    if (!dp[st][end].empty())
        return dp[st][end];

    vector<TreeNode *> curr;
    for (int x = st; x <= end; x++)
    {
        vector<TreeNode *> left = makeTree(st, x - 1, dp);
        vector<TreeNode *> right = makeTree(x + 1, end, dp);
        for (TreeNode *l : left)
            for (TreeNode *r : right)
                curr.push_back(new TreeNode(x, l, r));
    }
    return dp[st][end] = curr;
}

vector<TreeNode *> generateTrees(int n)
{
    vector<vector<vector<TreeNode *>>> dp(n + 1, vector<vector<TreeNode *>>(n + 1));
    return makeTree(1, n, dp);
}

// DAY 3 (Erect The Fence)=============================================================================

int crossProduct(vector<int> &a, vector<int> &b, vector<int> &c)
{
    // CROSS PRODUCT OF AB and AC --> x1*y2 - x2*y1
    return ((b[0] - a[0]) * (c[1] - a[1]) - (c[0] - a[0]) * (b[1] - a[1]));
}

vector<vector<int>> outerTrees(vector<vector<int>> &trees)
{
    int n = trees.size();
    if (n <= 3)
        return trees;
    sort(trees.begin(), trees.end(), [](auto const &a, auto const &b)
         { return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });

    vector<vector<int>> upper;
    upper.push_back(trees[0]);
    upper.push_back(trees[1]);
    for (int i = 2; i < n; i++)
    {
        int sz = upper.size();
        while (sz >= 2 && crossProduct(upper[sz - 2], upper[sz - 1], trees[i]) > 0)
        {
            upper.pop_back();
            sz--;
        }
        upper.push_back(trees[i]);
    }

    vector<vector<int>> lower;
    lower.push_back(trees[n - 1]);
    lower.push_back(trees[n - 2]);
    for (int i = n - 3; i >= 0; i--)
    {
        int sz = lower.size();
        while (sz >= 2 && crossProduct(lower[sz - 2], lower[sz - 1], trees[i]) > 0)
        {
            lower.pop_back();
            sz--;
        }
        lower.push_back(trees[i]);
    }

    upper.pop_back();
    lower.pop_back();

    for (auto v : lower)
        upper.push_back(v);

    sort(upper.begin(), upper.end());
    upper.erase(unique(upper.begin(), upper.end()), upper.end());

    return upper;
}

// DAY 4 (Sum of Distances in Tree)===========================================================================

vector<int> cnt, ans;
void dfs1(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            dfs1(v, u, gp);
            cnt[u] += cnt[v];
            ans[u] += ans[v] + cnt[v];
        }
    }
}
void dfs2(int u, int p, vector<vector<int>> &gp)
{
    for (int v : gp[u])
    {
        if (v != p)
        {
            ans[v] = ans[u] - cnt[v] + (gp.size() - cnt[v]);
            dfs2(v, u, gp);
        }
    }
}

vector<int> sumOfDistancesInTree(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(n);
    for (auto e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }
    cnt.resize(n, 1), ans.resize(n, 0);
    dfs1(0, -1, gp);
    dfs2(0, -1, gp);

    return ans;
}

// DAY 5 (Orderly Queue)===================================================================

string orderlyQueue(string s, int k)
{
    if (k > 1)
    {
        sort(s.begin(), s.end());
        return s;
    }
    char minc = 'z';
    for (char c : s)
        minc = min(minc, c);
    string ans = s;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == minc)
        {
            string x = s.substr(i, s.size()) + s.substr(0, i);
            if (x < ans)
                ans = x;
        }
    }
    return ans;
}

// DAY 6 (Slowest Key)==================================================================================

char slowestKey(vector<int> &releaseTimes, string keysPressed)
{
    char ans = NULL;
    int maxdur = 0;
    for (int i = 0; i < releaseTimes.size(); i++)
    {
        int dur = releaseTimes[i] - (i ? releaseTimes[i - 1] : 0);
        if (ans == NULL || dur > maxdur)
        {
            ans = keysPressed[i];
            maxdur = dur;
        }
        else if (dur == maxdur && keysPressed[i] > ans)
            ans = keysPressed[i];
    }
    return ans;
}

// DAY 7 (Reverse linked List)=================================================================================

ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr, *curr = head, *forw = head;
    while (curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}