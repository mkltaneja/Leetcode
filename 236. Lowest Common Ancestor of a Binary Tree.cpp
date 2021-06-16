
// APPROACH 1 (Standard Approach) --> O(n)

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (!root)
        return nullptr;

    if (root->val == p->val || root->val == q->val)
        return root;

    TreeNode *lans = lowestCommonAncestor(root->left, p, q);
    TreeNode *rans = lowestCommonAncestor(root->right, p, q);

    if (!lans && !rans)
        return nullptr;
    if (lans && rans)
        return root;
    return (lans) ? lans : rans;
}

// APPROACH 2 (Preprocessing the parent and level of every node) --> O(n) (with extra stace)
// [Useful in CP questions, where we are asked to find LCA more than 1 time]

void preProcess(TreeNode *node, unordered_map<TreeNode *, TreeNode *> &par, unordered_map<TreeNode *, int> &lvl)
{
    queue<TreeNode *> que;
    que.push(node);
    par[node] = nullptr;
    lvl[node] = 0;
    int level = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            TreeNode *top = que.front();
            que.pop();
            if (top->left)
            {
                par[top->left] = top;
                lvl[top->left] = level + 1;
                que.push(top->left);
            }
            if (top->right)
            {
                par[top->right] = top;
                lvl[top->right] = level + 1;
                que.push(top->right);
            }
        }
        level++;
    }
}

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    unordered_map<TreeNode *, TreeNode *> par;
    unordered_map<TreeNode *, int> level;
    preProcess(root, par, level);

    int lvlp = level[p];
    int lvlq = level[q];
    while (lvlp > lvlq)
    {
        p = par[p];
        lvlp--;
    }
    while (lvlq > lvlp)
    {
        q = par[q];
        lvlq--;
    }

    while (p != q)
    {
        p = par[p];
        q = par[q];
    }
    return p;
}