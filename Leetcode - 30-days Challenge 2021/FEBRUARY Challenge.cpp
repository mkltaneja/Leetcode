// DAY 1 (Number of 1 Bits)================================================================

// in C++
int hammingWeight(uint32_t n)
{
    int cnt = 0;
    while (n)
    {
        cnt++;
        n &= (n - 1);
    }
    return cnt;
}

// in Java
// you need to treat n as an unsigned value
public
int hammingWeight(int n)
{
    int cnt = 0;
    if ((n & (1 << 31)) != 0)
    {
        n ^= (1 << 31);
        cnt++;
    }
    System.out.println(n);
    while (n > 0)
    {
        cnt++;
        n &= (n - 1);
    }
    return cnt;
}
// OR
public
int hammingWeight(int n)
{
    return Integer.bitCount(n);
}

// DAY 2 (Trim a Binary Search Tree)=====================================================

TreeNode *trimBST(TreeNode *root, int low, int high)
{
    if (!root)
        return nullptr;
    if (root->val < low)
        return trimBST(root->right, low, high);
    if (root->val > high)
        return trimBST(root->left, low, high);
    root->left = trimBST(root->left, low, high);
    root->right = trimBST(root->right, low, high);
    return root;
}

// DAY 3 (Linked List Cycle)===================================================================

bool hasCycle(ListNode *head)
{
    ListNode *slow = head, *fast = head;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if (slow == fast)
            return true;
    }
    return false;
}

// DAY 4 (Longest Harmonious Subsequence)===============================================================

// APPROACH 1 (taking record of maximum and minimum) --> O(n^2)
// TLE
int findLHS(vector<int> &nums)
{
    int n = nums.size();
    int maxlen = 0;
    for (int i = 0; i < n; i++)
    {
        int a = nums[i], b = nums[i] - 1, c = nums[i] + 1;
        int ca = 1, cb = 0, cc = 0;
        for (int j = i + 1; j < n; j++)
        {
            if (nums[j] == a)
                ca++;
            else if (nums[j] == b)
                cb++;
            else if (nums[j] == c)
                cc++;

            if (cb != 0)
                maxlen = max(maxlen, ca + cb);
            if (cc != 0)
                maxlen = max(maxlen, ca + cc);
        }
    }
    return maxlen;
}

// APPROACH 2 (By Sorting) --> O(nlogn + n)
// AC

int findLHS(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    long maxlen = 0;
    int i = 0;
    long prev = INT_MIN, curr = nums[i];
    long prevcnt = 0, currcnt = 0;
    while (i < n)
    {
        while (i < n && nums[i] == curr)
        {
            currcnt++;
            i++;
        }
        maxlen = (curr - prev == 1) ? max(maxlen, prevcnt + currcnt) : maxlen;
        prev = curr;
        prevcnt = currcnt;
        currcnt = 0;
        if (i < n)
            curr = nums[i];
    }
    return maxlen;
}

// DAY 5 (Simply Path)=============================================

string simplifyPath(string path)
{
    string ans = "";
    deque<string> que;
    stringstream ss(path);
    string file;
    while (getline(ss, file, '/'))
    {
        if (file == "." || file == "")
            continue;
        if (file == "..")
        {
            if (!que.empty())
                que.pop_back();
        }
        else
            que.push_back(file);
    }
    while (!que.empty())
    {
        ans += "/";
        ans += que.front();
        que.pop_front();
    }
    return ans.empty() ? "/" : ans;
}

// DAY 6 (Binary Tree Right Side View)
vector<int> rightSideView(TreeNode *root)
{
    if (!root)
        return {};
    vector<int> ans;
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            TreeNode *node = que.front();
            que.pop();
            if (sz == 0 && node)
                ans.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
    }
    return ans;
}

// DAY 7 (Shortest Distance to a Character)==================================================================

// APPROACH 1 (BFS) --> O(2*n)
// AC

