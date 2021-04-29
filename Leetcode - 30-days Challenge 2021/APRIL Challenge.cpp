
// DAY 1 (Palindrome Linked List)===============================================================

// METHOD 1 (Using Extra Space (Stack))
bool isPalindrome(ListNode *head)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        n++;
        itr = itr->next;
    }
    int i = 0;
    ListNode *tmp = head;
    stack<int> st;
    while (i++ < n / 2)
    {
        st.push(tmp->val);
        tmp = tmp->next;
    }

    if (n & 1)
        tmp = tmp->next;
    while (tmp && !st.empty())
    {
        if (tmp->val != st.top())
            return false;
        tmp = tmp->next;
        st.pop();
    }
    return (st.empty() && !tmp);
}

// METHOD 2 (Const Extra Space) -- (By reversing the lower half of LL)

bool isPalindrome(ListNode *head)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        n++;
        itr = itr->next;
    }
    int i = 0;
    ListNode *tmp = head;
    ListNode *curr = head, *prev = nullptr, *forw = head;

    while (i++ < n / 2)
    {
        tmp = tmp->next;
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    ListNode *tmp1 = prev;

    if (n & 1)
        tmp = tmp->next;
    while (tmp && tmp1)
    {
        // cout<<tmp->val<<" "<<tmp1->val;
        if (tmp->val != tmp1->val)
            return false;
        tmp = tmp->next;
        tmp1 = tmp1->next;
    }
    return (!tmp && !tmp1);
}

// DAY 2 (Ones and Zeros)====================================================================

// APPROACH 1 (Subsequence Method) --> O(2^n)
// TLE
int subseq(int i, vector<pair<int, int>> &v01, int n, int m)
{
    if (i == v01.size())
        return 0;

    int ans = 0;
    if (n - v01[i].first >= 0 && m - v01[i].second >= 0)
        ans = subseq(i + 1, v01, n - v01[i].first, m - v01[i].second) + 1;
    ans = max(ans, subseq(i + 1, v01, n, m));

    return ans;
}

int findMaxForm(vector<string> &strs, int m, int n)
{
    int sz = strs.size();
    cout << sz << endl;
    vector<pair<int, int>> v01(sz);
    for (int i = 0; i < sz; i++)
    {
        int c0 = 0, c1 = 0;
        for (char c : strs[i])
        {
            if (c == '0')
                c0++;
            else
                c1++;
        }
        v01[i] = {c0, c1};
    }

    return subseq(0, v01, m, n);
}

// METHOD 2 (3D - DP)
// AC

int subseq(int i, vector<pair<int, int>> &v01, int m, int n, vector<vector<vector<int>>> &dp)
{
    if (i == v01.size())
        return dp[i][m][n] = 0;
    if (dp[i][m][n] != -1)
        return dp[i][m][n];
    int ans = 0;
    if (m - v01[i].first >= 0 && n - v01[i].second >= 0)
        ans = subseq(i + 1, v01, m - v01[i].first, n - v01[i].second, dp) + 1;
    ans = max(ans, subseq(i + 1, v01, m, n, dp));

    return dp[i][m][n] = ans;
}

int findMaxForm(vector<string> &strs, int m, int n)
{
    int sz = strs.size();
    // cout<<sz<<endl;
    vector<pair<int, int>> v01(sz);
    for (int i = 0; i < sz; i++)
    {
        int c0 = 0, c1 = 0;
        for (char c : strs[i])
        {
            if (c == '0')
                c0++;
            else
                c1++;
        }
        v01[i] = {c0, c1};
    }

    vector<vector<vector<int>>> dp(sz + 1, (vector<vector<int>>(m + 1, vector<int>(n + 1, -1))));
    return subseq(0, v01, m, n, dp);
}

// DAY 3 (Longest Valid Parenthesis)===================================================================================

