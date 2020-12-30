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

// METHOD 2 (Using inoder array(should be sorted))

void inorder(TreeNode *node, vector<int> &tree)
{
    if (!node)
        return;
    inorder(node->left, tree);
    tree.push_back(node->val);
    inorder(node->right, tree);
}

bool isValidBST(TreeNode *root)
{
    vector<int> tree;
    inorder(root, tree);

    for (int i = 1; i < tree.size(); i++)
        if (tree[i] <= tree[i - 1])
            return false;
    return true;
}

// METHOD 3 (Same as METHOD 2 --> Space OPTIMIZED)

TreeNode *prev = nullptr;

bool check_sorted(TreeNode *node)
{
    if (!prev)
    {
        prev = node;
        return true;
    }
    if (prev->val >= node->val)
        return false;
    prev = node;
    return true;
}

bool isValidBST(TreeNode *root)
{
    if (!root)
        return true;
    return isValidBST(root->left) && check_sorted(root) && isValidBST(root->right);
}

// DAY 17 (4 Sum II)=====================================================================

// METHOD 1 (Brute Force) --> O(n^3)
int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
    unordered_map<int, int> m;
    for (int i : D)
        m[i]++;

    int count = 0;
    for (int i : A)
        for (int j : B)
            for (int k : C)
                count += m[-1 * (i + j + k)];
    return count;
}

// METHOD 2 --> O(n^2)

int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
    unordered_map<int, int> m;
    for (int i : C)
        for (int j : D)
            m[i + j]++;

    int count = 0;
    for (int i : A)
        for (int j : B)
            count += m[-1 * (i + j)];
    return count;
}

// METHOD 3 -->  <=O(n^2)

#define f first
#define s second

int fourSumCount(vector<int> &A, vector<int> &B, vector<int> &C, vector<int> &D)
{
    unordered_map<int, int> a, b, c, d, ab;
    for (int i : A)
        a[i]++;
    for (int i : B)
        b[i]++;
    for (int i : C)
        c[i]++;
    for (int i : D)
        d[i]++;
    for (auto i : a)
        for (auto j : b)
            ab[i.f + j.f] += i.s * j.s;

    int count = 0;
    for (auto i : c)
        for (auto j : d)
            count += i.s * j.s * ab[-(i.f + j.f)];

    return count;
}

// DAY 18 (Increasing Triplet Sum)====================================================

bool increasingTriplet(vector<int> &nums)
{
    int a = INT_MAX, b = INT_MAX;

    for (int x : nums)
    {
        if (x <= a)
            a = x;
        else if (x <= b)
            b = x;
        else
            return true;
    }
    return false;
}

// DAY 20 (Decoded String at Index)=====================================================================

string decodeAtIndex(string S, int K)
{
    long size = 0;
    int N = S.size();

    for (int i = 0; i < N; ++i)
    {
        if (isdigit(S[i]))
            size *= S[i] - '0';
        else
            size++;
    }
    // cout<<size<<endl;

    for (int i = N - 1; i >= 0; --i)
    {
        // cout<<K<<", "<<size<<"->";
        K %= size;
        // cout<<K<<", "<<size<<endl;
        if (K == 0 && isalpha(S[i]))
            return (string) "" + S[i];

        if (isdigit(S[i]))
            size /= S[i] - '0';
        else
            size--;
    }
    return S.substr(K, 1);
}

// DAY 21 (Smallest Range 2)==============================================================

int smallestRangeII(vector<int> &A, int K)
{
    int n = A.size();
    sort(A.begin(), A.end());

    int mindiff = A[n - 1] - A[0];
    for (int i = 0; i < n - 1; i++)
    {
        int x = A[i], y = A[i + 1];
        int mini = min(A[0] + K, y - K);
        int maxi = max(A[n - 1] - K, x + K);
        mindiff = min(mindiff, maxi - mini);
    }

    return mindiff;
}

// DAY 22 (Balanced Binary Tree)================================================================

// METHOD 1 --> O(n^2)
int height(TreeNode *node)
{
    if (!node)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}

bool isBalanced(TreeNode *root)
{
    if (!root)
        return true;

    int lefth = height(root->left);
    int righth = height(root->right);

    if (abs(righth - lefth) > 1)
        return false;

    bool res = true;
    res &= isBalanced(root->left);
    if (res)
        res &= isBalanced(root->right);

    return res;
}

// METHOD 2 --> O(n)

int height(TreeNode *node)
{
    if (!node)
        return 0;

    int lefth = height(node->left);
    int righth = height(node->right);

    if (lefth == -1 || righth == -1 || abs(lefth - righth) > 1)
        return -1;

    return max(height(node->left), height(node->right)) + 1;
}