#define f first
#define s second
vector<int> shortestToChar(string s, char c)
{
    int n = s.size();
    queue<pair<int, int>> que;
    vector<int> dists(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (s[i] == c)
        {
            que.push({i, 0});
            dists[i] = 0;
        }
    }

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        // dists[p.f] = p.s;
        // cout<<p.f<<" "<<dists[p.f]<<endl;
        if (p.f > 0 && dists[p.f - 1] == -1 && s[p.f - 1] != c)
        {
            que.push({p.f - 1, p.s + 1});
            dists[p.f - 1] = p.s + 1;
        }
        if (p.f < n - 1 && dists[p.f + 1] == -1 && s[p.f + 1] != c)
        {
            que.push({p.f + 1, p.s + 1});
            dists[p.f + 1] = p.s + 1;
        }
    }
    // cout<<endl;
    return dists;
}

// APPROACH 2 (Min Array)
// AC

vector<int> shortestToChar(string s, char c)
{
    int n = s.size();
    vector<int> a(n), b(n);
    int count = n;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != c)
            a[i] = ++count;
        else
            a[i] = count = 0;
    }
    count = n;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] != c)
            b[i] = ++count;
        else
            b[i] = count = 0;
    }
    for (int i = 0; i < n; i++)
        a[i] = min(a[i], b[i]);
    return a;
}

// DAY 8 (Peeking Iterator)=====================================================
/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator
{
public:
    int nxt;
    bool hasnxt;
    PeekingIterator(const vector<int> &nums) : Iterator(nums)
    {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
        nxt = Iterator::next();
        hasnxt = Iterator::hasNext();
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        return nxt;
    }

    // hasNext() and next() should behave the same as in the Iterator interface.
    // Override them if needed.
    int next()
    {
        int ans = nxt;
        hasnxt = Iterator::hasNext();
        if (hasnxt)
            nxt = Iterator::next();
        return ans;
    }

    bool hasNext() const
    {
        return hasnxt;
    }
};

// DAY 9 (Convert BST to Greater Tree)============================================================

// Method 1 --> O(2n)

void convertBST(TreeNode *node, int rootval)
{
    if (!node)
        return;
    convertBST(node->right, rootval);
    TreeNode *temp = node->right;
    while (temp && temp->left)
        temp = temp->left;
    node->val += (!node->right ? rootval : 0) + (temp ? temp->val : 0);
    cout << node->val << " " << rootval << endl;
    convertBST(node->left, node->val);

    return;
}

TreeNode *convertBST(TreeNode *root)
{
    convertBST(root, 0);
    return root;
}

// METHOD 2 --> O(n)

int sum = 0;
TreeNode *convertBST(TreeNode *root)
{
    if (!root)
        return nullptr;

    convertBST(root->right);
    sum += root->val;
    root->val = sum;
    convertBST(root->left);

    return root;
}

// DAY 10 (Copy List with Random Pointer)===============================================================

// METHOD 1 (By Changing the origninal values of head node to count of their position from start)

Node *copyRandomList(Node *head)
{
    if (!head)
        return nullptr;
    Node *node = new Node(-1), *ans = node;
    Node *temp = head;
    int count = 0;
    while (temp)
    {
        // node->random = temp->random;
        node->next = new Node(temp->val);
        temp->val = count++;
        node = node->next;
        temp = temp->next;
    }
    ans = ans->next;
    temp = head;
    node = ans;
    while (temp)
    {
        Node *t = ans;
        if (!temp->random)
            t = nullptr;
        else
        {
            int cnt = temp->random->val;
            while (cnt--)
                t = t->next;
        }
        node->random = t;
        node = node->next;
        temp = temp->next;
    }
    return ans;
}

// METHOD 2 (Using Map to store the head nodes)

Node *copyRandomList(Node *head)
{
    unordered_map<Node *, Node *> m;
    Node *node = head, *ans = nullptr, *prev = nullptr;
    while (node)
    {
        Node *nnode = new Node(node->val);
        m[node] = nnode;
        if (!ans)
            ans = nnode;
        else
            prev->next = nnode;
        prev = nnode;
        node = node->next;
    }
    node = head;
    Node *temp = ans;
    while (node)
    {
        temp->random = m[node->random];
        node = node->next;
        temp = temp->next;
    }
    return ans;
}

// DAY 11 (Valid Anagram)======================================================

bool isAnagram(string s, string t)
{
    if (s.size() != t.size())
        return false;
    vector<int> m(26, 0);
    for (char c : s)
        m[c - 'a']++;
    for (char c : t)
        m[c - 'a']--;

    for (int x : m)
        if (x != 0)
            return false;

    return true;
}

