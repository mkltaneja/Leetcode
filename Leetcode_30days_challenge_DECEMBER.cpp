// DAY 1 (Maximum Depth of Binary Tree)==============================================================

// METHOD 1 (void type)
void maxdepth(TreeNode *node, int depth, int &maxans)
{
    if (node == nullptr)
        return;
    maxans = max(maxans, depth);
    maxdepth(node->left, depth + 1, maxans);
    maxdepth(node->right, depth + 1, maxans);
}

int maxDepth(TreeNode *root)
{
    int depth = 0;
    maxdepth(root, 1, depth);
    return depth;
}

// METHOD 2 (int type)

int maxdepth(TreeNode *node, int depth)
{
    if (node == nullptr)
        return depth;
    return max(maxdepth(node->left, depth), maxdepth(node->right, depth)) + 1;
}

int maxDepth(TreeNode *root)
{
    return maxdepth(root, 0);
}

// DAY 2 (Linked List Random Node)=========================================================

vector<int> vals;
Solution(ListNode *head)
{
    while (head)
    {
        vals.push_back(head->val);
        head = head->next;
    }
}

/** Returns a random node's value. */
int getRandom()
{
    return vals[rand() % vals.size()];
}

// DAY 3 (Increasing Order Search Tree)======================================================

TreeNode *head = new TreeNode(-1);
TreeNode *temp = head;

void inorder(TreeNode *node)
{
    if (!node)
        return;
    inorder(node->left);
    temp->right = new TreeNode(node->val);
    temp = temp->right;
    inorder(node->right);
}

TreeNode *increasingBST(TreeNode *root)
{
    inorder(root);
    return head->right;
}

// DAY 4 (The kth Factor of n)===========================================================

int kthFactor(int n, int k)
{
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
            k--;
        if (k == 0)
            return i;
    }
    return -1;
}

// DAY 5 (Can Place Flowers)========================================================

// METHOD 1
bool canPlaceFlowers(vector<int> &flowerbed, int n)
{
    int m = flowerbed.size();
    vector<bool> isplaced(m, false);
    for (int i = 0; i < m; i++)
        if (flowerbed[i])
            isplaced[i] = true;

    int available = 0;
    if (!isplaced[0] && !isplaced[1])
    {
        isplaced[0] = true;
        available++;
    }
    if (!isplaced[m - 1] && !isplaced[m - 2])
    {
        isplaced[m - 1] = true;
        available++;
    }
    for (int i = 1; i < m - 1; i++)
    {
        if (!isplaced[i] && !isplaced[i - 1] && !isplaced[i + 1])
        {
            isplaced[i++] = true;
            available++;
        }
    }

    return available >= n;
}

// METHOD 2

bool canPlaceFlowers(vector<int> &flowerbed, int n)
{
    if (n == 0)
        return true;
    int m = flowerbed.size();
    int available = 0;
    for (int i = 0; i < m; i++)
    {
        if (flowerbed[i] == 1)
            continue;
        bool front = (i == 0 || flowerbed[i - 1] == 0);
        bool behind = (i == m - 1 || flowerbed[i + 1] == 0);

        if (front && behind)
        {
            flowerbed[i] = 1;
            available++;
        }
        if (available >= n)
            return true;
    }
    return false;
}