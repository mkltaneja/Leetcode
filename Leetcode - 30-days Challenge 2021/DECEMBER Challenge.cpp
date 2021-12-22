// DAY 1 (198. House Robber)======================================================================

int rob(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n);
    dp[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
        dp[i] = max(nums[i] + ((i + 2 < n) ? dp[i + 2] : 0), dp[i + 1]);

    return dp[0];
}

// DAY 3 (152. Maximum Product Subarray)================================================================================

int maxProduct(vector<int> &nums)
{
    int ans = nums[0];
    int maxp = nums[0], minp = nums[0];
    for (int i = 1; i < nums.size(); i++)
    {
        int x = nums[i];
        if (x < 0)
            swap(minp, maxp);
        maxp = max(maxp * x, x);
        minp = min(minp * x, x);

        ans = max({ans, maxp, minp});
    }

    return ans;
}

// DAY 4 (1032. Stream of Characters)=======================================================================
class StreamChecker
{
public:
    class trie
    {
    public:
        vector<trie *> v;
        bool wordEnd;
        trie()
        {
            this->v.assign(26, nullptr);
            this->wordEnd = false;
        }

        void insert(string &s)
        {
            trie *curr = this;
            for (char c : s)
            {
                if (!curr->v[c - 'a'])
                    curr->v[c - 'a'] = new trie();
                curr = curr->v[c - 'a'];
            }
            curr->wordEnd = true;
        }
    };
    trie *root = new trie();

