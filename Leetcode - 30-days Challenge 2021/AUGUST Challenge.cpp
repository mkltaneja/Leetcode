
// DAY 2 (Two Sum)=========================================================================

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.count(target - nums[i]))
            return {m[target - nums[i]], i};
        m[nums[i]] = i;
    }
    return {};
}

// DAY 3 (Subsets 2)===============================================================================================

void subsets(int i, vector<int> &nums, set<vector<int>> &st, vector<vector<int>> &ans, vector<int> ss)
{
    if (i == nums.size())
    {
        if (!st.count(ss))
        {
            ans.push_back(ss);
            st.insert(ss);
        }
        return;
    }
    subsets(i + 1, nums, st, ans, ss);
    ss.push_back(nums[i]);
    subsets(i + 1, nums, st, ans, ss);
    ss.pop_back();
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    vector<vector<int>> ans;
    subsets(0, nums, st, ans, {});
    return ans;
}

// DAY 4 (Path Sum 2)================================================================================

void dfs(TreeNode *node, int sum, int target, vector<int> &curr, vector<vector<int>> &ans)
{
    if (!node)
        return;

    curr.push_back(node->val);
    sum += node->val;

    if (!node->left && !node->right && sum == target)
        ans.push_back(curr);

    dfs(node->left, sum, target, curr, ans);
    dfs(node->right, sum, target, curr, ans);

    curr.pop_back();
    sum -= node->val;
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<vector<int>> ans;
    vector<int> curr;
    dfs(root, 0, targetSum, curr, ans);
    return ans;
}

// DAY 6 (N - ary tree Level Order Traversal)===============================================================================
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        if (!root)
            return {};

        vector<vector<int>> ans;

        queue<Node *> que;
        que.push(root);

        while (!que.empty())
        {
            int sz = que.size();
            vector<int> lvl;
            while (sz--)
            {
                Node *node = que.front();
                que.pop();
                lvl.push_back(node->val);
                for (Node *child : node->children)
                    que.push(child);
            }
            ans.push_back(lvl);
        }
        return ans;
    }
};

// DAY 7 (Palindromic Partitioning 2)=======================================================================

int minCut(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n, false));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (gap == 0)
                ispal[i][j] = true;
            else if (s[i] == s[j] && gap == 1)
                ispal[i][j] = true;
            else if (s[i] == s[j] && ispal[i + 1][j - 1])
                ispal[i][j] = true;
        }
    }

    vector<int> dp(n);
    for (int i = 0; i < n; i++)
        dp[i] = i;

    for (int i = 1; i < n; i++)
    {
        if (ispal[0][i])
        {
            dp[i] = 0;
            continue;
        }
        for (int j = 1; j <= i; j++)
            if (ispal[j][i])
                dp[i] = min(dp[i], dp[j - 1] + 1);
    }
    return dp[n - 1];
}

// DAY 8 (Rank Transform of a Matrix)==============================================================================

#define f first
#define s second

int findpar(int x, vector<int> &par)
{
    if (par[x] == x)
        return x;
    return par[x] = findpar(par[x], par);
}

vector<vector<int>> matrixRankTransform(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    map<int, vector<pair<int, int>>> mat;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[matrix[i][j]].push_back({i, j});

    vector<int> rank(n + m, 0);
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (auto p : mat)
    {
        vector<int> par(n + m);
        for (int i = 0; i < n + m; i++)
            par[i] = i;

        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pi = findpar(i, par), pj = findpar(j + n, par);
            par[pi] = pj;
            rank[pj] = max(rank[pi], rank[pj]);
        }
        vector<int> curr = rank;
        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pij = findpar(i, par);
            ans[i][j] = rank[pij] + 1;
            curr[i] = rank[pij] + 1;
            curr[j + n] = rank[pij] + 1;
        }
        rank = curr;
    }
    return ans;
}

// DAY 9 (Add Strings)======================================================

