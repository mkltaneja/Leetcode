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

// DAY 6 (Populating Next Right Pointers in Each Node II)====================================================================

void leveloder(Node *node)
{
    if (node == nullptr)
        return;
    queue<Node *> que;
    que.push(node);

    while (!que.empty())
    {
        int size = que.size();
        while (size--)
        {
            Node *prev = que.front();
            que.pop();
            if (size > 0)
                prev->next = que.front();
            else
                prev->next = nullptr;
            if (prev->left)
                que.push(prev->left);
            if (prev->right)
                que.push(prev->right);
        }
    }
}

Node *connect(Node *root)
{
    leveloder(root);
    return root;
}

// DAY 7 (Spiral Matrix 2)======================================================================

// METHOD 1
vector<vector<int>> generateMatrix(int n)
{
    int d = 0;
    int sn = 0, sm = 0, en = n - 1, em = n - 1;
    int x = 1;
    int i = 0, j = 0;
    vector<vector<int>> mat(n, vector<int>(n));

    while (x <= n * n)
    {
        mat[i][j] = x;
        // cout<<x<<" ";
        if (d == 0)
        {
            x++;
            j++;
            if (j == em)
            {
                d = (d + 1) % 4;
                sn++;
            }
        }
        else if (d == 1)
        {
            x++;
            i++;
            if (i == en)
            {
                d = (d + 1) % 4;
                em--;
            }
        }
        else if (d == 2)
        {
            x++;
            j--;
            if (j == sm)
            {
                d = (d + 1) % 4;
                en--;
            }
        }
        else if (d == 3)
        {
            x++;
            i--;
            if (i == sn)
            {
                d = (d + 1) % 4;
                sm++;
            }
        }
    }
    return mat;
}

// METHOD 2 (CONCISE)
vector<vector<int>> generateMatrix(int n)
{
    int sn = 0, sm = 0, en = n - 1, em = n - 1;
    int x = 1;
    vector<vector<int>> mat(n, vector<int>(n));

    while (x <= n * n)
    {
        for (int j = sm; j <= em; j++)
            mat[sn][j] = x++;
        sn++;
        for (int i = sn; i <= en; i++)
            mat[i][em] = x++;
        em--;
        for (int j = em; j >= sm; j--)
            mat[en][j] = x++;
        en--;
        for (int i = en; i >= sn; i--)
            mat[i][sm] = x++;
        sm++;
    }
    return mat;
}

// DAY 8 (Pairs of Songs With Total Durations Divisible by 60)=================================================================

// METHOD 1 (using unordered_map)
int numPairsDivisibleBy60(vector<int> &time)
{
    unordered_map<int, int> m;
    int pairs = 0;
    for (int i = 0; i < time.size(); i++)
    {
        int x = 60 - (time[i] % 60);
        if (x == 60)
            pairs += m[0];
        if (m.find(x) != m.end())
            pairs += m[x];
        m[time[i] % 60]++;
    }

    return pairs;
}

// METHOD 2 (using vector)
int numPairsDivisibleBy60(vector<int> &time)
{
    vector<int> v(60, 0);
    int pairs = 0;
    for (int i = 0; i < time.size(); i++)
    {
        int x = 60 - (time[i] % 60);
        if (x == 60)
            pairs += v[0];
        else
            pairs += v[x];
        v[time[i] % 60]++;
    }

    return pairs;
}

// DAY 9 (Binary Search Tree Iterator)=========================================================

// METHOD 1 (Using vector)
vector<int> vals;
int i = 0;

void inoder(TreeNode *node)
{
    if (!node)
        return;
    inoder(node->left);
    vals.push_back(node->val);
    inoder(node->right);
}
BSTIterator(TreeNode *root)
{
    inoder(root);
}

int next()
{
    return vals[i++];
}

bool hasNext()
{
    return i < vals.size();
}

// METHOD 2 (Using queue)===============================================
queue<int> vals;

void inoder(TreeNode *node)
{
    if (!node)
        return;
    inoder(node->left);
    vals.push(node->val);
    inoder(node->right);
}
BSTIterator(TreeNode *root)
{
    inoder(root);
}

int next()
{
    int top = vals.front();
    vals.pop();
    return top;
}

bool hasNext()
{
    return vals.size() > 0;
}

// METHOD 3 (Using stack) --> Space OPTIMIZED (O(height of tree))
stack<TreeNode *> vals;

void lefts(TreeNode *node)
{
    while (node)
    {
        vals.push(node);
        node = node->left;
    }
}
BSTIterator(TreeNode *root)
{
    lefts(root);
}

