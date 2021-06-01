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
class Solution
{
public:
    // Morris preorder traversal (iterative traversal)
    // Time complexity --> O(3*n)
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        while (root)
        {
            if (root->left == nullptr)
            {
                ans.push_back(root->val);
                root = root->right;
            }
            else
            {
                TreeNode *rootp1 = root->left;
                while (rootp1->right && rootp1->right != root)
                    rootp1 = rootp1->right;
                if (rootp1->right == nullptr) // First time encountered
                {
                    rootp1->right = root;
                    ans.push_back(root->val);
                    root = root->left;
                }
                else // 2nd time encountered
                {
                    // UNDO the operation of joining the rootp1->right to root
                    rootp1->right = nullptr;
                    root = root->right;
                }
            }
        }
        return ans;
    }
};