string addStrings(string num1, string num2)
{
    string ans = "";
    int i = num1.size() - 1, j = num2.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0)
    {
        int x = (i >= 0) ? (num1[i--] - '0') : 0;
        int y = (j >= 0) ? (num2[j--] - '0') : 0;

        int sum = x + y + carry;
        carry = sum / 10;
        ans += char(sum % 10 + '0');
    }

    if (carry)
        ans += char(carry + '0');
    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 10 (Flip String to Monotone String)===================================================

// APPROACH 1 (Making all possible combinations of the string) --> O(n^2)
// TLE

int cost(string &a, string &b)
{
    int cost = 0;
    for (int i = 0; i < a.size(); i++)
        cost += (a[i] != b[i]);
    return cost;
}

int minFlipsMonoIncr(string s)
{
    int zeros = s.size(), ones = 0;
    int mincost = INT_MAX;
    while (zeros >= 0)
    {
        string temp = "";
        for (int i = 0; i < zeros; i++)
            temp += "0";
        for (int i = 0; i < ones; i++)
            temp += "1";
        mincost = min(mincost, cost(temp, s));
        zeros--, ones++;
    }
    return mincost;
}

// APPROACH 2 (Two variable approach)===================================================

int minFlipsMonoIncr(string s)
{
    int ones = 0, flips = 0;
    for (char c : s)
    {
        if (c == '0')
        {
            if (ones)
                flips++;
        }
        else
            ones++;
        if (ones < flips)
            flips = ones;
    }
    return flips;
}

// DAY 11 (Array of Doubled Pairs)====================================================================

bool canReorderDoubled(vector<int> &arr)
{
    sort(arr.begin(), arr.end(), [](int a, int b)
         { return abs(a) < abs(b); });
    unordered_map<int, int> m;
    for (int x : arr)
        m[x]++;

    for (int x : arr)
    {
        if (x & 1)
        {
            if (m[2 * x] == 0)
                return false;
            m[x]--;
            m[2 * x]--;
        }
        else
        {
            if (m[x] == 0)
                continue;
            if (m[2 * x] == 0)
                return false;
            m[x]--;
            m[2 * x]--;
        }
    }
    return true;
}

// DAY 12 (Group Anagrams)=====================================================================

#define ull unsigned long long

int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

ull make_hash(string &s)
{
    ull hash = 1;
    for (char c : s)
        hash *= primes[c - 'a'];
    return hash;
}

vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<ull, vector<string>> m;
    for (string s : strs)
    {
        ull hash = make_hash(s);
        m[hash].push_back(s);
    }

    vector<vector<string>> ans;
    for (auto p : m)
        ans.push_back(p.second);

    return ans;
}

// DAY 13 (Set Matrix Zeros)============================================================================

void setZeroes(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<bool> row(n), col(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 0)
                row[i] = true, col[j] = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (row[i] || col[j])
                matrix[i][j] = 0;
}

// DAY 14 (Remove Boxes)========================================================================================

int dfs(int i, int j, int k, vector<int> &boxes, vector<vector<vector<int>>> &dp)
{
    if (i > j)
        return 0;

    if (dp[i][j][k] != -1)
        return dp[i][j][k];

    int ans = (k + 1) * (k + 1) + dfs(i + 1, j, 0, boxes, dp);
    for (int x = i + 1; x <= j; x++)
        if (boxes[x] == boxes[i])
            ans = max(ans, dfs(i + 1, x - 1, 0, boxes, dp) + dfs(x, j, k + 1, boxes, dp));
    return dp[i][j][k] = ans;
}

int removeBoxes(vector<int> &boxes)
{
    int n = boxes.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -1)));
    return dfs(0, n - 1, 0, boxes, dp);
}

// DAY 15 (Minimum Sliding Window Substring)=======================================================================

string minWindow(string s, string t)
{
    unordered_map<char, int> map, tmap;
    for (char c : t)
        map[c]++, tmap[c]++;

    int match = 0, x = s.size(), y = -1;
    int j = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (map[s[i]])
        {
            if (tmap[s[i]] > 0)
                match++;
            tmap[s[i]]--;
        }
        while (j <= i && match == t.size())
        {
            if (i - j + 1 < x - y + 1)
                x = i, y = j;
            if (map[s[j]])
                if (++tmap[s[j]] > 0)
                    match--;
            j++;
        }
    }
    return y == -1 ? "" : s.substr(y, x - y + 1);
}

