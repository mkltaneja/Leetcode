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

// DAY 13 (Burst Baloons)===================================================================

// METHOD 1 (Recursion)
// TLE

int BurstBaloons(int st, int end, vector<int> &arr)
{
    int leftcost = (st == 0) ? 1 : arr[st - 1];
    int rightcost = (end == arr.size() - 1) ? 1 : arr[end + 1];

    int maxans = 0;
    for (int cut = st; cut <= end; cut++)
    {
        int leftans = (cut == st) ? 0 : BurstBaloons(st, cut - 1, arr);
        int rightans = (cut == end) ? 0 : BurstBaloons(cut + 1, end, arr);

        int myans = leftans + leftcost * arr[cut] * rightcost + rightans;
        maxans = max(maxans, myans);
    }

    return maxans;
}

int maxCoins(vector<int> &nums)
{
    return BurstBaloons(0, nums.size() - 1, nums);
}

// METHOD 2 (Memoized)

int BurstBaloons(int st, int end, vector<int> &arr, vector<vector<int>> &dp)
{
    if (dp[st][end] != -1)
        return dp[st][end];

    int leftcost = (st == 0) ? 1 : arr[st - 1];
    int rightcost = (end == arr.size() - 1) ? 1 : arr[end + 1];

    int maxans = 0;
    for (int cut = st; cut <= end; cut++)
    {
        int leftans = (cut == st) ? 0 : BurstBaloons(st, cut - 1, arr, dp);
        int rightans = (cut == end) ? 0 : BurstBaloons(cut + 1, end, arr, dp);

        int myans = leftans + leftcost * arr[cut] * rightcost + rightans;
        maxans = max(maxans, myans);
    }

    return dp[st][end] = maxans;
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return BurstBaloons(0, n - 1, nums, dp);
}

// METHOD 3 (Tabulated)

int BurstBaloons(int n, vector<int> &arr, vector<vector<int>> &dp)
{
    for (int gap = 0; gap < n; gap++)
    {
        for (int st = 0, end = gap; end < n; st++, end++)
        {
            int leftcost = (st == 0) ? 1 : arr[st - 1];
            int rightcost = (end == n - 1) ? 1 : arr[end + 1];

            int maxans = 0;
            for (int cut = st; cut <= end; cut++)
            {
                int leftans = (cut == st) ? 0 : dp[st][cut - 1];
                int rightans = (cut == end) ? 0 : dp[cut + 1][end];

                int myans = leftans + leftcost * arr[cut] * rightcost + rightans;
                maxans = max(maxans, myans);
            }
            dp[st][end] = maxans;
        }
    }
    return dp[0][n - 1];
}

int maxCoins(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return BurstBaloons(n, nums, dp);
}

// DAY 14 (Palindrome Partitioning)==============================================================

// METHOD 1 (Backtracking) --> O(n * 2^n)
bool ispal(string &s)
{
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
        if (s[i] != s[n - i - 1])
            return false;
    return true;
}

void palPartition(int idx, int n, string &que, vector<string> temp, vector<vector<string>> &res)
{
    if (idx == n)
    {
        res.push_back(temp);
        return;
    }
    string ans = "";
    for (int i = idx; i < n; i++)
    {
        ans += que[i];
        if (ispal(ans))
        {
            temp.push_back(ans);
            palPartition(i + 1, n, que, temp, res);
            temp.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    vector<vector<string>> res;
    palPartition(0, s.size(), s, {}, res);

    return res;
}

// METHOD 2 (Backtracking using Dynamic Programming) --> <O(n * 2^n)

void palindromes(int n, string &s, vector<vector<bool>> &ispal)
{
    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; i++, j++)
        {
            if (gap == 0)
                ispal[i][j] = true;
            else if (s[i] == s[j] && (gap == 1 || ispal[i + 1][j - 1]))
                ispal[i][j] = true;
        }
    }
}

void palPartition(int i, int n, string &s, vector<string> temp, vector<vector<string>> &res, vector<vector<bool>> &ispal)
{
    if (i == n)
    {
        res.push_back(temp);
        return;
    }

    for (int j = i; j < n; j++)
    {
        if (ispal[i][j])
        {
            temp.push_back(s.substr(i, j - i + 1));
            palPartition(j + 1, n, s, temp, res, ispal);
            temp.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n, false));
    palindromes(n, s, ispal);
    // for(int i = 0; i < n; i++)
    // {
    //     for(int j = 0; j < n; j++)
    //         cout<<ispal[i][j]<<" ";
    //     cout<<endl;
    // }
    vector<vector<string>> res;
    palPartition(0, s.size(), s, {}, res, ispal);

    return res;
}

// METHOD 3 (Same as METHOD 2, just more CONCISE)

void palPartition(int i, int n, string &s, vector<string> temp, vector<vector<string>> &res, vector<vector<bool>> &ispal)
{
    if (i == n)
    {
        res.push_back(temp);
        return;
    }

    for (int j = i; j < n; j++)
    {
        if (s[i] == s[j] && (j - i <= 2 || ispal[i + 1][j - 1]))
        {
            ispal[i][j] = true;
            temp.push_back(s.substr(i, j - i + 1));
            palPartition(j + 1, n, s, temp, res, ispal);
            temp.pop_back();
        }
    }
}

vector<vector<string>> partition(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n, false));
    vector<vector<string>> res;
    palPartition(0, s.size(), s, {}, res, ispal);

    return res;
}

// DAY 15 (Squares of a Sorted Array)=====================================================

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

// METHOD 2 --> (n*logn)
vector<int> sortedSquares(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end(), [](const int a, const int b) {
        return abs(a) < abs(b);
    });
    vector<int> squares(n);
    for (int i = 0; i < n; i++)
        squares[i] = nums[i] * nums[i];
    return squares;
}

// METHOD 3 --> O(n)
vector<int> sortedSquares(vector<int> &nums)
{
    int n = nums.size();

    int i = 0;
    while (i < n && nums[i] < 0)
        i++;
    int j = i - 1, k = 0;

    vector<int> squares(n);

    while (j >= 0 && i < n)
    {
        if (nums[i] < abs(nums[j]))
            squares[k++] = nums[i] * nums[i++];
        else
            squares[k++] = nums[j] * nums[j--];
    }
    while (j >= 0)
        squares[k++] = nums[j] * nums[j--];
    while (i < n)
        squares[k++] = nums[i] * nums[i++];

    return squares;
}

// DAY 16 (Validate Binary Search Tree)======================================================

// METHOD 1 --> O(n^2)
bool checkBSTright(int val, TreeNode *node)
{
    if (node->val <= val)
        return false;

    bool res = true;

    if (node->left)
        res &= checkBSTright(val, node->left);
    if (res && node->right)
        res &= checkBSTright(val, node->right);

    return res;
}
bool checkBSTleft(int val, TreeNode *node)
{
    if (node->val >= val)
        return false;

    bool res = true;

    if (node->left)
        res &= checkBSTleft(val, node->left);
    if (res && node->right)
        res &= checkBSTleft(val, node->right);

    return res;
}

bool isValidBST(TreeNode *root)
{
    bool res = true;

    if (root->left)
        res &= checkBSTleft(root->val, root->left);
    if (res && root->right)
        res &= checkBSTright(root->val, root->right);

    if (res && root->left)
        res &= isValidBST(root->left);
    if (res && root->right)
        res &= isValidBST(root->right);

    return res;
}