// METHOD 1 (Using Stack of pair)
int longestValidParentheses(string s)
{
    stack<pair<int, int>> st;
    int ans = 0, len = 0, plen = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
        {
            st.push({i, plen});
            plen = 0;
        }
        else
        {
            if (st.empty())
            {
                plen = 0;
                continue;
            }
            len = (i - st.top().first + 1) + st.top().second;
            ans = max(ans, len);
            plen = len;
            st.pop();
        }
    }
    return ans;
}

// METHOD 2 (SHORTER, CONCISE AND OPTIMIZED WAY)

int longestValidParentheses(string s)
{
    stack<int> st;
    st.push(-1);
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            st.push(i);
        else
        {
            if (!st.empty())
                st.pop();
            if (st.empty())
                st.push(i);
            else
                ans = max(ans, i - st.top());
        }
    }
    return ans;
}

// DAY 4 (Design Circular Queue)========================================================
class MyCircularQueue
{
public:
    vector<int> arr;
    int n;
    int si, ei;
    MyCircularQueue(int k)
    {
        arr.reserve(k);
        si = -1, ei = -1;
        n = k;
    }

    bool enQueue(int value)
    {
        if ((ei + 1) % n == si)
            return false;
        if (si == -1)
            si++;
        ei = (ei + 1) % n;
        arr[ei] = value;
        return true;
    }

    bool deQueue()
    {
        if (si == -1)
            return false;
        if (si == ei)
            si = -1, ei = -1;
        else
            si = (si + 1) % n;
        return true;
    }

    int Front()
    {
        return (si == -1) ? -1 : arr[si];
    }

    int Rear()
    {
        return (ei == -1) ? -1 : arr[ei];
    }

    bool isEmpty()
    {
        return (si == -1);
    }

    bool isFull()
    {
        return ((ei + 1) % n == si);
    }
};

/**
 * Your MyCircularQueue object will be instantiated and called as such:
 * MyCircularQueue* obj = new MyCircularQueue(k);
 * bool param_1 = obj->enQueue(value);
 * bool param_2 = obj->deQueue();
 * int param_3 = obj->Front();
 * int param_4 = obj->Rear();
 * bool param_5 = obj->isEmpty();
 * bool param_6 = obj->isFull();
 */

// DAY 5 (Global and Local Inversions)=====================================================

// APPROACH 1 (Brute Force) --> O(n^2)
// TLE

bool isIdealPermutation(vector<int> &A)
{
    int n = A.size();
    for (int i = 0; i < n - 2; i++)
        for (int j = i + 2; j < n; j++)
            if (A[j] < A[i])
                return false;
    return true;
}

// APPROACH 2 (Ideal Permutation) --> O(n)

bool isIdealPermutation(vector<int> &A)
{
    int n = A.size();
    for (int i = 0; i < n; i++)
        if (abs(A[i] - i) > 1)
            return false;
    return true;
}

// DAY 6 (Minimum operation to Make Array Equal)==================================================================

int minOperations(int n)
{
    int ans = 0;
    int x = 1, i = 0;
    for (int i = 0; i < n / 2; i++)
        ans += n - x, x += 2;
    return ans;
}

// DAY 7 (Determine if String Halves are Alike)=========================================================================