// DAY 16 (Range Sum Query - Immutable)===================================================================================
class NumArray
{
public:
    vector<int> psum;
    NumArray(vector<int> &nums)
    {
        psum.assign(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++)
            psum[i] = (i ? psum[i - 1] : 0) + nums[i];
    }

    int sumRange(int left, int right)
    {
        return psum[right] - (left ? psum[left - 1] : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

// DAY 17 (Count Good Nodes in Binary Tree)====================================================================

int ans = 0;
void dfs(TreeNode *node, int mx)
{
    if (!node)
        return;
    if (node->val >= mx)
        ans++;
    dfs(node->left, max(mx, node->val));
    dfs(node->right, max(mx, node->val));
}

int goodNodes(TreeNode *root)
{
    dfs(root, INT_MIN);
    return ans;
}

// DAY 18 (Decode Ways)=============================================================

int dfs(int i, string &s, vector<int> &dp)
{
    if (i == s.size())
        return 1;
    if (s[i] == '0')
        return 0;
    if (dp[i] != -1)
        return dp[i];

    int ans = 0;
    ans += dfs(i + 1, s, dp);

    if (i != s.size() - 1)
    {
        int num = (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26;
        if (num >= 1 && num <= 26)
            ans += dfs(i + 2, s, dp);
    }
    return dp[i] = ans;
}

int numDecodings(string s)
{
    vector<int> dp(s.size(), -1);
    return dfs(0, s, dp);
}

// DAY 19 (Maximum Sum of Splitted Binary Tree)=========================================================

#define ull unsigned long long

ull tsum = 0;
ull total_sum(TreeNode *node)
{
    if (!node)
        return 0;
    return total_sum(node->left) + total_sum(node->right) + node->val;
}

ull maxans = 0;
ull dfs(TreeNode *node)
{
    if (!node)
        return 0;

    ull lsum = dfs(node->left);
    ull rsum = dfs(node->right);

    ull csum = node->val + lsum + rsum;

    maxans = max(maxans, csum * (tsum - csum));

    return lsum + rsum + node->val;
}

int maxProduct(TreeNode *root)
{
    tsum = total_sum(root);
    dfs(root);

    return maxans % (1000000007);
}

// DAY 20 (Valid Sudoku)================================================================================

int row[9] = {0}, col[9] = {0}, mat[3][3] = {0};

bool isSafe(int i, int j, int n)
{
    if ((row[i] & (1 << n)) || (col[j] & (1 << n)) || (mat[i / 3][j / 3] & (1 << n)))
        return false;
    return true;
}

void set(int i, int j, int n, bool placed, vector<vector<char>> &board)
{
    if (placed)
        board[i][j] = '.';
    else
        board[i][j] = char(n + '0');

    row[i] ^= (1 << n);
    col[j] ^= (1 << n);
    mat[i / 3][j / 3] ^= (1 << n);
}

bool isValidSudoku(vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                if (!isSafe(i, j, board[i][j] - '0'))
                    return false;
                set(i, j, board[i][j] - '0', false, board);
            }
        }
    }
    return true;
}

// DAY 21 (Sudoku Solver)=====================================================================================

int row[9] = {0}, col[9] = {0}, mat[3][3] = {0};

bool isSafe(int i, int j, int n)
{
    if((row[i] & (1 << n)) || (col[j] & (1 << n)) || (mat[i/3][j/3] & (1 << n)))
        return false;
    return true;
}

void set(int i, int j, int n, bool placed, vector<vector<char>> &board)
{
    board[i][j] = placed? '.' : char(n+'0');
    row[i] ^= (1 << n);
    col[j] ^= (1 << n);
    mat[i/3][j/3] ^= (1 << n);
}

bool sudoku(int x, vector<vector<char>> &board)
{
    if(x == 81) return true;
    
    int i = x/9, j = x%9;
    if(board[i][j] != '.')
        return sudoku(x+1, board);
    
    
    for(int n = 1; n <= 9; n++)
    {
        if(isSafe(i, j, n))
        {
            set(i, j, n, false, board);
            if(sudoku(x+1, board)) return true;
            set(i, j, n, true, board);
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>>& board) 
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board[i][j] != '.')
                set(i, j, board[i][j]-'0', false, board);
    sudoku(0, board);
}

// DAY 23 (2 Sum 4 - Input in a BST) ==========================================================================

// APPROACH 1 --> O(n*logn)

bool find(TreeNode* root, TreeNode* node, int x)
{
    if(!root) return false;
    if(root->val == x && root != node) return true;
    if(root->val < x) return find(root->right, node, x);
    else return find(root->left, node, x);
}

bool preorder(TreeNode* root, TreeNode* node, int k)
{
    if(!node) return false;
    
    if(find(root, node, k - node->val)) return true;
    
    if(preorder(root, node->left, k)) return true;
    if(preorder(root, node->right, k)) return true;
    
    return false;
}

bool findTarget(TreeNode* root, int k) 
{
    return preorder(root, root, k);
}

// APPROACH 2 --> O(n)

// DAY 2 (Two Sum)=========================================================================

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.count(target - nums[i]))
            return {m[target - nums[i]], i};
        m[nums[i]] = i;
    }
    return {};
}

