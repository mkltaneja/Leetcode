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
    long long kthLargestLevelSum(TreeNode* root, int k) 
    {
        priority_queue<ll, vector<ll>, greater<ll>> pq;
        queue<TreeNode*> que;
        que.push(root);
        while(!que.empty())
        {
            int sz = que.size();
            ll sum = 0;
            while(sz--)
            {
                TreeNode* node = que.front();
                que.pop();
                
                sum += (ll)node->val;
                if(node->left) que.push(node->left);
                if(node->right) que.push(node->right);
            }
            pq.push(sum);
            if(pq.size() > k) pq.pop();
        }
        
        return pq.size() < k? -1 : pq.top();
    }
};
