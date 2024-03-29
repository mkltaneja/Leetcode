// DAY 1 (Longest Common Subsequence)============================================================

int longestCommonSubsequence(string text1, string text2)
{
    int n = text1.size(), m = text2.size();
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int im1 = i ? dp[i - 1][j] : 0;
            int jm1 = j ? dp[i][j - 1] : 0;
            int ijm1 = (i && j) ? dp[i - 1][j - 1] : 0;

            dp[i][j] = (text1[i] == text2[j]) ? max({ijm1 + 1, im1, jm1}) : max(im1, jm1);
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

// DAY 2 (Dungeon Game)================================================================================

int calculateMinimumHP(vector<vector<int>> &dungeon)
{
    int n = dungeon.size(), m = dungeon[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    dp[n - 1][m - 1] = (dungeon[n - 1][m - 1] <= 0) ? (-dungeon[n - 1][m - 1] + 1) : 1;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = m - 1; j >= 0; j--)
        {
            if (i == n - 1 && j == m - 1)
                continue;

            int right = (j != m - 1) ? dp[i][j + 1] : INT_MAX;
            int down = (i != n - 1) ? dp[i + 1][j] : INT_MAX;

            dp[i][j] = max(-dungeon[i][j] + min(right, down), 1);
        }
    }

    return dp[0][0];
}

// DAY 3 (Jump Game)=================================================================================

bool canJump(vector<int> &nums)
{
    int maxjump = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        maxjump--;
        maxjump = max(maxjump, nums[i]);
        if (i != nums.size() - 1 && maxjump == 0)
            return false;
    }
    return true;
}

// DAY 4 (Island Perimeter)============================================================================

int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j])
            {
                ans += (i ? (grid[i - 1][j] == 0) : 1);
                ans += (j ? (grid[i][j - 1] == 0) : 1);
                ans += ((i != n - 1) ? (grid[i + 1][j] == 0) : 1);
                ans += ((j != m - 1) ? (grid[i][j + 1] == 0) : 1);
            }
        }
    }
    return ans;
}

// DAY 5 (Climbing Stairs)====================================================================

int climbStairs(int n)
{
    int a = 1, b = 1, ans = 1;
    while (--n)
    {
        a = b;
        b = ans;
        ans = a + b;
    }
    return ans;
}

// DAY 6 (Find All Duplicates in an Array)===============================================================

vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[abs(nums[i]) - 1] > 0)
            nums[abs(nums[i]) - 1] *= -1;
        else
            ans.push_back(abs(nums[i]));
    }
    return ans;
}

// DAY 7 (Word Search)===============================================================================

bool dfs(int i, int j, int k, int n, int m, vector<vector<char>> &board, string &s)
{
    if (k == s.size())
        return true;
    if (i == -1 || j == -1 || i == n || j == m || board[i][j] != s[k])
        return false;

    char c = board[i][j];
    board[i][j] = '#';
    if (dfs(i + 1, j, k + 1, n, m, board, s))
        return true;
    if (dfs(i, j + 1, k + 1, n, m, board, s))
        return true;
    if (dfs(i - 1, j, k + 1, n, m, board, s))
        return true;
    if (dfs(i, j - 1, k + 1, n, m, board, s))
        return true;
    board[i][j] = c;

    return false;
}