// DAY 12 (Number of Steps to Reduce a Number to Zero)===========================================================

// METHOD 1 (BFS) --> O(2*log(num))

int numberOfSteps(int num)
{
    queue<pair<int, int>> que;
    que.push({num, 0});
    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        if (p.first == 0)
            return p.second;
        if (p.first & 1)
            que.push({p.first - 1, p.second + 1});
        else
            que.push({p.first / 2, p.second + 1});
    }
    return 0;
}

// METHOD 2 (Recursion) --> O(2*log(num))

int numberOfSteps(int num)
{
    if (num == 0)
        return 0;
    if (num & 1)
        return numberOfSteps(num - 1) + 1;
    else
        return numberOfSteps(num / 2) + 1;
}

// DAY 13 (Shortest Path in Binary Matrix)============================================================================

#define f first
#define s second
int shortestPathBinaryMatrix(vector<vector<int>> &grid)
{
    int n = grid.size();
    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
        return -1;
    queue<pair<int, int>> que;
    que.push({0, 1}); // coordinate,count
    grid[0][0] = 1;

    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        int i = p.f / n;
        int j = p.f % n;
        if (i == n - 1 && j == n - 1)
            return p.s;
        for (int d = 0; d < 8; d++)
        {
            int x = i + dir[d][0], y = j + dir[d][1];
            if (x < n && x >= 0 && y < n && y >= 0 && grid[x][y] == 0)
            {
                grid[x][y] = 1;
                que.push({x * n + y, p.s + 1});
            }
        }
    }
    return -1;
}

// DAY 14 (Is Graph Bipartite?)============================================================

// APPROACH 1 (BFS) --> O(2n)
bool bfs(int src, vector<int> &code, vector<vector<int>> &gp)
{
    queue<int> que;
    que.push(src);
    code[src] = 0;
    while (!que.empty())
    {
        int x = que.front();
        que.pop();
        for (int y : gp[x])
        {
            if (code[y] == -1)
            {
                code[y] = (code[x] + 1) % 2;
                que.push(y);
            }
            else if (code[y] == code[x])
                return false;
        }
    }
    return true;
}

bool isBipartite(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> code(n, -1);
    for (int i = 0; i < n; i++)
        if (code[i] == -1)
            if (!bfs(i, code, graph))
                return false;
    return true;
}

// APPROACH 2 (DFS) --> O(2n)

bool dfs(int src, vector<int> &code, vector<vector<int>> &gp)
{
    for (int v : gp[src])
    {
        if (code[v] == -1)
        {
            code[v] = (code[src] + 1) % 2;
            if (!dfs(v, code, gp))
                return false;
        }
        else if (code[v] == code[src])
            return false;
    }
    return true;
}

bool isBipartite(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<int> code(n, -1);
    for (int i = 0; i < n; i++)
    {
        if (code[i] == -1)
        {
            code[i] = 0;
            if (!dfs(i, code, graph))
                return false;
        }
    }
    return true;
}

// DAY 15 (The K weakest Rows in a Matrix)============================

#define f first
#define s second

class comp
{
public:
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return (a.f == b.f) ? (a.s > b.s) : (a.f > b.f);
    }
};

vector<int> kWeakestRows(vector<vector<int>> &mat, int k)
{
    int n = mat.size(), m = mat[0].size();
    priority_queue<pair<int, int>, vector<pair<int, int>>, comp> pq;
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        while (count < m && mat[i][count] == 1)
            count++;
        pq.push({count, i});
        // if(pq.size() > k)
        //     pq.pop();
    }
    vector<int> ans;
    while (k--)
    {
        cout << pq.top().f << " " << pq.top().s << endl;
        ans.push_back(pq.top().s);
        pq.pop();
    }
    cout << endl;
    return ans;
}

// DAY 16 (Letter Case Permutation)================================================================

void dfs(int i, int n, string &s, vector<string> &ans)
{
    if (i == n)
    {
        ans.push_back(s);
        return;
    }
    if ((s[i] - 'a' >= 0 && s[i] - 'a' < 26) || (s[i] - 'A' >= 0 && s[i] - 'A' < 26))
    {
        s[i] = tolower(s[i]);
        dfs(i + 1, n, s, ans);
        s[i] = toupper(s[i]);
        dfs(i + 1, n, s, ans);
    }
    else
        dfs(i + 1, n, s, ans);
}