bool isBalanced(TreeNode *root)
{
    if (!root)
        return true;
    return height(root) != -1;
}

// DAY 23 (Next Greater Element)============================================================

// METHOD 1 (short)
int nextGreaterElement(int n)
{
    string s = to_string(n);

    if (next_permutation(s.begin(), s.end()))
    {
        long nn = stol(s);
        return nn > INT_MAX ? -1 : nn;
    }
    else
        return -1;
}

// METHOD 2 (Actual Method)
int nextGreaterElement(int n)
{
    vector<int> num;
    int temp = n;
    while (temp)
    {
        num.push_back(temp % 10);
        temp /= 10;
    }
    reverse(num.begin(), num.end());

    int ptr1 = -1;
    for (int i = num.size() - 1; i > 0; i--)
    {
        if (num[i - 1] < num[i])
        {
            ptr1 = i - 1;
            break;
        }
    }
    if (ptr1 == -1)
        return -1;

    int ptr2 = ptr1 + 1;
    for (int i = ptr2; i < num.size(); i++)
        if (num[i] > num[ptr1])
            ptr2 = i;
    swap(num[ptr1], num[ptr2]);

    reverse(num.begin() + ptr1 + 1, num.end());

    long nn = 0;
    for (int x : num)
    {
        nn *= 10;
        nn += x;
    }

    return nn > INT_MAX ? -1 : nn;
}

// DAY 24 (Swap Nodes in Pair)=========================================================

ListNode *swapPairs(ListNode *head)
{
    ListNode *prev = nullptr, *next, *itr = head;
    int swap = 1;

    while (itr && itr->next)
    {
        cout << itr->val << " -> ";
        ListNode *a = itr, *b = itr->next;
        // a->next = nullptr;
        a->next = b->next;
        // b->next = nullptr;
        b->next = a;
        if (prev != nullptr)
            prev->next = b;
        else
            head = b;

        prev = itr;
        cout << itr->val << ", ";
        itr = itr->next;
        swap = (swap + 1) % 2;
    }
    cout << endl;

    return head;
}

// DAY 25 (Diagonal Traverse)======================================================

vector<int> findDiagonalOrder(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    if (n == 0)
        return {};
    int m = matrix[0].size();
    int sum = 0;
    int down = 1;
    vector<int> ans(n * m);
    int k = 0;
    while (sum < (m + n - 1))
    {
        if (down == 1)
        {
            int i = min(sum, n - 1), j = sum - i;
            while (j <= min(sum, m - 1))
                ans[k++] = matrix[i--][j++];
        }
        else
        {
            int j = min(sum, m - 1), i = sum - j;
            while (i <= min(sum, n - 1))
                ans[k++] = matrix[i++][j--];
        }
        sum++;
        down = (down + 1) % 2;
    }
    return ans;
}

// DAY 26 (Decode Ways)===================================================

// METHOD 1 (Recursion)
// TLE
int countways(int i, string &s)
{
    if (i >= s.size())
        return 1;
    if (s[i] == '0')
        return 0;

    int count = 0;

    count += countways(i + 1, s);

    if (i < s.size() - 1)
    {
        int num = s[i] - '0';
        num *= 10;
        num += s[i + 1] - '0';
        if (num >= 10 && num <= 26)
            count += countways(i + 2, s);
    }
    return count;
}

int numDecodings(string s)
{
    return countways(0, s);
}

// METHOD 2 (DP - Memoized)

int countways(int i, string &s, vector<int> &dp)
{
    if (i >= s.size())
        return 1;
    if (s[i] == '0')
        return dp[i] = 0;
    if (i == s.size() - 1)
        return 1;
    if (dp[i] != -1)
        return dp[i];

    int count = 0;
    count += countways(i + 1, s, dp);

    int num = s[i] - '0';
    num *= 10;
    num += s[i + 1] - '0';
    if (num <= 26)
        count += countways(i + 2, s, dp);

    return dp[i] = count;
}

int numDecodings(string s)
{
    vector<int> dp(s.size(), -1);
    return countways(0, s, dp);
}

// METHOD 3 (Tabulation)

