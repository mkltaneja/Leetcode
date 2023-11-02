
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

// DAY 2 (2265. Count Nodes Equal to Average of Subtree)=================================================================================================================

int ans = 0;

pair<int,int> dfs(TreeNode* node)
{
    if(!node) return {0, 0};

    pair<int,int> lAns = dfs(node->left);
    pair<int,int> rAns = dfs(node->right);

    int sum = lAns.first + rAns.first + node->val;
    int tot = lAns.second + rAns.second + 1;
    
    ans += (sum / tot) == node->val;

    return {sum, tot};
}

int averageOfSubtree(TreeNode* root) 
{
    dfs(root);
    return ans;
}
