
// DAY 1 (501. Find Mode in Binary Search Tree)=======================================================================================

vector<int> ans;
int maxCnt = 0, cnt = 0, prev = INT_MIN;

void inorder(TreeNode* node)
{
    if(!node) return;

    inorder(node->left);

    if(node->val == prev) cnt++;
    else cnt = 1;
    if(cnt >= maxCnt)
    {
        if(cnt > maxCnt)
            ans.clear();
        ans.push_back(node->val);
        maxCnt = cnt;
    }
    prev = node->val;

    inorder(node->right);
}

vector<int> findMode(TreeNode* root)
{
    inorder(root);
    return ans;
}