// DAY 3 (Subsets 2)===============================================================================================

void subsets(int i, vector<int> &nums, set<vector<int>> &st, vector<vector<int>> &ans, vector<int> ss)
{
    if (i == nums.size())
    {
        if (!st.count(ss))
        {
            ans.push_back(ss);
            st.insert(ss);
        }
        return;
    }
    subsets(i + 1, nums, st, ans, ss);
    ss.push_back(nums[i]);
    subsets(i + 1, nums, st, ans, ss);
    ss.pop_back();
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    vector<vector<int>> ans;
    subsets(0, nums, st, ans, {});
    return ans;
}

// DAY 4 (Path Sum 2)================================================================================

void dfs(TreeNode *node, int sum, int target, vector<int> &curr, vector<vector<int>> &ans)
{
    if (!node)
        return;

    curr.push_back(node->val);
    sum += node->val;

    if (!node->left && !node->right && sum == target)
        ans.push_back(curr);

    dfs(node->left, sum, target, curr, ans);
    dfs(node->right, sum, target, curr, ans);

    curr.pop_back();
    sum -= node->val;
}

vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    vector<vector<int>> ans;
    vector<int> curr;
    dfs(root, 0, targetSum, curr, ans);
    return ans;
}

// DAY 6 (N - ary tree Level Order Traversal)===============================================================================
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution
{
public:
    vector<vector<int>> levelOrder(Node *root)
    {
        if (!root)
            return {};

        vector<vector<int>> ans;

        queue<Node *> que;
        que.push(root);

        while (!que.empty())
        {
            int sz = que.size();
            vector<int> lvl;
            while (sz--)
            {
                Node *node = que.front();
                que.pop();
                lvl.push_back(node->val);
                for (Node *child : node->children)
                    que.push(child);
            }
            ans.push_back(lvl);
        }
        return ans;
    }
};

// DAY 7 (Palindromic Partitioning 2)=======================================================================

int minCut(string s)
{
    int n = s.size();
    vector<vector<bool>> ispal(n, vector<bool>(n, false));

    for (int gap = 0; gap < n; gap++)
    {
        for (int i = 0, j = gap; j < n; j++, i++)
        {
            if (gap == 0)
                ispal[i][j] = true;
            else if (s[i] == s[j] && gap == 1)
                ispal[i][j] = true;
            else if (s[i] == s[j] && ispal[i + 1][j - 1])
                ispal[i][j] = true;
        }
    }

    vector<int> dp(n);
    for (int i = 0; i < n; i++)
        dp[i] = i;

    for (int i = 1; i < n; i++)
    {
        if (ispal[0][i])
        {
            dp[i] = 0;
            continue;
        }
        for (int j = 1; j <= i; j++)
            if (ispal[j][i])
                dp[i] = min(dp[i], dp[j - 1] + 1);
    }
    return dp[n - 1];
}

