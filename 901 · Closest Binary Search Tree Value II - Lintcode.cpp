
queue<int> que;
void inorder(TreeNode *node, double tar, int k)
{
    if (!node)
        return;

    inorder(node->left, tar, k);
    if (que.size() < k || abs(tar - node->val) < abs(que.front() - tar))
    {
        que.push(node->val);
        if (que.size() > k)
            que.pop();
    }
    else
        return;
    inorder(node->right, tar, k);
}

vector<int> closestKValues(TreeNode *root, double target, int k)
{
    vector<int> ans;
    inorder(root, target, k);
    while (!que.empty())
    {
        ans.push_back(que.front());
        que.pop();
    }
    return ans;
}