int countways(int i, string &s, vector<int> &dp)
{
    dp[0] = 1;
    for (int i = 1; i <= s.size(); i++)
    {
        if (s[i - 1] != '0')
            dp[i] = dp[i - 1];
        if (i > 1 && (s[i - 2] - '0') * 10 + (s[i - 1] - '0') >= 10 && (s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)
            dp[i] += dp[i - 2];
    }

    return dp[s.size()];
}

int numDecodings(string s)
{
    vector<int> dp(s.size() + 1, 0);
    return countways(0, s, dp);
}

// DAY 27 (Jump Game 4)==========================================================

// METHOD 1 (Using Recursion and Backtracking)
// TLE
int dfs(int i, unordered_map<int, vector<int>> &m, vector<bool> &vis, vector<int> &arr)
{
    if (i == arr.size() - 1)
        return 0;

    int moves = 5e5;
    int forw = 5e5, back = 5e5, tele = 5e5;
    if (vis[i + 1] == false)
    {
        vis[i + 1] = true;
        forw = dfs(i + 1, m, vis, arr);
        vis[i + 1] = false;
    }
    if (i - 1 >= 0 && vis[i - 1] == false)
    {
        vis[i - 1] = true;
        back = dfs(i - 1, m, vis, arr);
        vis[i - 1] = false;
    }
    for (int j : m[arr[i]])
    {
        if (vis[j] == false)
        {
            vis[j] = true;
            tele = dfs(j, m, vis, arr);
            vis[j] = false;
        }
    }
    moves = min(moves, min(forw, min(back, tele)));

    return moves + 1;
}

int minJumps(vector<int> &arr)
{
    int n = arr.size();
    unordered_map<int, vector<int>> m;
    for (int i = 0; i < n; i++)
        m[arr[i]].push_back(i);
    vector<bool> vis(n, false);
    vis[0] = true;

    return dfs(0, m, vis, arr);
}

// METHOD 2 (DFS using graph)
// TLE
int dfs(int src, int dest, vector<bool> &vis, vector<vector<int>> &gp)
{
    if (src == dest)
        return 0;

    int moves = 5e5;
    for (int i : gp[src])
    {
        if (!vis[i])
        {
            vis[i] = true;
            moves = min(moves, dfs(i, dest, vis, gp));
            vis[i] = false;
        }
    }
    return moves + 1;
}

int minJumps(vector<int> &arr)
{
    int n = arr.size();

    unordered_map<int, vector<int>> m;
    for (int i = 0; i < n; i++)
        m[arr[i]].push_back(i);
    vector<vector<int>> gp(n, vector<int>());
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            gp[i].push_back(i - 1);
        if (i != n - 1)
            gp[i].push_back(i + 1);
        for (int j : m[arr[i]])
            gp[i].push_back(j);
    }

    vector<bool> vis(n, false);
    vis[0] = true;

    return dfs(0, n - 1, vis, gp);
}

// METHOD 3 (BFS)
// TLE

int bfs(int src, int dest, vector<bool> &vis, vector<vector<int>> &gp)
{
    queue<int> que;
    que.push(0);
    int moves = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            int src = que.front();
            que.pop();
            vis[src] = true;

            if (src == dest)
                return moves;

            for (int i : gp[src])
            {
                if (!vis[i])
                {
                    if (i == dest)
                        return moves + 1;
                    que.push(i);
                }
            }
        }
        moves++;
    }
    return moves;
}

int minJumps(vector<int> &arr)
{
    int n = arr.size();

    unordered_map<int, vector<int>> m;
    for (int i = 0; i < n; i++)
        m[arr[i]].push_back(i);
    vector<vector<int>> gp(n, vector<int>());
    for (int i = 0; i < n; i++)
    {
        if (i != 0)
            gp[i].push_back(i - 1);
        if (i != n - 1)
            gp[i].push_back(i + 1);
        for (int j : m[arr[i]])
            gp[i].push_back(j);
    }

    vector<bool> vis(n, false);
    vis[0] = true;

    return bfs(0, n - 1, vis, gp);
}

// OPTIMIZED BFS

int bfs(int src, int dest, vector<int> &arr, unordered_map<int, vector<int>> &gp)
{
    deque<int> que;
    que.push_back(0);
    vector<bool> vis(arr.size(), false);
    vis[0] = true;
    int moves = 0;
    while (!que.empty())
    {
        int sz = que.size();
        // cout<<moves<<": \n";
        while (sz--)
        {
            int src = que.front();
            que.pop_front();
            // cout<<src<<", ";

            if (src == dest)
                return moves;
            // cout<<arr[src]<<" --> ";

            for (int i : gp[arr[src]])
            {
                if (i != src && !vis[i])
                {
                    // cout<<i<<", ";
                    vis[i] = true;
                    if (i == dest)
                        return moves + 1;
                    que.push_back(i);
                }
            }

            for (int d : {-1, 1})
            {
                if (src + d >= 0 && src + d <= dest && !vis[src + d])
                {
                    // cout<<src+d<<", ";
                    vis[src + d] = true;
                    if (src + d == dest)
                        return moves + 1;
                    que.push_back(src + d);
                }
            }
            // cout<<endl;
        }
        moves++;
    }
    return moves;
}