// DAY 8 (Rank Transform of a Matrix)==============================================================================

#define f first
#define s second

int findpar(int x, vector<int> &par)
{
    if (par[x] == x)
        return x;
    return par[x] = findpar(par[x], par);
}

vector<vector<int>> matrixRankTransform(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    map<int, vector<pair<int, int>>> mat;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            mat[matrix[i][j]].push_back({i, j});

    vector<int> rank(n + m, 0);
    vector<vector<int>> ans(n, vector<int>(m, 0));
    for (auto p : mat)
    {
        vector<int> par(n + m);
        for (int i = 0; i < n + m; i++)
            par[i] = i;

        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pi = findpar(i, par), pj = findpar(j + n, par);
            par[pi] = pj;
            rank[pj] = max(rank[pi], rank[pj]);
        }
        vector<int> curr = rank;
        for (auto pt : p.s)
        {
            int i = pt.f, j = pt.s;
            int pij = findpar(i, par);
            ans[i][j] = rank[pij] + 1;
            curr[i] = rank[pij] + 1;
            curr[j + n] = rank[pij] + 1;
        }
        rank = curr;
    }
    return ans;
}

// DAY 9 (Add Strings)======================================================

string addStrings(string num1, string num2)
{
    string ans = "";
    int i = num1.size() - 1, j = num2.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0)
    {
        int x = (i >= 0) ? (num1[i--] - '0') : 0;
        int y = (j >= 0) ? (num2[j--] - '0') : 0;

        int sum = x + y + carry;
        carry = sum / 10;
        ans += char(sum % 10 + '0');
    }

    if (carry)
        ans += char(carry + '0');
    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 10 (Flip String to Monotone String)===================================================

// APPROACH 1 (Making all possible combinations of the string) --> O(n^2)
// TLE

int cost(string &a, string &b)
{
    int cost = 0;
    for (int i = 0; i < a.size(); i++)
        cost += (a[i] != b[i]);
    return cost;
}

int minFlipsMonoIncr(string s)
{
    int zeros = s.size(), ones = 0;
    int mincost = INT_MAX;
    while (zeros >= 0)
    {
        string temp = "";
        for (int i = 0; i < zeros; i++)
            temp += "0";
        for (int i = 0; i < ones; i++)
            temp += "1";
        mincost = min(mincost, cost(temp, s));
        zeros--, ones++;
    }
    return mincost;
}

// APPROACH 2 (Two variable approach)===================================================

int minFlipsMonoIncr(string s)
{
    int ones = 0, flips = 0;
    for (char c : s)
    {
        if (c == '0')
        {
            if (ones)
                flips++;
        }
        else
            ones++;
        if (ones < flips)
            flips = ones;
    }
    return flips;
}

// DAY 11 (Array of Doubled Pairs)====================================================================

bool canReorderDoubled(vector<int> &arr)
{
    sort(arr.begin(), arr.end(), [](int a, int b)
         { return abs(a) < abs(b); });
    unordered_map<int, int> m;
    for (int x : arr)
        m[x]++;

    for (int x : arr)
    {
        if (x & 1)
        {
            if (m[2 * x] == 0)
                return false;
            m[x]--;
            m[2 * x]--;
        }
        else
        {
            if (m[x] == 0)
                continue;
            if (m[2 * x] == 0)
                return false;
            m[x]--;
            m[2 * x]--;
        }
    }
    return true;
}

// DAY 12 (Group Anagrams)=====================================================================

#define ull unsigned long long

int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

ull make_hash(string &s)
{
    ull hash = 1;
    for (char c : s)
        hash *= primes[c - 'a'];
    return hash;
}