    StreamChecker(vector<string> &words)
    {
        for (string word : words)
        {
            reverse(word.begin(), word.end());
            root->insert(word);
        }
    }
    string s = "";
    bool query(char letter)
    {
        s += letter;
        trie *curr = root;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (!curr->v[s[i] - 'a'])
                return false;
            if (curr->v[s[i] - 'a']->wordEnd)
                return true;
            curr = curr->v[s[i] - 'a'];
        }
        return curr->wordEnd;
        return true;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */

//  DAY 5 (337. House Robber III)=========================================================================================

// APPROACH 1 (Without DP) --> O(4^h) [h = height of tree]      OR O(n^2)  [n = number of nodes]
// TLE

int rob(TreeNode *root)
{
    if (!root)
        return 0;

    int exc = rob(root->left) + rob(root->right);
    int inc = (root->left ? rob(root->left->left) + rob(root->left->right) : 0) +
              (root->right ? rob(root->right->left) + rob(root->right->right) : 0) + root->val;

    return max(inc, exc);
}

// APPROACH 2 (Using map as DP) --> >O(n)
// AC

unordered_map<TreeNode *, int> dp;
int rob(TreeNode *root)
{
    if (!root)
        return 0;

    if (dp.count(root))
        return dp[root];

    int exc = rob(root->left) + rob(root->right);
    int inc = (root->left ? rob(root->left->left) + rob(root->left->right) : 0) +
              (root->right ? rob(root->right->left) + rob(root->right->right) : 0) + root->val;

    return dp[root] = max(inc, exc);
}

// APPROACH 3 (Without DP -> inc, exc) --> O(n)
// AC

#define f first
#define s second
pair<int, int> dfs(TreeNode *node)
{
    if (!node)
        return {0, 0};

    auto lmax = dfs(node->left);
    auto rmax = dfs(node->right);

    int inc = lmax.s + rmax.s + node->val;
    int exc = max(lmax.f, lmax.s) + max(rmax.f, rmax.s);

    return {inc, exc};
}

int rob(TreeNode *root)
{
    auto ans = dfs(root);
    return max(ans.f, ans.s);
}

// DAY 6 (1217. Minimum Cost to Move Chips to The Same Position)==========================================================================

int minCostToMoveChips(vector<int> &position)
{
    int osum = 0, esum = 0;
    for (int i = 0; i < position.size(); i++)
    {
        osum += (position[i] & 1);
        esum += (position[i] & 1 ^ 1);
    }

    return min(osum, esum);
}

// DAY 7 (1290. Convert Binary Number in a Linked List to Integer)=======================================================================

int getDecimalValue(ListNode *head)
{
    int ans = 0;
    ListNode *curr = head;
    while (curr)
    {
        ans = ans * 2 + curr->val;
        curr = curr->next;
    }

    return ans;
}

// DAY 8 (563. Binary Tree Tilt)==============================================================================================

#define f first
#define s second

int sum = 0;
int dfs(TreeNode *node)
{
    if (!node)
        return 0;

    int lans = dfs(node->left);
    int rans = dfs(node->right);

    sum += abs(lans - rans);

    return lans + rans + node->val;
}

int findTilt(TreeNode *root)
{
    dfs(root);
    return sum;
}

// DAY 9 (1306. Jump Game III)==========================================================================================

// APPROACH 1 (BFS) -> O(n)

bool canReach(vector<int> &arr, int start)
{
    queue<int> que;
    que.push(start);
    if (arr[start] == 0)
        return true;

    while (!que.empty())
    {
        int i = que.front();
        que.pop();

        int j = i + arr[i];
        int k = i - arr[i];
        arr[i] = -1;

        if (j < arr.size() && arr[j] != -1)
        {
            if (arr[j] == 0)
                return true;
            que.push(j);
        }
        if (k >= 0 && arr[k] != -1)
        {
            if (arr[k] == 0)
                return true;
            que.push(k);
        }
    }

    return false;
}

// APPROACH 2 (DFS) --> O(n)

bool dfs(int i, int n, vector<int> &arr, vector<bool> &vis)
{
    if (i < 0 || i >= n || vis[i])
        return false;

    if (arr[i] == 0)
        return true;

    vis[i] = true;

    return dfs(i + arr[i], n, arr, vis) || dfs(i - arr[i], n, arr, vis);
}

bool canReach(vector<int> &arr, int start)
{
    int n = arr.size();
    vector<bool> vis(n, false);
    return dfs(start, n, arr, vis);
}

// DAY 11 (878. Nth Magical Number)===============================================================================================

int mod = (int)1e9 + 7;
long gcd(int a, int b)
{
    return (a == 0) ? b : gcd(b % a, a);
}

int nthMagicalNumber(int n, int a, int b)
{
    int lcm = a / gcd(a, b) * b;
    int x = (lcm / a) + (lcm / b) - 1;
    int q = n / x;
    int r = n % x;

    long ans = ((long)(q % mod) * (lcm % mod)) % mod;

    if (r == 0)
        return (int)ans % mod;

    int aa = a, bb = b;
    for (int i = 0; i < r - 1; i++)
    {
        if (aa <= bb)
            aa += a;
        else
            bb += b;
    }
    ans = (ans + min(aa, bb)) % mod;

    return (int)ans % mod;
}

// DAY 12 (416. Partition Equal Subset Sum)====================================================================

// APPROACH 1 (Memoization with 2D DP) --> O(n*(sum/2))

bool subseq(int i, int n, int csum, int tsum, vector<int> &arr, vector<vector<int>> &dp)
{
    if (i == n)
        return false;
    if (2 * csum == tsum)
        return dp[i][csum] = true;
    if (2 * csum > tsum)
        return false;
    if (dp[i][csum] != -1)
        return dp[i][csum];

    return dp[i][csum] = subseq(i + 1, n, csum + arr[i], tsum, arr, dp) ||
                         subseq(i + 1, n, csum, tsum, arr, dp);
}

bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int tsum = 0;
    for (int x : nums)
        tsum += x;
    if (tsum & 1)
        return false;

    vector<vector<int>> dp(n, vector<int>(tsum + 1, -1));
    return subseq(0, n, 0, tsum, nums, dp);
}

// APPROACH 2 (Tabulation with 2D DP) --> O(n*(sum/2))

bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int tsum = 0;
    for (int x : nums)
        tsum += x;
    if (tsum & 1)
        return false;
    tsum >>= 1;

    vector<vector<bool>> dp(n + 1, vector<bool>(tsum + 1, false));
    dp[0][0] = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= tsum; j++)
        {
            if (j < nums[i - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
        }
    }

    return dp[n][tsum];
}