int minJumps(vector<int> &arr)
{
    int n = arr.size();
    // cout<<n<<endl;

    unordered_map<int, vector<int>> gp;
    for (int i = 0; i < n; i++)
        gp[arr[i]].push_back(i);

    return bfs(0, n - 1, arr, gp);
}

// DAY 28 (Reach a Number)===================================================

// METHOD 1 (BFS) --> O(2^n)
// TLE
#define f first
#define s second
int reachNumber(int target)
{
    queue<pair<int, int>> que;
    que.push({0, 1});
    int jump = 1;

    while (!que.empty())
    {
        auto top = que.front();
        que.pop();
        if (top.f == target)
            return top.s - 1;
        if (top.f - top.s >= -1e9)
        {
            if (top.f - top.s == target)
                return top.s;
            que.push({top.f - top.s, top.s + 1});
        }
        if (top.f + top.s <= 1e9)
        {
            if (top.f + top.s == target)
                return top.s;
            que.push({top.f + top.s, top.s + 1});
        }
    }
    return 0;
}

// METHOD 2 (Math) --> O(sqrt(target))
// AC
int reachNumber(int target)
{
    int t = abs(target);

    for (int n = 0; n <= 1e5; n++)
    {
        long x = (n * (n + 1)) / 2;
        if (x - t >= 0 && (x - t) % 2 == 0)
            return n;
    }
    return -1;
}

// DAY 29 (Pseudo-Palindromic Paths in a Binary Tree)============================================================

// METHOD 1 (Using Haspmap)
bool isvalidPath(unordered_map<int, int> &m)
{
    int odds = 0;
    for (auto itr : m)
        if (itr.second % 2 != 0)
            odds++;
    if (odds > 1)
        return false;
    return true;
}

int preorder(unordered_map<int, int> &m, TreeNode *node)
{
    if (!node)
        return 0;
    m[node->val]++;
    if (!node->left && !node->right)
    {
        if (isvalidPath(m))
        {
            if (--m[node->val] == 0)
                m.erase(node->val);
            return 1;
        }
        if (--m[node->val] == 0)
            m.erase(node->val);
        return 0;
    }
    int count = 0;

    count += preorder(m, node->left);
    count += preorder(m, node->right);
    // --m[node->val];
    if (--m[node->val] == 0)
        m.erase(node->val);
    return count;
}

int pseudoPalindromicPaths(TreeNode *root)
{
    unordered_map<int, int> m;
    return preorder(m, root);
}

// METHOD 2 (Without map, using bitwise operation) --> OPTIMIZED
int count = 0;
void preorder(TreeNode *node, int odds)
{
    if (!node)
        return;

    odds ^= (1 << node->val);
    if (!node->left && !node->right && __builtin_popcount(odds) <= 1)
        count++;
    preorder(node->left, odds);
    preorder(node->right, odds);
}

int pseudoPalindromicPaths(TreeNode *root)
{
    preorder(root, 0);
    return count;
}

// DAY 30 (Game of Life)======================================================

int liveOrdead(int i, int j, int n, int m, vector<vector<int>> &arr)
{
    int live = 0;
    if (i - 1 >= 0 && arr[i - 1][j] == 1)
        live++;
    if (j - 1 >= 0 && arr[i][j - 1] == 1)
        live++;
    if (i + 1 < n && arr[i + 1][j] == 1)
        live++;
    if (j + 1 < m && arr[i][j + 1] == 1)
        live++;
    if (i - 1 >= 0 && j - 1 >= 0 && arr[i - 1][j - 1] == 1)
        live++;
    if (i - 1 >= 0 && j + 1 < m && arr[i - 1][j + 1] == 1)
        live++;
    if (i + 1 < n && j - 1 >= 0 && arr[i + 1][j - 1] == 1)
        live++;
    if (i + 1 < n && j + 1 < m && arr[i + 1][j + 1] == 1)
        live++;

    if (live < 2 || live > 3)
        return 0;
    if (live == 3)
        return 1;
    return arr[i][j];
}

void gameOfLife(vector<vector<int>> &board)
{
    int n = board.size();
    int m = board[0].size();
    vector<vector<int>> ans(board);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ans[i][j] = liveOrdead(i, j, n, m, board);
    board = ans;
}