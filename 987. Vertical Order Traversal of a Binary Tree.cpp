
// APPROACH 1 (Using map for dynamically adding the vertical level; and multiset for automatically sorting the same horizotal and vertical level nodes)

#define f first
#define s second
vector<vector<int>> verticalTraversal(TreeNode *root)
{
    map<int, vector<int>> mp;
    queue<pair<TreeNode *, int>> que;
    que.push({root, 0});
    mp[0].push_back(root->val);
    while (!que.empty())
    {
        int sz = que.size();
        unordered_map<int, multiset<int>> tmp;
        while (sz--)
        {
            auto top = que.front();
            que.pop();
            if (top.f->left)
            {
                que.push({top.f->left, top.s - 1});
                tmp[top.s - 1].insert(top.f->left->val);
            }
            if (top.f->right)
            {
                que.push({top.f->right, top.s + 1});
                tmp[top.s + 1].insert(top.f->right->val);
            }
        }
        for (auto p : tmp)
            for (int x : p.s)
                mp[p.f].push_back(x);
    }
    vector<vector<int>> ans;
    for (auto p : mp)
        ans.push_back(p.s);

    return ans;
}

// APPROACH 2 (Precalculate leftmost and rightmost vertical level, make the array of that size and do BFS) [OPTIMIZED]

void dfs(TreeNode *node, int width, int &lm, int &rm)
{
    if (!node)
        return;
    lm = min(lm, width);
    rm = max(rm, width);
    dfs(node->left, width - 1, lm, rm);
    dfs(node->right, width + 1, lm, rm);
}

void bfs(TreeNode *node, vector<vector<int>> &ans, int lm, int rm)
{
    queue<pair<TreeNode *, int>> que;
    que.push({node, 0});
    ans[-lm].push_back(node->val);
    while (!que.empty())
    {
        vector<vector<int>> tmp(ans.size(), vector<int>());
        int sz = que.size();
        while (sz--)
        {
            auto tp = que.front();
            que.pop();
            if (tp.first->left)
            {
                que.push({tp.first->left, tp.second - 1});
                tmp[-lm + (tp.second - 1)].push_back(tp.first->left->val);
            }
            if (tp.first->right)
            {
                que.push({tp.first->right, tp.second + 1});
                tmp[-lm + (tp.second + 1)].push_back(tp.first->right->val);
            }
        }
        for (int i = 0; i < tmp.size(); i++)
        {
            sort(tmp[i].begin(), tmp[i].end());
            for (int j = 0; j < tmp[i].size(); j++)
                ans[i].push_back(tmp[i][j]);
        }
    }
}

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    int leftmost = INT_MAX, rightmost = INT_MIN;
    dfs(root, 0, leftmost, rightmost);
    // cout<<leftmost<<" "<<rightmost<<endl;
    vector<vector<int>> ans(rightmost - leftmost + 1, vector<int>());
    bfs(root, ans, leftmost, rightmost);
    return ans;
}