bool isalpha(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

bool halvesAreAlike(string s)
{
    int n = s.size(), cnt = 0;
    for (int i = 0, j = n / 2; i < n / 2 && j < n; i++, j++)
    {
        if (isalpha(tolower(s[i])))
            cnt++;
        if (isalpha(tolower(s[j])))
            cnt--;
    }
    return cnt == 0;
}

// DAY 8 (Letter Combinations of a Phone Number)=============================================================================

void combinations(int i, string ans, string &digits, vector<string> &keypad, vector<string> &combs)
{
    if (i == digits.size())
    {
        if (!ans.empty())
            combs.push_back(ans);
        return;
    }
    for (int j = 0; j < keypad[digits[i] - '0'].size(); j++)
        combinations(i + 1, ans + keypad[digits[i] - '0'][j], digits, keypad, combs);
}

vector<string> letterCombinations(string digits)
{
    vector<string> keypad = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
    vector<string> combs;
    combinations(0, "", digits, keypad, combs);
    return combs;
}

// DAY 9 (Verifying an Alien Dictionary)===========================================================================================

bool compare(string &a, string &b, vector<int> &m)
{
    int i = 0, j = 0;
    while (i < a.size() || j < b.size())
    {
        // cout<<a[i]<<" "<<b[j]<<": "<<endl;
        if (i == a.size())
            return true;
        if (j == b.size())
            return false;
        if (m[b[j] - 'a'] < m[a[i] - 'a'])
            return false;
        if (m[b[j++] - 'a'] > m[a[i++] - 'a'])
            return true;
    }
    return true;
}

bool isAlienSorted(vector<string> &words, string order)
{
    vector<int> m(26, 26);
    for (int i = 0; i < order.size(); i++)
        m[order[i] - 'a'] = i;
    for (int i = 0; i < words.size() - 1; i++)
        if (!compare(words[i], words[i + 1], m))
            return false;
    return true;
}

// DAY 10 (Longest Increasing Path in a Matrix)=========================================================================================

// APPROACH 1 (Void Type)
// TLE
void dfs(int i, int j, int len, int &maxlen, int n, int m, vector<vector<int>> &arr)
{
    maxlen = max(maxlen, len);
    // cout<<len<<", ";
    // cout<<maxlen<<endl;
    if ((i + 1 != n) && (arr[i + 1][j] > arr[i][j]))
        dfs(i + 1, j, len + 1, maxlen, n, m, arr);
    if ((j + 1 != m) && (arr[i][j + 1] > arr[i][j]))
        dfs(i, j + 1, len + 1, maxlen, n, m, arr);
    if ((i - 1 != -1) && (arr[i - 1][j] > arr[i][j]))
        dfs(i - 1, j, len + 1, maxlen, n, m, arr);
    if ((j - 1 != -1) && (arr[i][j - 1] > arr[i][j]))
        dfs(i, j - 1, len + 1, maxlen, n, m, arr);
}

int longestIncreasingPath(vector<vector<int>> &matrix)
{
    int maxlen = 1;
    int n = matrix.size();
    int m = matrix[0].size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            dfs(i, j, 1, maxlen, n, m, matrix);
            // cout<<endl;
        }
    }
    return maxlen;
}

// APPROACH 2 (DP)
// AC

int dfs(int i, int j, int prev, int n, int m, vector<vector<int>> &arr, vector<vector<int>> &dp)
{
    if (i == n || j == m || i == -1 || j == -1 || arr[i][j] <= prev)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    int maxi = max({dfs(i + 1, j, arr[i][j], n, m, arr, dp),
                    dfs(i, j + 1, arr[i][j], n, m, arr, dp),
                    dfs(i - 1, j, arr[i][j], n, m, arr, dp),
                    dfs(i, j - 1, arr[i][j], n, m, arr, dp)});
    return dp[i][j] = maxi + 1;
}

int longestIncreasingPath(vector<vector<int>> &matrix)
{
    int maxlen = 1;
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            maxlen = max(maxlen, dfs(i, j, -1, n, m, matrix, dp));
    return maxlen;
}

// DAY 11 (Deepest Leaves Sum)==========================================================

// APPROACH 1 (DFS)

void dfs(int level, int &maxlevel, int &sum, TreeNode *node)
{
    if (!node)
        return;
    if (level > maxlevel)
    {
        maxlevel = level;
        sum = node->val;
    }
    else if (level == maxlevel)
        sum += node->val;
    dfs(level + 1, maxlevel, sum, node->left);
    dfs(level + 1, maxlevel, sum, node->right);
}

