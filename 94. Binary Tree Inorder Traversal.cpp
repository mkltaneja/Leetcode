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
    // Morris inorder traversal (iterative traversal)
    vector<int> inorderTraversal(TreeNode *root)
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
                if (rootp1->right == nullptr)
                {
                    rootp1->right = root;
                    root = root->left;
                }
                else
                {
                    ans.push_back(root->val);
                    rootp1->right = nullptr;
                    root = root->right;
                }
            }
        }
        return ans;
    }
};