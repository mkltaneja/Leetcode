
// DAY 2 (Two Sum)=========================================================================

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.count(target - nums[i]))
            return {m[target - nums[i]], i};
        m[nums[i]] = i;
    }
    return {};
}

// DAY 3 (Subsets 2)===============================================================================================

void subsets(int i, vector<int> &nums, set<vector<int>> &st, vector<vector<int>> &ans, vector<int> ss)
{
    if (i == nums.size())
    {
        if (!st.count(ss))
        {
            ans.push_back(ss);
            st.insert(ss);
        }
        return;
    }
    subsets(i + 1, nums, st, ans, ss);
    ss.push_back(nums[i]);
    subsets(i + 1, nums, st, ans, ss);
    ss.pop_back();
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    vector<vector<int>> ans;
    subsets(0, nums, st, ans, {});
    return ans;
}

// DAY 4 (Path Sum 2)================================================================================

void dfs(TreeNode *node, int sum, int target, vector<int> &curr, vector<vector<int>> &ans)
{
    if (!node)
        return;

    curr.push_back(node->val);
    sum += node->val;

    if (!node->left && !node->right && sum == target)
        ans.push_back(curr);

    dfs(node->left, sum, target, curr, ans);
    dfs(node->right, sum, target, curr, ans);

    curr.pop_back();
    sum -= node->val;
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<vector<int>> ans;
    vector<int> curr;
    dfs(root, 0, targetSum, curr, ans);
    return ans;
}

// DAY 6 (N - ary tree Level Order Traversal)===============================================================================
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        if (!root)
            return {};

        vector<vector<int>> ans;

        queue<Node *> que;
        que.push(root);

        while (!que.empty())
        {
            int sz = que.size();
            vector<int> lvl;
            while (sz--)
            {
                Node *node = que.front();
                que.pop();
                lvl.push_back(node->val);
                for (Node *child : node->children)
                    que.push(child);
            }
            ans.push_back(lvl);
        }
        return ans;
    }
};

// DAY 7 (Palindromic Partitioning 2)=======================================================================

int minCut(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n, false));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (gap == 0)
                ispal[i][j] = true;
            else if (s[i] == s[j] && gap == 1)
                ispal[i][j] = true;
            else if (s[i] == s[j] && ispal[i + 1][j - 1])
                ispal[i][j] = true;
        }
    }

    vector<int> dp(n);
    for (int i = 0; i < n; i++)
        dp[i] = i;

    for (int i = 1; i < n; i++)
    {
        if (ispal[0][i])
        {
            dp[i] = 0;
            continue;
        }
        for (int j = 1; j <= i; j++)
            if (ispal[j][i])
                dp[i] = min(dp[i], dp[j - 1] + 1);
    }
    return dp[n - 1];
}

// DAY 8 (Rank Transform of a Matrix)==============================================================================

#define f first
#define s second

int findpar(int x, vector<int> &par)
{
    if (par[x] == x)
        return x;
    return par[x] = findpar(par[x], par);
}

vector<vector<int>> matrixRankTransform(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    map<int, vector<pair<int, int>>> mat;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[matrix[i][j]].push_back({i, j});

    vector<int> rank(n + m, 0);
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (auto p : mat)
    {
        vector<int> par(n + m);
        for (int i = 0; i < n + m; i++)
            par[i] = i;

        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pi = findpar(i, par), pj = findpar(j + n, par);
            par[pi] = pj;
            rank[pj] = max(rank[pi], rank[pj]);
        }
        vector<int> curr = rank;
        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pij = findpar(i, par);
            ans[i][j] = rank[pij] + 1;
            curr[i] = rank[pij] + 1;
            curr[j + n] = rank[pij] + 1;
        }
        rank = curr;
    }
    return ans;
}