int deepestLeavesSum(TreeNode *root)
{
    int sum = 0, maxlevel = -1;
    dfs(0, maxlevel, sum, root);
    return sum;
}

// APPROACH 2 (BFS)

int deepestLeavesSum(TreeNode *root)
{
    queue<TreeNode *> que;
    que.push(root);
    int ans = 0;
    while (!que.empty())
    {
        int sz = que.size();
        int sum = 0;
        while (sz--)
        {
            TreeNode *top = que.front();
            sum += top->val;
            que.pop();
            if (top->left)
                que.push(top->left);
            if (top->right)
                que.push(top->right);
        }
        ans = sum;
    }
    return ans;
}

// DAY 12 (Beautiful Arrangement 2)=========================================================================

// METHOD 1 (By Keeping difference variable)
vector<int> constructArray(int n, int k)
{
    vector<int> ans(n);
    int d = n - 1, x = 1;
    ans[0] = 1;
    int i = 1;
    while (i < n && --k)
    {
        ans[i] = ans[i - 1] + d;
        // cout<<ans[i]<<" "<<d<<endl;
        i++;
        d = d < 0 ? -(d + 1) : -(d - 1);
    }
    d = (d < 0) ? -1 : 1;
    while (i < n)
        ans[i] = ans[i - 1] + d, i++;
    return ans;
}

// METHOD 2 (Using 2 Pointers)

vector<int> constructArray(int n, int k)
{
    vector<int> ans(n);
    int a = 1, b = n;
    for (int i = 0; i < n; i++)
        ans[i] = (k > 1) ? ((k-- % 2) ? a++ : b--) : a++;
    return ans;
}

