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

/////////////OR//////////////////

// (by LAMBDA OPERATION custom operator)

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), [](const vector<int> &a, const vector<int> &b) {
        return (a[0] - a[1]) < b[0] - b[1];
    });

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}

//DAY 4(Reverse String)==============================================================================

// (using swap function)
void reverseString(vector<char> &s)
{
    for (int i = 0; i < s.size() / 2; i++)
        swap(s[i], s[s.size() - i - 1]);
}

////////////////OR/////////////////
// (using reverse function)
void reverseString(vector<char> &s)
{
    reverse(s.begin(), s.end());
}

///////////////OR/////////////////
// (using 2 pointer approach)
void reverseString(vector<char> &s)
{
    int l = 0, h = s.size() - 1;
    while (l < h)
    {
        char c = s[l];
        s[l] = s[h];
        s[h] = c;
        l++, h--;
    }
}