int next()
{
    TreeNode *front = vals.top();
    vals.pop();
    if (front->right)
        lefts(front->right);
    return front->val;
}

bool hasNext()
{
    return vals.size() > 0;
}

// DAY 10 (Valid Mountain Array)======================================

// METHOD 1
bool validMountainArray(vector<int> &arr)
{
    int n = arr.size();
    if (n < 3)
        return false;
    int peakx = INT_MIN;
    int peaki = -1;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > peakx)
        {
            peakx = arr[i];
            peaki = i;
        }
    }
    if (peaki == 0 || peaki == n - 1)
        return false;
    for (int i = peaki - 1; i >= 0; i--)
        if (arr[i + 1] - arr[i] <= 0)
            return false;
    for (int i = peaki + 1; i < n; i++)
        if (arr[i - 1] - arr[i] <= 0)
            return false;

    return true;
}

// METHOD 2 (OPTIMIZED)
bool validMountainArray(vector<int> &arr)
{
    int n = arr.size();
    if (n < 3)
        return false;
    bool up = false, down = false;
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] == arr[i + 1])
            return false;
        if (arr[i] < arr[i + 1])
        {
            if (!down)
                up = true;
            else
                return false;
        }
        else
        {
            if (up)
                down = true;
            else
                return false;
        }
    }

    return up && down;
}

// DAY 11 (Remove Duplicates from Sorted Array II)========================================================

int removeDuplicates(vector<int> &nums)
{
    if (nums.size() <= 2)
        return nums.size();
    int slow = 2, fast = 2;
    while (fast < nums.size())
    {
        if (nums[slow - 2] != nums[fast])
            nums[slow++] = nums[fast];
        fast++;
    }
    return slow;
}

// DAY 12 (Smallest Subtree with all the Deepest Nodes)================================================

// METHOD 1 (by finding LCA of two most farthest and deepest nodes)
unordered_map<int, TreeNode *> mf, ml;

int levelorder(TreeNode *node)
{
    queue<TreeNode *> que;
    que.push(node);
    int level = 0;

    while (!que.empty())
    {
        int size = que.size();
        while (size--)
        {
            TreeNode *top = que.front();
            que.pop();
            if (mf.find(level) == mf.end())
                mf[level] = top;
            ml[level] = top;
            if (top->left)
                que.push(top->left);
            if (top->right)
                que.push(top->right);
        }
        level++;
    }
    return --level;
}

vector<TreeNode *> RootToNodePath(TreeNode *node, TreeNode *tar)
{
    if (!node)
        return {};

    if (node->val == tar->val)
        return {node};

    vector<TreeNode *> left = RootToNodePath(node->left, tar);
    if (left.size() > 0)
    {
        left.push_back(node);
        return left;
    }

    vector<TreeNode *> right = RootToNodePath(node->right, tar);
    if (right.size() > 0)
    {
        right.push_back(node);
        return right;
    }

    return {};
}

TreeNode *subtreeWithAllDeepest(TreeNode *root)
{
    int maxdepth = levelorder(root);
    TreeNode *leftmost = mf[maxdepth];
    TreeNode *rightmost = ml[maxdepth];
    cout << leftmost->val << ", " << rightmost->val << endl;

    vector<TreeNode *> lmp = RootToNodePath(root, leftmost);
    vector<TreeNode *> rmp = RootToNodePath(root, rightmost);
    for (int i = 0; i < lmp.size(); i++)
        cout << lmp[i]->val << " ";
    cout << endl;
    for (int i = 0; i < rmp.size(); i++)
        cout << rmp[i]->val << " ";

    int i = 0, j = 0;
    while (lmp[i]->val != rmp[j]->val)
        i++, j++;
    return lmp[i];
}

// METHOD 2 (Concise and OPTIMIZED(space and time BOTH))===============================================

int getHeight(TreeNode *node)
{
    if (!node)
        return 0;
    return max(getHeight(node->left), getHeight(node->right)) + 1;
}

TreeNode *subtreeWithAllDeepest(TreeNode *root)
{
    // if(!node)
    //     return null;
    int leftheight = getHeight(root->left);
    int rightheight = getHeight(root->right);

    if (leftheight == rightheight)
        return root;
    else if (leftheight > rightheight)
        return subtreeWithAllDeepest(root->left);
    else
        return subtreeWithAllDeepest(root->right);
}

// DAY 15 ()=====================================================

// METHOD 1 --> O(n*logn)
vector<int> sortedSquares(vector<int> &nums)
{
    int n = nums.size();
    vector<int> squares(n);
    for (int i = 0; i < n; i++)
        squares[i] = nums[i] * nums[i];
    sort(squares.begin(), squares.end());
    return squares;
}