vector<vector<string>> groupAnagrams(vector<string> &strs)
{
    unordered_map<ull, vector<string>> m;
    for (string s : strs)
    {
        ull hash = make_hash(s);
        m[hash].push_back(s);
    }

    vector<vector<string>> ans;
    for (auto p : m)
        ans.push_back(p.second);

    return ans;
}

// DAY 13 (Set Matrix Zeros)============================================================================

void setZeroes(vector<vector<int>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<bool> row(n), col(m);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == 0)
                row[i] = true, col[j] = true;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (row[i] || col[j])
                matrix[i][j] = 0;
}

// DAY 14 (Remove Boxes)========================================================================================

int dfs(int i, int j, int k, vector<int> &boxes, vector<vector<vector<int>>> &dp)
{
    if (i > j)
        return 0;

    if (dp[i][j][k] != -1)
        return dp[i][j][k];

    int ans = (k + 1) * (k + 1) + dfs(i + 1, j, 0, boxes, dp);
    for (int x = i + 1; x <= j; x++)
        if (boxes[x] == boxes[i])
            ans = max(ans, dfs(i + 1, x - 1, 0, boxes, dp) + dfs(x, j, k + 1, boxes, dp));
    return dp[i][j][k] = ans;
}

int removeBoxes(vector<int> &boxes)
{
    int n = boxes.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n, -1)));
    return dfs(0, n - 1, 0, boxes, dp);
}

// DAY 15 (Minimum Sliding Window Substring)=======================================================================

string minWindow(string s, string t)
{
    unordered_map<char, int> map, tmap;
    for (char c : t)
        map[c]++, tmap[c]++;

    int match = 0, x = s.size(), y = -1;
    int j = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (map[s[i]])
        {
            if (tmap[s[i]] > 0)
                match++;
            tmap[s[i]]--;
        }
        while (j <= i && match == t.size())
        {
            if (i - j + 1 < x - y + 1)
                x = i, y = j;
            if (map[s[j]])
                if (++tmap[s[j]] > 0)
                    match--;
            j++;
        }
    }
    return y == -1 ? "" : s.substr(y, x - y + 1);
}

// DAY 16 (Range Sum Query - Immutable)===================================================================================
class NumArray
{
public:
    vector<int> psum;
    NumArray(vector<int> &nums)
    {
        psum.assign(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++)
            psum[i] = (i ? psum[i - 1] : 0) + nums[i];
    }

    int sumRange(int left, int right)
    {
        return psum[right] - (left ? psum[left - 1] : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */

// DAY 17 (Count Good Nodes in Binary Tree)====================================================================

int ans = 0;
void dfs(TreeNode *node, int mx)
{
    if (!node)
        return;
    if (node->val >= mx)
        ans++;
    dfs(node->left, max(mx, node->val));
    dfs(node->right, max(mx, node->val));
}

int goodNodes(TreeNode *root)
{
    dfs(root, INT_MIN);
    return ans;
}

// DAY 18 (Decode Ways)=============================================================

int dfs(int i, string &s, vector<int> &dp)
{
    if (i == s.size())
        return 1;
    if (s[i] == '0')
        return 0;
    if (dp[i] != -1)
        return dp[i];

    int ans = 0;
    ans += dfs(i + 1, s, dp);

    if (i != s.size() - 1)
    {
        int num = (s[i] - '0') * 10 + (s[i + 1] - '0') <= 26;
        if (num >= 1 && num <= 26)
            ans += dfs(i + 2, s, dp);
    }
    return dp[i] = ans;
}

int numDecodings(string s)
{
    vector<int> dp(s.size(), -1);
    return dfs(0, s, dp);
}

// DAY 19 (Maximum Sum of Splitted Binary Tree)=========================================================

#define ull unsigned long long

ull tsum = 0;
ull total_sum(TreeNode *node)
{
    if (!node)
        return 0;
    return total_sum(node->left) + total_sum(node->right) + node->val;
}

ull maxans = 0;
ull dfs(TreeNode *node)
{
    if (!node)
        return 0;

    ull lsum = dfs(node->left);
    ull rsum = dfs(node->right);

    ull csum = node->val + lsum + rsum;

    maxans = max(maxans, csum * (tsum - csum));

    return lsum + rsum + node->val;
}

int maxProduct(TreeNode *root)
{
    tsum = total_sum(root);
    dfs(root);

    return maxans % (1000000007);
}

// DAY 20 (Valid Sudoku)================================================================================

int row[9] = {0}, col[9] = {0}, mat[3][3] = {0};

bool isSafe(int i, int j, int n)
{
    if ((row[i] & (1 << n)) || (col[j] & (1 << n)) || (mat[i / 3][j / 3] & (1 << n)))
        return false;
    return true;
}

void set(int i, int j, int n, bool placed, vector<vector<char>> &board)
{
    if (placed)
        board[i][j] = '.';
    else
        board[i][j] = char(n + '0');

    row[i] ^= (1 << n);
    col[j] ^= (1 << n);
    mat[i / 3][j / 3] ^= (1 << n);
}

bool isValidSudoku(vector<vector<char>> &board)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != '.')
            {
                if (!isSafe(i, j, board[i][j] - '0'))
                    return false;
                set(i, j, board[i][j] - '0', false, board);
            }
        }
    }
    return true;
}

