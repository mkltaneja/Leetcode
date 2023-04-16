/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    TreeNode* replaceValueInTree(TreeNode* root) 
    {
        root->val = 0;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty())
        {
            int sz = que.size();
            ll sum = 0;
            vector<pair<TreeNode*, ll>> nodes;
            while(sz--)
            {
                TreeNode* node = que.front();
                que.pop();
                
                ll tot = (node->left? node->left->val : 0) + (node->right? node->right->val : 0);
                sum += tot;
                if(node->left)
                {
                    nodes.push_back({node->left, tot});
                    que.push(node->left);
                }
                if(node->right)
                {
                    nodes.push_back({node->right, tot});
                    que.push(node->right);
                }
            }
            
            for(auto p : nodes)
            {
                p.f->val = sum - p.s;
            }
        }
        
        return root;
    }
};