// DAY 13 (Flatten Nested List Iterator)===============================================

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator
{
public:
    vector<int> ans;
    int idx;

    void flatten(vector<NestedInteger> list)
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i].isInteger())
                ans.push_back(list[i].getInteger());
            else
                flatten(list[i].getList());
        }
    }

    NestedIterator(vector<NestedInteger> &nestedList)
    {
        flatten(nestedList);
        idx = 0;
    }

    int next()
    {
        return ans[idx++];
    }

    bool hasNext()
    {
        return idx < ans.size();
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */

// DAY 14 (Partition List)========================================================================

ListNode *partition(ListNode *head, int x)
{
    ListNode *l = new ListNode(INT_MIN), *li = l;
    ListNode *r = new ListNode(INT_MIN), *ri = r;
    ListNode *itr = head;
    while (itr)
    {
        // cout<<itr->val<<endl;
        if (itr->val < x)
        {
            li->next = new ListNode(itr->val);
            li = li->next;
        }
        else
        {
            ri->next = new ListNode(itr->val);
            ri = ri->next;
        }
        itr = itr->next;
    }
    l = l->next;
    r = r->next;
    li->next = r;
    return l ? l : r;
}

// DAY 15 (Fibonacci Numbers)===============================================================================

// APPROACH 1 (Recursive) --> O(2^n)

int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

// APPROACH 2 (2 pointers) --> O(n)

int fib(int n)
{
    if (n == 0 || n == 1)
        return n;
    int a = 0, b = 1, ans = 0;
    while (--n)
    {
        ans = a + b;
        a = b;
        b = ans;
    }
    return ans;
}

// APPROACH 3 (Using Benit's Formula) --> O(1)  (Not right for large values of n)

int fib(int n)
{
    int bf = round((pow((1 + sqrt(5)) / 2, n)) / sqrt(5));
    return bf;
}

// APPROACH 4 (Matrix Exponentiation)  --> O(logn)

vector<vector<int>> mult(vector<vector<int>> &A, vector<vector<int>> &B)
{
    int a = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    int b = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    int c = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    int d = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    A = {{a, b}, {c, d}};
    return A;
}

int binpow(vector<vector<int>> &A, int n)
{
    vector<vector<int>> ans = {{1, 0}, {0, 1}}; // Identity Matrix
    while (n)                                   // Binary Exponentiation
    {
        if (n & 1)
            ans = mult(ans, A);
        A = mult(A, A);
        n >>= 1;
    }
    // cout<<ans[0][0]<<" "<<ans[0][1]<<endl;
    // cout<<ans[1][0]<<" "<<ans[1][1]<<endl;
    // cout<<endl;
    return ans[0][0];
}

int fib(int n)
{
    if (n <= 1)
        return n;
    vector<vector<int>> A = {{1, 1}, {1, 0}};
    return binpow(A, n - 1);
}

// DAY 16 (Remove all Adjacent Duplicates in String 2)============================================================

// APPROACH 1 (Using Stack) --> O(n*k)

string removeDuplicates(string s, int k)
{
    int n = s.size();
    stack<pair<char, int>> st;
    for (int i = 0; i < n; i++)
    {
        st.push({s[i], (st.empty() || (st.top().first != s[i])) ? 1 : st.top().second + 1});
        if (st.top().second == k)
        {
            for (int j = 0; j < k; j++)
                st.pop();
        }
    }
    string ans = "";
    while (!st.empty())
    {
        ans += st.top().first;
        st.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

// APPROACH 2 (Without Stack -- Naive Approach) --> >O(n^2)

string removeDuplicates(string s, int k)
{
    int n = s.size();
    bool f = true;
    while (f)
    {
        f = false;
        int x = 1;
        for (int i = 1; i < s.size(); i++)
        {
            if (s[i] == s[i - 1])
            {
                if (++x == k)
                {
                    f = true;
                    s = s.substr(0, i - (k - 1)) + s.substr(i + 1);
                }
            }
            else
                x = 1;
        }
    }
    return s;
}

// DAY 17(Number of Matrices that sum to n)====================================================================================

// APPROACH --> (Similar to 1D array problem whih was of O(n)) --> O(n^2)
int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            matrix[i][j] += matrix[i][j - 1];
    unordered_map<int, int> sums;
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i; j < m; j++)
        {
            int csum = 0;
            sums[0] = 1;
            for (int k = 0; k < n; k++)
            {
                csum += matrix[k][j] - (i ? matrix[k][i - 1] : 0);
                ans += sums[csum - target];
                sums[csum]++;
            }
            sums.clear();
        }
    }
    return ans;
}

// DAY 18 (Remove nth Node from End of the List)========================================================================

ListNode *removeNthFromEnd(ListNode *head, int n)
{
    int sz = 0;
    ListNode *itr = head;
    while (itr)
    {
        sz++;
        itr = itr->next;
    }
    int x = sz - n;
    ListNode *curr = head, *prev = nullptr;
    while (x--)
    {
        prev = curr;
        curr = curr->next;
    }
    if (prev)
        prev->next = curr->next;
    else
        head = head->next;

    return head;
}

// DAY 19 (Combination Sum 4)====================================================================

// METHOD 1 (Bottom-Up -- Coin change - Permutation of infinite coins) --> O(n^n)
// TLE

int combinationSum4(vector<int> &nums, int target)
{
    if (target == 0)
        return 1;
    int count = 0;
    for (int i = 0; i < nums.size(); i++)
        if (target - nums[i] >= 0)
            count += combinationSum4(nums, target - nums[i]);
    return count;
}

// METHOD 2 (Top-Down) --> O(n*target)

int combinationSum4(vector<int> &nums, int target)
{
    vector<unsigned int> dp(target + 1, 0);
    dp[0] = 1;
    for (int tar = 1; tar <= target; tar++)
        for (int i = 0; i < nums.size(); i++)
            if (tar - nums[i] >= 0)
                dp[tar] += dp[tar - nums[i]];
    return dp[target];
}

// DAY 20 (N-ary Tree Preorder Traversal)===========================================================

