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
    if(s.size() != t.size())
        return false;
    vector<int> m(26,0);
    for(char c : s) m[c-'a']++;
    for(char c : t) m[c-'a']--;
    
    for(int x : m)
        if(x != 0)
            return false;
    
    return true;
}