vector<string> letterCasePermutation(string S)
{
    vector<string> ans;
    dfs(0, S.size(), S, ans);
    return ans;
}

// DAY 17 (Container with Most water)==================================================================

// APPROACH 1 (finding exponentially) --> O(2^(n/2))
// TLE
void findmaxarea(int st, int end, vector<int> &arr, int &maxarea)
{
    if (st == end)
        return;

    maxarea = max(maxarea, min(arr[end], arr[st]) * (end - st));
    findmaxarea(st + 1, end, arr, maxarea);
    findmaxarea(st, end - 1, arr, maxarea);
}

int maxArea(vector<int> &height)
{
    int maxarea = 0;
    findmaxarea(0, height.size() - 1, height, maxarea);
    return maxarea;
}

// APPROACH 2 --> O(n^2)
// TLE

void findmaxarea(int n, vector<int> &arr, int &maxarea)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            maxarea = max(maxarea, min(arr[i], arr[j]) * (j - i));
}

int maxArea(vector<int> &height)
{
    int maxarea = 0;
    findmaxarea(height.size(), height, maxarea);
    return maxarea;
}

// APPROACH 3 (Greedy) --> O(n)
// AC

void findmaxarea(int st, int end, vector<int> &arr, int &maxarea)
{
    if (st == end)
        return;

    maxarea = max(maxarea, min(arr[end], arr[st]) * (end - st));
    if (arr[st] < arr[end])
        findmaxarea(st + 1, end, arr, maxarea);
    else
        findmaxarea(st, end - 1, arr, maxarea);
}

int maxArea(vector<int> &height)
{
    int maxarea = 0;
    findmaxarea(0, height.size() - 1, height, maxarea);
    return maxarea;
}

// DAY 18 (Arithmetic Slices)====================================================================

int numberOfArithmeticSlices(vector<int> &A)
{
    int pi = 0, count = 0;
    for (int i = 0; i + 2 < A.size(); i++)
    {
        if (A[i + 1] - A[i] == A[i + 2] - A[i + 1])
            count += i - pi + 1;
        else
            pi = i + 1;
    }
    return count;
}

// DAY 19 (Minimum Remove to Make Valid Parenthesis)====================================================================

// APPROACH 1 (Using Deque)

#define f first
#define s second

string minRemoveToMakeValid(string s)
{
    int n = s.size();
    deque<pair<char, int>> st;
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if (isalpha(c))
            continue;
        if (st.empty() || st.front().f == ')' || c == '(')
            st.push_front({c, i});
        else if (c == ')')
            st.pop_front();
    }
    // cout<<st.size()<<endl;
    // cout<<st.front()<<endl;
    string ans = "";
    for (int i = 0; i < n; i++)
    {
        char c = s[i];
        if (st.empty())
            ans += c;
        else if (i == st.back().s)
            st.pop_back();
        else
            ans += c;
    }
    return ans;
}

// APPROACH 2 (Keeping Count of Opening and Closing Brackets -- Space OPTIMIZED)

string minRemoveToMakeValid(string s)
{
    int n = s.size();
    int open = 0;
    int close = count(s.begin(), s.end(), ')');
    // cout<<close<<endl;

    string ans = "";
    for (char c : s)
    {
        if (c == '(')
        {
            if (open == close)
                continue;
            open++;
        }
        else if (c == ')')
        {
            close--;
            if (open == 0)
                continue;
            open--;
        }
        ans += c;
    }
    return ans;
}

// DAY 20 (Roman To Intger)==================================================================

int romanToInt(string s)
{
    unordered_map<char, int> m;
    m['I'] = 1, m['V'] = 5, m['X'] = 10, m['L'] = 50, m['C'] = 100, m['D'] = 500, m['M'] = 1000;

    char p = NULL;
    int ans = 0;
    for (int i = s.size() - 1; i >= 0; i--)
    {
        int num = toint(s[i]);
        if (p == NULL || num >= m[p])
            ans += m[s[i]];
        else
            ans -= m[s[i]];
        p = s[i];
    }
    return ans;
}

