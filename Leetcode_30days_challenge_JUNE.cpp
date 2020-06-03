//DAY 1(Invert Binary Tree)

// Method 1 (by saving the right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode *r = root->right;
    root->right = invertTree(root->left);
    root->left = invertTree(r);

    return root;
}

///////////////OR//////////////
// Method 2 (by swaping the left and right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    invertTree(root->left);
    invertTree(root->right);
    swap(root->left, root->right);

    return root;
}

//DAY 2(Delete Node in a Linked List)===============================================

void deleteNode(ListNode *&node)
{
    node->val = node->next->val;
    node->next = node->next->next;
}

///////////////OR///////////////

void deleteNode(ListNode *&node)
{
    *node = *(node->next);
}

//DAY 3()===============================================================================

// (by custom comparator)
static bool sort_bydiff(vector<int> &a, vector<int> &b)
{
    return (a[0] - a[1]) < (b[0] - b[1]);
}

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), sort_bydiff);

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}
