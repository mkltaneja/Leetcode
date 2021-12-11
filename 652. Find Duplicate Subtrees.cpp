
vector<TreeNode *> ans;
unordered_map<string, int> seen;

string encodeAndCheck(TreeNode *node)
{
    if (!node)
        return "#";

    string ltree = encodeAndCheck(node->left);
    string rtree = encodeAndCheck(node->right);

    string curr = "(" + ltree + to_string(node->val) + rtree + ")";

    if (++seen[curr] == 2)
        ans.push_back(node);

    return curr;
}

vector<TreeNode *> findDuplicateSubtrees(TreeNode *root)
{
    encodeAndCheck(root);
    return ans;
}