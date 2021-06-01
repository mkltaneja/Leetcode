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
    // Note:- This can not be done with Morris postorder, as Morris's method doesn't use the extra                 space. Instead we use the jugaad of Morris method, where we interchange the "left" and               "right". But here extra space (as array) will be required for reversing the array
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> ans;
        while (root)
        {
            TreeNode *rootp1 = root->right;
            if (!rootp1)
            {
                ans.push_back(root->val);
                root = root->left;
            }
            else
            {
                while (rootp1->left && rootp1->left != root)
                    rootp1 = rootp1->left;
                if (rootp1->left == nullptr)
                {
                    ans.push_back(root->val);
                    rootp1->left = root;
                    root = root->right;
                }
                else if (rootp1->left == root)
                {
                    rootp1->left = nullptr;
                    root = root->left;
                }
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};