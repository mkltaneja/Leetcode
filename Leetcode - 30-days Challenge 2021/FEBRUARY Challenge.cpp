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