bool exist(vector<vector<char>> &board, string word)
{
    int n = board.size(), m = board[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (dfs(i, j, 0, n, m, board, word))
                return true;
    return false;
}

// DAY 8 (Implement Trie (Prefix Tree))===============================================================================
class Trie
{
public:
    class Node
    {
    public:
        vector<Node *> t;
        bool wordEnd;
        Node()
        {
            this->t.assign(26, nullptr);
            this->wordEnd = false;
        }
    };

    Node *node;

    Trie()
    {
        this->node = new Node();
    }

    void insert(string word)
    {
        Node *curr = node;
        for (char c : word)
        {
            if (!curr->t[c - 'a'])
                curr->t[c - 'a'] = new Node();
            curr = curr->t[c - 'a'];
        }
        curr->wordEnd = true;
    }

    bool search(string word)
    {
        Node *curr = node;
        for (char c : word)
        {
            if (!curr->t[c - 'a'])
                return false;
            curr = curr->t[c - 'a'];
        }
        return curr->wordEnd;
    }

    bool startsWith(string prefix)
    {
        Node *curr = node;
        for (char c : prefix)
        {
            if (!curr->t[c - 'a'])
                return false;
            curr = curr->t[c - 'a'];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

// DAY 10 (Bitwise and Number Range)======================================================================

// APPROACH 1 (Find the last OFF bit for a particular ON bit) --> O(32)

int rangeBitwiseAnd(int left, int right)
{
    int ans = 0;
    int i = 0;
    while (i < 32)
    {
        if (right & (1 << i))
        {
            int offbit = right & ~(1 << i);
            offbit |= (1 << i) - 1;
            if (left > offbit)
                ans |= (1 << i);
        }
        i++;
    }

    return ans;
}

// APPROACH 2 (Find maximum common prefix) --> O(log(right))

int rangeBitwiseAnd(int left, int right)
{
    int x = 0;
    while (left != right)
    {
        left >>= 1;
        right >>= 1;
        x++;
    }
    return left << x;
}

// DAY 11 (Diameter of a Binary Tree)==============================================

int ans = 0;
int dia(TreeNode *node)
{
    if (!node)
        return -1;

    int lans = dia(node->left);
    int rans = dia(node->right);
    ans = max(ans, lans + rans + 2);

    return max(lans, rans) + 1;
}

int diameterOfBinaryTree(TreeNode *root)
{
    dia(root);
    return ans;
}

// DAY 12 (Guess the Number Higher or Lower)=======================================================

int guessNumber(int n)
{
    int l = 1, r = n;
    while (l <= r)
    {
        int m = l + (r - l) / 2;
        int guessed = guess(m);
        if (guessed == 0)
            return m;
        if (guessed == -1)
            r = m - 1;
        else
            l = m + 1;
    }
    return -1;
}

// DAY 13 (Construct Binary Search Tree From Preorder Travesal)==========================================================

TreeNode *insert(int x, TreeNode *node)
{
    if (!node)
        return new TreeNode(x);
    if (x > node->val)
        node->right = insert(x, node->right);
    else
        node->left = insert(x, node->left);

    return node;
}

TreeNode *bstFromPreorder(vector<int> &preorder)
{
    TreeNode *root = nullptr;
    for (int x : preorder)
        root = insert(x, root);
    return root;
}

// DAY 14 ( Perfect Squares)===========================================================================

#define f first
#define s second
int numSquares(int n)
{
    queue<pair<int, int>> que;
    que.push({n, 0});
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        // cout<<tp.f<<", "<<tp.s<<endl;
        if (tp.f == 0)
            return tp.s;

        int x = sqrt(tp.f);
        for (int i = x; i >= 1; i--)
        {
            if (i * i == tp.f)
                return tp.s + 1;
            que.push({tp.f - i * i, tp.s + 1});
        }
    }
    return n;
}

// DAY 15 (Best Time to Buy and Sell Stock with Cooldown)=======================================================

int maxProfit(vector<int> &prices)
{
    int sellp = 0, buyp = INT_MIN, psellp = 0;
    for (int x : prices)
    {
        int tmp = sellp;
        sellp = max(sellp, buyp + x);
        buyp = max(buyp, psellp - x);
        psellp = tmp;
    }
    return sellp;
}

// DAY 16 (Best Time to Buy and Sell Stock 3)------------------------------------------------------------------------------

int maxProfit(vector<int> &prices)
{
    int sk1 = 0, sk2 = 0, bk1 = INT_MIN, bk2 = INT_MIN;
    for (int x : prices)
    {
        sk2 = max(sk2, bk2 + x);
        bk2 = max(bk2, sk1 - x);
        sk1 = max(sk1, bk1 + x);
        bk1 = max(bk1, -x);
    }

    return sk2;
}

// ḌAY 17 (Path Sum 3)=======================================================================================

int rootsum(TreeNode *node, int sum)
{
    if (!node)
        return 0;

    int ans = 0;
    if (sum == node->val)
        ans++;

    ans += rootsum(node->left, sum - node->val);
    ans += rootsum(node->right, sum - node->val);

    return ans;
}

int pathSum(TreeNode *root, int targetSum)
{
    if (!root)
        return 0;
    return pathSum(root->left, targetSum) + rootsum(root, targetSum) + pathSum(root->right, targetSum);
}

// DAY 18 (Cousins in Binary Tree)====================================================================================

#define f first
#define s second

bool isCousins(TreeNode *root, int x, int y)
{
    queue<pair<TreeNode *, int>> que;
    que.push({root, -1});

    while (!que.empty())
    {
        int sz = que.size();
        pair<TreeNode *, int> p1 = {nullptr, -1}, p2 = {nullptr, -1};
        while (sz--)
        {
            auto tp = que.front();
            que.pop();
            if (tp.f->val == x)
                p1 = {tp.f, tp.s};
            if (tp.f->val == y)
                p2 = {tp.f, tp.s};

            if (tp.f->left)
                que.push({tp.f->left, tp.f->val});
            if (tp.f->right)
                que.push({tp.f->right, tp.f->val});
        }
        if (p1.f && p2.f)
            return p1.s != p2.s;
        if (p1.f || p2.f)
            return false;
    }

    return false;
}

// DAY 19 (Next Greater Element 1)========================================================================

vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
{
    stack<int> st;
    unordered_map<int, int> ng;
    for (int i = 0; i < nums2.size(); i++)
    {
        while (!st.empty() && nums2[st.top()] < nums2[i])
        {
            ng[nums2[st.top()]] = nums2[i];
            st.pop();
        }
        st.push(i);
    }
    while (!st.empty())
    {
        ng[nums2[st.top()]] = -1;
        st.pop();
    }

    vector<int> ans(nums1.size());
    for (int i = 0; i < nums1.size(); i++)
        ans[i] = ng[nums1[i]];

    return ans;
}

// DAY 20 (Reverse Words in a String)====================================================================

string reverseWords(string s)
{
    stringstream ss(s);
    string token;

    vector<string> ans;
    while (ss >> token)
        ans.push_back(token);

    reverse(ans.begin(), ans.end());

    string res = "";
    for (string x : ans)
        res += x + " ";
    res.pop_back();

    return res;
}

// DAY 21 (Insert Delete GetRandom O(1))=================================================================
class RandomizedSet
{
public:
    unordered_map<int, int> mi;
    vector<int> arr;
    RandomizedSet() {}

    bool insert(int val)
    {
        if (mi.count(val))
            return false;

        mi[val] = arr.size();
        arr.push_back(val);

        return true;
    }

    bool remove(int val)
    {
        if (!mi.count(val))
            return false;

        arr[mi[val]] = arr[arr.size() - 1];
        arr.pop_back();
        mi[arr[mi[val]]] = mi[val];
        mi.erase(val);

        return true;
    }

    int getRandom()
    {
        return arr[rand() % arr.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// DAY 22 (Sort Characters By Frequency)================================================================================

string frequencySort(string s)
{
    vector<pair<int, char>> map(62);
    for (int i = 0; i < 62; i++)
    {
        if (i < 26)
            map[i] = {0, char(i + 'a')};
        else if (i < 52)
            map[i] = {0, char(i - 26 + 'A')};
        else
            map[i] = {0, char(i - 52 + '0')};
    }

    for (char c : s)
    {
        if (c >= 'a' && c <= 'z')
            map[c - 'a'].first++;
        else if (c >= 'A' && c <= 'Z')
            map[26 + c - 'A'].first++;
        else
            map[52 + c - '0'].first++;
    }
    sort(map.rbegin(), map.rend());

    string ans = "";
    for (int i = 0; i < 62; i++)
        while (map[i].first--)
            ans += map[i].second;
    return ans;
}

// DAY 23 (Find Minimum in Rotated Sorted Array)========================================================================

int findMin(vector<int> &nums)
{
    int l = 0, r = nums.size() - 1;
    while (l < r)
    {
        int m = (l + r) / 2;
        if (nums[m] > nums[r])
            l = m + 1;
        else if (nums[m] < nums[l])
            r = m;
        else
            r--;
    }
    return nums[l];
}

// DAY 24 (Count Complete Tree Nodes)==============================================

int lefth(TreeNode *node)
{
    int cnt = 0;
    while (node)
    {
        cnt++;
        node = node->left;
    }

    return cnt;
}
int righth(TreeNode *node)
{
    int cnt = 0;
    while (node)
    {
        cnt++;
        node = node->right;
    }

    return cnt;
}

int countNodes(TreeNode *root)
{
    if (!root)
        return 0;

    int lh = lefth(root);
    int rh = righth(root);

    if (lh == rh)
        return (1 << lh) - 1;

    int l = countNodes(root->left);
    int r = countNodes(root->right);

    return l + r + 1;
}

// DAY 25 (Min Stack)==========================================================================
class MinStack
{
public:
    stack<long> st;
    long mn;
    MinStack()
    {
        this->mn = INT_MAX;
    }

    void push(int val)
    {
        if (st.empty())
        {
            st.push(val);
            mn = val;
        }
        else if (val < mn)
        {
            st.push(val - mn + val);
            mn = val;
        }
        else
            st.push(val);
    }

    void pop()
    {
        if (st.top() < mn)
            mn = mn - st.top() + mn;
        st.pop();
    }

    int top()
    {
        if (st.top() < mn)
            return mn;
        return st.top();
    }

    int getMin()
    {
        return mn;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

// DAY 26 (Invert Binary Tree)========================================================================

TreeNode *invertTree(TreeNode *root)
{
    if (!root)
        return root;

    TreeNode *l = invertTree(root->left);
    TreeNode *r = invertTree(root->right);

    root->left = r;
    root->right = l;

    return root;
}

// DAY 27 (Sort Colors)===================================================================

void sortColors(vector<int> &nums)
{
    int i = 0, j = 0, k = nums.size() - 1;
    while (i <= k)
    {
        if (nums[i] == 0)
            swap(nums[i++], nums[j++]);
        else if (nums[i] == 2)
            swap(nums[i], nums[k--]);
        else
            i++;
    }
}

// DAY 28 (3Sum)=====================================================================================

vector<int> twoSum(int l, int r, vector<int> &nums, int tar, vector<vector<int>> &res)
{
    while (l < r)
    {
        int sum = nums[l] + nums[r];
        if (sum == tar)
        {
            int x = nums[l], y = nums[r];
            res.push_back({-tar, nums[l], nums[r]});
            while (l < r && nums[l] == x)
                l++;
            while (l < r && nums[r] == y)
                r--;
        }
        else if (sum < tar)
            l++;
        else
            r--;
    }
    return {-1, -1};
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < n; i++)
    {
        twoSum(i + 1, n - 1, nums, -nums[i], ans);
        while (i + 1 < n && nums[i + 1] == nums[i])
            i++;
    }

    return ans;
}

// DAY 29 (Rotten Oranges)======================================================================

int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size(), m = grid[0].size();
    queue<int> que;
    int rot = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 2)
                que.push(i * m + j);
            else if (grid[i][j] == 1)
                rot++;
        }
    }

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int time = 0;
    while (!que.empty())
    {
        int sz = que.size();
        bool areRot = false;
        while (sz--)
        {
            int x = que.front();
            que.pop();

            int i = x / m;
            int j = x % m;

            for (int d = 0; d < 4; d++)
            {
                int r = i + dir[d][0];
                int c = j + dir[d][1];
                if (r < n && c < m && r != -1 && c != -1 && grid[r][c] == 1)
                {
                    grid[r][c] = 2;
                    areRot = true;
                    rot--;
                    que.push(r * m + c);
                }
            }
        }
        time += areRot;
    }

    return rot ? -1 : time;
}

// DAY 31 (Flatten a Multilevel Doubly Linked List)=====================================================================

#define h first
#define t second

pair<Node *, Node *> flatten_(Node *head)
{
    Node *itr = head, *tail = head;
    while (itr)
    {
        pair<Node *, Node *> child = {nullptr, nullptr};
        if (itr->child)
            child = flatten_(itr->child);

        Node *nxt = itr->next;
        if (child.h != nullptr)
        {
            itr->next = nullptr;
            itr->next = child.h;
            child.h->prev = itr;

            child.t->next = nxt;
            if (nxt)
            {
                nxt->prev = nullptr;
                nxt->prev = child.t;
            }
            itr->child = nullptr;

            tail = child.t;
        }
        else
            tail = itr;
        itr = nxt;
    }
    return {head, tail};
}

Node *flatten(Node *head)
{
    Node *node = flatten_(head).h;
    return node;
}