// APPROACH 1 (Recursively - DFS)  --> O(n)
void preorder_(Node *node, vector<int> &ans)
{
    if (!node)
        return;
    ans.push_back(node->val);
    for (Node *n : node->children)
        preorder_(n, ans);
}

vector<int> preorder(Node *root)
{
    vector<int> ans;
    preorder_(root, ans);
    return ans;
}

// APPROACH 2 (Iteratively - Using Stack) --> O(n)-----------------------------------------

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
    vector<int> preorder(Node *root)
    {
        if (!root)
            return {};
        vector<int> ans;
        stack<Node *> st;
        st.push(root);
        while (!st.empty())
        {
            Node *node = st.top();
            st.pop();
            ans.push_back(node->val);
            for (int i = node->children.size() - 1; i >= 0; i--)
                st.push(node->children[i]);
        }
        return ans;
    }
};

// DAY 21 (Triangle)=====================================================================================

// APPROACH 1 (2D DP)

int dfs(int i, int j, vector<vector<int>> &cost, vector<vector<int>> &dp)
{
    if (i == cost.size())
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    int l = dfs(i + 1, j, cost, dp);
    int r = dfs(i + 1, j + 1, cost, dp);

    return dp[i][j] = cost[i][j] + min(l, r);
}

int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return dfs(0, 0, triangle, dp);
}

// APPROACH 2 (1D DP)

int dfs(int i, int j, int n, vector<vector<int>> &cost, vector<int> &dp)
{
    for (int i = n - 1; i >= 0; i--)
        for (int j = 0; j <= i; j++)
            dp[j] = cost[i][j] + min(dp[j], dp[j + 1]);
    return dp[0];
}

int minimumTotal(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<int> dp(n + 1, 0);
    return dfs(0, 0, n, triangle, dp);
}

// DAY 22 (Brikc Wall)=========================================================================

int leastBricks(vector<vector<int>> &wall)
{
    int n = wall.size();
    int nocross = 0;
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < wall[i].size() - 1; j++)
        {
            wall[i][j] += (j == 0) ? 0 : wall[i][j - 1];
            m[wall[i][j]]++;
            nocross = max(nocross, m[wall[i][j]]);
        }
    }
    return n - nocross;
}

// DAY 23 (Count Binary Strings)========================================================================

int countBinarySubstrings(string s)
{
    int ans = 0;
    int i = 0, n = s.size();
    char c = s[0];
    int cnt[2] = {0, 0};
    while (i < n)
    {
        cnt[c - '0'] = 0;

        while (i < n && s[i] == c)
            cnt[c - '0']++, i++;
        c = (((c - '0') + 1) % 2) + '0';
        ans += min(cnt[0], cnt[1]);

        // cout<<cnt[0]<<", "<<cnt[1]<<": "<<endl;
    }
    // cout<<endl;
    return ans;
}

// DAY 24 (critical Connections in a Network)======================================================================

vector<vector<int>> gp;
vector<int> disc;
vector<int> low;
vector<int> par;
vector<vector<int>> ans;
void tarjan(int u)
{
    static int time = 0;
    disc[u] = low[u] = time++;

    for (int v : gp[u])
    {
        if (disc[v] == -1)
        {
            par[v] = u;
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (disc[u] < low[v])
                ans.push_back({u, v});
        }
        else if (par[u] != v)
            low[u] = min(low[u], disc[v]);
    }
}

vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
{
    gp.resize(n);
    disc.resize(n, -1);
    low.resize(n);
    par.resize(n);
    for (vector<int> v : connections)
    {
        gp[v[0]].push_back(v[1]);
        gp[v[1]].push_back(v[0]);
    }
    vector<int> disc(n, -1), low(n), par(n);
    for (int i = 0; i < n; i++)
        if (disc[i] == -1)
            tarjan(i);
    return ans;
}

// DAY 25 (Rotate Image)========================================================================

// APPROACH 1 (Taking Strips for every level)

void rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int sr = 0, sc = 0, er = n - 1, ec = n - 1;
    int x = n;
    while (x > 1)
    {
        int m = 4 * x - 4;
        vector<int> strip(m);
        int i = sr, j = sc, k = 0;
        while (j <= ec)
            strip[k++] = matrix[i][j++];
        i++, j--;
        while (i <= er)
            strip[k++] = matrix[i++][j];
        j--, i--;
        while (j >= sc)
            strip[k++] = matrix[i][j--];
        i--, j++;
        while (i > sr)
            strip[k++] = matrix[i--][j];
        i++;

        // for(int x : strip) cout<<x<<" ";
        // cout<<endl;

        i = sr, j = sc, k = m - (x - 1);
        while (j <= ec)
            matrix[i][j++] = strip[k++ % m];
        i++, j--;
        while (i <= er)
            matrix[i++][j] = strip[k++ % m];
        j--, i--;
        while (j >= sc)
            matrix[i][j--] = strip[k++ % m];
        i--, j++;
        while (i > sr)
            matrix[i--][j] = strip[k++ % m];
        i++;

        x -= 2;
        sr++, sc++, er--, ec--;
    }
}

// APPROAH 2 (OPTIMIZED and COMPACT)

void rotate(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            swap(matrix[i][j], matrix[j][i]);
    for (int i = 0; i < n; i++)
        reverse(matrix[i].begin(), matrix[i].end());
}

// DAY 26 (Furthest building you can reach)====================================================

// APPROACH 1 (Subsequence) --> O(2^n)
// TLE

int subseq(int i, vector<int> &heights, int bricks, int ladders)
{
    if (i == heights.size() - 1)
        return i;
    int diff = heights[i + 1] - heights[i];
    // cout<<bricks<<" "<<ladders<<endl;
    // cout<<i<<" -> "<<diff<<endl;

    int exc = i;
    int inclad = i, incbrick = i;
    if (diff <= 0)
        exc = subseq(i + 1, heights, bricks, ladders);
    else
    {
        if (ladders - 1 >= 0)
            inclad = subseq(i + 1, heights, bricks, ladders - 1);
        if (bricks - diff >= 0)
            incbrick = subseq(i + 1, heights, bricks - diff, ladders);
    }

    return max(exc, max(inclad, incbrick));
}

int furthestBuilding(vector<int> &heights, int bricks, int ladders)
{
    return subseq(0, heights, bricks, ladders);
}

// APPROACH 2 (Using Min heap) --> <O(n*logn)
// AC

int furthestBuilding(vector<int> &heights, int bricks, int ladders)
{
    int n = heights.size();
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < n - 1; i++)
    {
        int diff = heights[i + 1] - heights[i];
        if (diff <= 0)
            continue;
        if (ladders)
        {
            pq.push(diff);
            ladders--;
        }
        else if (!pq.empty() && diff > pq.top())
        {
            bricks -= pq.top();
            pq.pop();
            pq.push(diff);
        }
        else
            bricks -= diff;
        if (bricks < 0)
            return i;
    }
    return n - 1;
}

// DAY 27 (Power of Three)=====================================================================

// APPROACH 1 (Using loops)
bool isPowerOfThree(int n)
{
    if (n <= 0)
        return false;
    while (n % 3 == 0)
        n /= 3;
    return (n == 1);
}

// APPROACH 2 (Without loops, checking multiplicity of n with th largest value of power of 3, possible with n)

bool isPowerOfThree(int n)
{
    if (n <= 0)
        return false;
    int maxi = pow(3, 19);
    return (maxi % n == 0);
}

// DAY 29 (Find First and Last Position of Element in Sorted Array)=============================================================================

vector<int> searchRange(vector<int> &nums, int target)
{
    int si = -1, ei = -1;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == target)
        {
            if (si == -1)
                si = i;
            ei = i;
        }
    }
    return {si, ei};
}