// DAY 21 (Sudoku Solver)=====================================================================================

int row[9] = {0}, col[9] = {0}, mat[3][3] = {0};

bool isSafe(int i, int j, int n)
{
    if((row[i] & (1 << n)) || (col[j] & (1 << n)) || (mat[i/3][j/3] & (1 << n)))
        return false;
    return true;
}

void set(int i, int j, int n, bool placed, vector<vector<char>> &board)
{
    board[i][j] = placed? '.' : char(n+'0');
    row[i] ^= (1 << n);
    col[j] ^= (1 << n);
    mat[i/3][j/3] ^= (1 << n);
}

bool sudoku(int x, vector<vector<char>> &board)
{
    if(x == 81) return true;
    
    int i = x/9, j = x%9;
    if(board[i][j] != '.')
        return sudoku(x+1, board);
    
    
    for(int n = 1; n <= 9; n++)
    {
        if(isSafe(i, j, n))
        {
            set(i, j, n, false, board);
            if(sudoku(x+1, board)) return true;
            set(i, j, n, true, board);
        }
    }
    return false;
}

void solveSudoku(vector<vector<char>>& board) 
{
    for(int i = 0; i < 9; i++)
        for(int j = 0; j < 9; j++)
            if(board[i][j] != '.')
                set(i, j, board[i][j]-'0', false, board);
    sudoku(0, board);
}

// DAY 23 (2 Sum 4 - Input in a BST) ==========================================================================

// APPROACH 1 --> O(n*logn)

bool find(TreeNode* root, TreeNode* node, int x)
{
    if(!root) return false;
    if(root->val == x && root != node) return true;
    if(root->val < x) return find(root->right, node, x);
    else return find(root->left, node, x);
}

bool preorder(TreeNode* root, TreeNode* node, int k)
{
    if(!node) return false;
    
    if(find(root, node, k - node->val)) return true;
    
    if(preorder(root, node->left, k)) return true;
    if(preorder(root, node->right, k)) return true;
    
    return false;
}

bool findTarget(TreeNode* root, int k) 
{
    return preorder(root, root, k);
}

// APPROACH 2 --> O(n)

void preorder(TreeNode* node, int k, vector<int> &arr)
{
    if(!node) return;
    
    preorder(node->left, k, arr);
    arr.push_back(node->val);
    preorder(node->right, k, arr);
    
    return;
}

bool findTarget(TreeNode* root, int k) 
{
    vector<int> arr;
    preorder(root, k, arr);
    
    int i = 0, j = arr.size()-1;
    
    while(i < j)
    {
        if(arr[i] + arr[j] == k) return true;
        if(arr[i] + arr[j] < k) i++;
        else j--;
    }
    return false;
}