// APPROACH 3 (Tabulation with 1D DP -> [space optimized, as we ony needed the previous index for every index in dp]) --> O(n*(sum/2))

bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int tsum = 0;
    for (int x : nums)
        tsum += x;
    if (tsum & 1)
        return false;
    tsum >>= 1;

    vector<int> dp(tsum + 1, 0);
    dp[0] = 1;
    for (int x : nums)
        for (int i = tsum; i >= x; i--)
            dp[i] |= dp[i - x];

    return dp[tsum];
}

// APPROACH 4 (Using bitset) --> O(n) [MOST OPTIMIZED]

bool canPartition(vector<int> &nums)
{
    int n = nums.size();

    int tsum = 0;
    for (int x : nums)
        tsum += x;
    if (tsum & 1)
        return false;
    tsum >>= 1;

    bitset<10001> dp = 1;

    for (int x : nums)
    {
        dp |= (dp << x);
        if (dp.test(tsum))
            return true;
    }

    return false;
}

// DAY 13 (1446. Consecutive Characters)=========================================================================

int maxPower(string s)
{
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n;)
    {
        int j = i;
        while (j < n && s[j] == s[i])
            j++;
        ans = max(ans, j - i);
        i = j;
    }

    return ans;
}

// DAY 14 (938. Range Sum of BST)==================================================================================

int rangeSumBST(TreeNode *root, int low, int high)
{
    if (!root)
        return 0;

    int lsum = 0, rsum = 0;
    if (root->val > high)
        return rangeSumBST(root->left, low, high);
    if (root->val < low)
        return rangeSumBST(root->right, low, high);
    return rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high) + root->val;
}

// DAY 15 (147. Insertion Sort List)============================================================================

ListNode *insertionSortList(ListNode *head)
{
    ListNode *curr = head->next, *sortend = head;
    while (curr)
    {
        ListNode *itr = head, *prev = nullptr;
        ListNode *next = curr->next;
        while (itr->val < curr->val)
        {
            prev = itr;
            itr = itr->next;
        }
        if (prev == nullptr)
        {
            curr->next = head;
            head = curr;
        }
        else
        {
            prev->next = curr;
            if (itr != curr)
                curr->next = itr;
        }
        if (itr == curr)
            sortend = sortend->next;
        else
            sortend->next = next;
        curr = next;
    }
    return head;
}

// DAY 16 (310. Minimum Height Trees)================================================================

int findh(int u, int p, vector<vector<int>> &gp)
{
    int h = 0;
    for (int v : gp[u])
        if (v != p)
            h = max(h, findh(v, u, gp));
    return h + 1;
}

vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
{
    vector<vector<int>> gp(n);
    for (vector<int> e : edges)
    {
        gp[e[0]].push_back(e[1]);
        gp[e[1]].push_back(e[0]);
    }

    vector<int> ht(n);
    int minh = n + 1;
    for (int i = 0; i < n; i++)
    {
        ht[i] = findh(i, -1, gp);
        minh = min(minh, ht[i]);
    }

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (ht[i] == minh)
            ans.push_back(i);
    return ans;
}

// DAY 17 (221. Maximal Square)============================================================================

int maximalSquare(vector<vector<char>> &matrix)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<int> pdp(m + 1, 0), dp(m + 1, 0);

    int maxsq = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (matrix[i - 1][j - 1] - '0')
            {
                dp[j] = min({pdp[j], dp[j - 1], pdp[j - 1]}) + 1;
                maxsq = max(maxsq, dp[j]);
            }
            else
                dp[j] = 0;
        }
        pdp = dp;
    }

    return maxsq * maxsq;
}

// DAY 19 (394. Decode String)============================================================================================

bool isnum(char c)
{
    return c >= '0' && c <= '9';
}
bool ischar(char c)
{
    return c >= 'a' && c <= 'z';
}

