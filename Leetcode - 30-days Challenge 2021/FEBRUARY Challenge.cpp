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

// METHOD 1 (BFS)
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