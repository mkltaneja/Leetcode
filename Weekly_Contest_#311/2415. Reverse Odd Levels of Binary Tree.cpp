
TreeNode* reverseOddLevels(TreeNode* root) 
{
    queue<TreeNode*> que;
    que.push(root);

    int lvl = 0;
    while(!que.empty())
    {
        int sz = que.size();
        vector<TreeNode*> st;
        int l = 0, r = sz-1;
        while(sz--)
        {
            TreeNode* node = que.front();
            st.push_back(node);
            que.pop();

            if(!node->left) continue;

            que.push(node->left);
            que.push(node->right);
        }

        if(lvl&1)
            while(l < r)
                swap(st[l++]->val, st[r--]->val);

        lvl++;
    }

    return root;
}