// DAY 22 (Broken Calculator)===========================================================================

// APPROACH 1 (BFS) --> <O(2^(Y-X)) ~= O(n^2)
#define f first
#define s second
int brokenCalc(int X, int Y)
{
    if (X >= Y)
        return X - Y;
    queue<pair<int, int>> que;
    que.push({X, 0});
    while (!que.empty())
    {
        auto p = que.front();
        que.pop();
        // cout<<p.f<<" "<<p.s<<endl;
        if (p.f == Y)
            return p.s;
        if (p.f - 1 > 1)
            que.push({p.f - 1, p.s + 1});
        if (p.f < Y)
            que.push({2 * p.f, p.s + 1});
    }
    cout << endl;
    return 0;
}

// APPROACH 2 (Moving Backwards) --> O(log(Y-X))

int brokenCalc(int X, int Y)
{
    int count = 0;
    while (X < Y)
    {
        if (Y & 1)
            Y++;
        else
            Y /= 2;
        count++;
    }
    return X - Y + count;
}

// DAY 22 (Longest Word in Dictionary through Deleting)================================================================

// METHOD 1 (Naive Approach) --> O(n^2)

int countsame(int i, int j, string &s, string &a)
{
    if (j == a.size())
        return a.size();
    if (i == s.size())
        return 0;
    if (s[i] == a[j])
        return countsame(i + 1, j + 1, s, a);
    else
        return countsame(i + 1, j, s, a);
}

string findLongestWord(string s, vector<string> &d)
{
    string ans = "";

    int maxsimi = 0;
    for (string a : d)
    {
        int simi = countsame(0, 0, s, a);
        if (simi >= maxsimi)
        {
            if (simi == maxsimi && a > ans)
                continue;
            maxsimi = simi;
            ans = a;
        }
    }
    return ans;
}

// METHOD 2 (By sorting the strings first) --> O(n*logn + n^2)

int countsame(int i, int j, string &s, string &a)
{
    if (j == a.size())
        return a.size();
    if (i == s.size())
        return 0;
    if (s[i] == a[j])
        return countsame(i + 1, j + 1, s, a);
    else
        return countsame(i + 1, j, s, a);
}

string findLongestWord(string s, vector<string> &d)
{
    auto comp = [](string &a, string &b) {
        return (a.size() == b.size()) ? (a < b) : (a.size() > b.size());
    };
    int maxsimi = 0;
    sort(d.begin(), d.end(), comp);

    for (string a : d)
    {
        int simi = countsame(0, 0, s, a);
        if (simi > 0)
            return a;
    }
    return "";
}

// DAY 23 (Search a 2D Matrix)===========================================================

// APPROACH 1 (Naive) --> O(n*m)
// TLE
bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size();
    cout << n << " " << m << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] == target)
                return true;
    return false;
}

// APPROACH 2 (Binary Search in every row) --> O(n*logm)
// AC

pair<bool, int> binarysearch(int i, int st, int end, vector<vector<int>> &matrix, int target)
{
    while (st <= end)
    {
        int mid = (st + end) >> 1;
        if (matrix[i][mid] == target)
            return {true, end};
        if (matrix[i][mid] > target)
            end = mid - 1;
        else
            st = mid + 1;
    }
    return {false, end};
}

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size();
    int j = m - 1;
    for (int i = 0; i < n; i++)
    {
        pair<bool, int> p = binarysearch(i, 0, j, matrix, target);
        if (p.first)
            return true;
        j = p.second;
        if (j == -1)
            return false;
    }
    return false;
}

// APPROACH 3 (Using the giver Sorting property fully by considering height and width in the matrix) --> O(max(n,m))
// AC

bool searchMatrix(vector<vector<int>> &matrix, int target)
{
    int n = matrix.size(), m = matrix[0].size();
    int h = 0, w = m;
    while (h < n && w > 0)
    {
        if (matrix[h][w - 1] == target)
            return true;
        if (matrix[h][w - 1] < target)
            h++;
        else
            w--;
    }
    return false;
}

// DAY 24 (Score of Parenthesis)============================================================

// APPROACH 1 (Using Stack)