string decodeString(string s)
{
    vector<string> st;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '[')
            continue;

        string x = "";
        while (i < s.size() && isnum(s[i]))
            x += s[i++];
        if (!x.empty())
            st.push_back(x);

        else if (s[i] >= 'a' && s[i] <= 'z')
        {
            string tp = "";
            if (!st.empty() && (!isnum(st.back()[0])))
            {
                tp = st.back();
                st.pop_back();
            }
            tp += s[i];
            st.push_back(tp);
        }
        else if (s[i] == ']')
        {
            string tp = st.back();
            st.pop_back();
            int x = stoi(st.back());
            st.pop_back();

            string tmp = "";
            while (x--)
                tmp += tp;
            while (!st.empty() && !isnum(st.back()[0]))
            {
                tmp = st.back() + tmp;
                st.pop_back();
            }
            st.push_back(tmp);
        }
    }
    string ans = "";
    for (int i = 0; i < st.size(); i++)
        ans += st[i];
    return ans;
}

// DAY 20 (1200. Minimum Absolute Difference)==================================================================

// APPROACH 1 (Simple sort) -> O(n*logn)

vector<vector<int>> minimumAbsDifference(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
    int mindiff = INT_MAX;
    for (int i = 1; i < arr.size(); i++)
        mindiff = min(mindiff, arr[i] - arr[i - 1]);

    vector<vector<int>> ans;
    for (int i = 1; i < arr.size(); i++)
        if (arr[i] - arr[i - 1] == mindiff)
            ans.push_back({arr[i - 1], arr[i]});

    return ans;
}

// APPROACH 2 (Counting Sort) -> O(n + m) [n -> size of array, m -> (max - min) element in array]

vector<vector<int>> minimumAbsDifference(vector<int> &arr)
{
    int mn = INT_MAX;
    int mx = INT_MIN;
    for (int x : arr)
    {
        mx = max(mx, x);
        mn = min(mn, x);
    }
    vector<int> line(mx - mn + 1, 0);
    for (int x : arr)
        line[x - mn] = 1;

    int prev = INT_MIN;
    int mindiff = INT_MAX;
    for (int i = 0; i <= mx - mn; i++)
    {
        if (line[i])
        {
            if (prev != INT_MIN)
                mindiff = min(mindiff, (i + mn) - prev);
            prev = i + mn;
        }
    }

    vector<vector<int>> ans;
    for (int i = 0; i <= mx - mn; i++)
    {
        if (line[i])
        {
            if (prev != INT_MIN && (i + mn) - prev == mindiff)
                ans.push_back({prev, i + mn});
            prev = i + mn;
        }
    }

    return ans;
}

// DAY 21 (231. Power of Two)==============================================================================

// METHOD 1 (subtraction with n should be 0)

bool isPowerOfTwo(int n)
{
    return (n > 0 && (n - (n & -n) == 0));
}

// METHOD 2 (AND with n-1 should be 0)

bool isPowerOfTwo(int n)
{
    return (n > 0 && !(n & (n - 1)));
}

// DAY 22 (143. Reorder List)=======================================================================

// APPROACH 1 (Recursively) --> O(n) time, O(n) space [stack space]

bool dfs(ListNode *&head, ListNode *itr)
{
    if (!itr)
        return false;

    if (dfs(head, itr->next))
        return true;

    itr->next = nullptr;
    ListNode *nxt = head->next;
    if (itr == nxt || itr == head)
        return true;

    itr->next = nxt;
    head->next = itr;
    head = nxt;

    return false;
}

void reorderList(ListNode *head)
{
    dfs(head, head);
}

// APPROACH 2 (Reversing the second half of LL) --> O(n) time, O(1) space

ListNode *reverse(ListNode *head)
{
    ListNode *prev = nullptr, *forw = nullptr;
    while (head)
    {
        forw = head->next;
        head->next = prev;
        prev = head;
        head = forw;
    }
    return prev;
}

void reorderList(ListNode *head)
{
    ListNode *fast = head, *slow = head;
    while (fast && fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    ListNode *tail = reverse(slow);

    while (head && tail && head != tail)
    {
        ListNode *nxt1 = head->next;
        ListNode *nxt2 = tail->next;
        head->next = tail;
        tail->next = nxt1;
        head = nxt1;
        tail = nxt2;
    }
}