int scoreOfParentheses(string s)
{
    int ans = 0;
    stack<int> st;
    st.push(0);
    for (char c : s)
    {
        if (c == '(')
            st.push(0);
        else
        {
            int top = st.top();
            st.pop();
            int val = 0;
            if (top > 0)
                val = top * 2;
            else
                val = 1;
            st.top() += val;
        }
    }
    return st.top();
}

// APPROACH 2 (Mathematically)===============================================

int scoreOfParentheses(string s)
{
    int ans = 0, p = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(')
            p++;
        else
        {
            p--;
            if (s[i - 1] == '(')
                ans += (1 << p);
        }
    }
    return ans;
}

// DAY 25 (Shortest Unsorted Continuous Subarray)=================================================================

// APPROACH 1 (Sort and check for different values at same position) --> O(n*logn)

int findUnsortedSubarray(vector<int> &nums)
{
    int n = nums.size();

    vector<int> a(nums);
    sort(a.begin(), a.end());

    int st = 0, end = n - 1;
    for (; st < n; st++)
        if (nums[st] != a[st])
            break;
    if (st == n)
        return 0;
    for (; end >= 0; end--)
        if (nums[end] != a[end])
            break;
    return end - st + 1;
}

// APPROACH 2 (Visualize with a graph of values and set the start and end pointers)

int setst(vector<int> &nums, int end, int st)
{
    while (st >= 0 && nums[st] > nums[end])
        st--;
    return ++st;
}

int findUnsortedSubarray(vector<int> &nums)
{
    int st = -1, end = -1;
    int maxi = INT_MIN;
    for (int i = 0; i < nums.size() - 1; i++)
    {
        if (nums[i + 1] < nums[i] || nums[i + 1] < maxi)
        {
            if (st == -1)
                st = i;
            end = i + 1;
            st = min(st, setst(nums, end, st));
        }
        maxi = max(maxi, nums[i]);
    }
    // cout<<st<<" "<<end<<endl;
    return (st == -1) ? 0 : (end - st + 1);
}

// DAY 26 (Validate Stack Sequences)==============================================================

bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
{
    int n = pushed.size();
    stack<int> st;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        st.push(pushed[i]);
        while (!st.empty() && j < n && st.top() == popped[j])
        {
            st.pop();
            j++;
        }
    }
    return st.empty();
}

// DAY 27 (Divide 2 Integers)======================================================

int divide(int dividend, int divisor)
{
    if (divisor == 0)
        return INT_MAX;
    if (dividend == 0)
        return 0;
    if (fabs(divisor) > fabs(dividend))
        return 0;
    // cout<<abs(dividend)<<endl;
    // cout<<fabs(dividend)<<endl;
    long ans = (double)exp(log(fabs(dividend)) - log(fabs(divisor)));
    if ((dividend > 0) ^ (divisor > 0))
        ans = -ans;
    // cout<<ans<<endl;
    return ans > INT_MAX ? INT_MAX : ans;
}

// DAY 28 (Maximum Frequency Stack)================================================================

// APPROACH 1 (Using priority queue and frequency map)
class FreqStack
{
#define f first
#define s second
private:
    struct comp
    {
        bool operator()(pair<int, pair<int, int>> &a, pair<int, pair<int, int>> &b)
        {
            return (a.s.f == b.s.f) ? (a.s.s < b.s.s) : (a.s.f < b.s.f);
        }
    };

    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, comp> pq;
    unordered_map<int, int> cnt;
    int i;

public:
    FreqStack()
    {
        i = 0;
    }

    void push(int x)
    {
        pq.push({x, {++cnt[x], i++}});
    }

    int pop()
    {
        int tp = pq.top().f;
        pq.pop();
        --cnt[tp];
        return tp;
    }
};

// APPROACH 2 (Using stack map and frequency map)
class FreqStack
{
private:
    unordered_map<int, int> freqmap;
    unordered_map<int, vector<int>> stmap;
    int maxfreq;

public:
    FreqStack()
    {
        this->maxfreq = 0;
    }

    void push(int x)
    {
        int freq = ++freqmap[x];
        maxfreq = max(maxfreq, freq);
        stmap[freq].push_back(x);
    }

    int pop()
    {
        vector<int> &st = stmap[maxfreq];
        int x = st.back();
        st.pop_back();
        --freqmap[x];
        if (st.empty())
            maxfreq--;
        return x;
    }
};