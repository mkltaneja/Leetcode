// DAY 1 (62. Unique Paths)========================================================================================

int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == 0 && j == 0)
                continue;
            dp[i][j] = (i ? dp[i - 1][j] : 0) + (j ? dp[i][j - 1] : 0);
        }
    }
    return dp[m - 1][n - 1];
}

// DAY 2 (378. Kth Smallest Element in a Sorted Matrix)============================================================

int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    int lo = matrix[0][0], hi = matrix[n - 1][m - 1];

    while (lo < hi)
    {
        int x = lo + ((hi - lo) >> 1);
        int tot = 0;
        for (int i = 0; i < n; i++)
        {
            int st = 0, end = m;
            while (st < end)
            {
                int mid = st + ((end - st) >> 1);
                if (matrix[i][mid] <= x)
                    st = mid + 1;
                else
                    end = mid;
            }
            tot += st;
        }
        if (tot < k)
            lo = x + 1;
        else
            hi = x;
    }

    return lo;
}

// DAY 3 (729. My Calendar I)=======================================================================================

// APPROACH 1 (By finding just lower element)

class MyCalendar
{
public:
    set<pair<int, int>> st;
    MyCalendar()
    {
    }

    auto just_lower(int x)
    {
        int lo = 0, hi = st.size() - 1, ans = -1;
        while (lo <= hi)
        {
            int mid = lo + ((hi - lo) >> 1);
            auto itr = st.begin();
            advance(itr, mid);
            if (itr->first <= x)
                lo = mid + 1, ans = mid;
            else
                hi = mid - 1;
        }

        if (ans == -1)
            return st.end();
        auto ansitr = st.begin();
        advance(ansitr, ans);
        return ansitr;
    }

    bool book(int start, int end)
    {
        if (st.empty())
        {
            st.insert({start, end});
            return true;
        }
        auto x = just_lower(start);
        if (x == st.end()) // no just_lower element found, so compare with just above ony
        {
            if (st.begin()->first < end)
                return false;
        }
        else
        {
            if (x->second > start || (++x != st.end() && x->first < end))
                return false;
        }

        st.insert({start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

//  APPROACH 2 (By Finding lower_bound)

class MyCalendar
{
public:
#define f first
#define s second
    set<pair<int, int>> events;
    MyCalendar()
    {
    }

    bool book(int start, int end)
    {
        auto itr = events.lower_bound({start, end});
        if (itr != events.end() && (*itr).f < end)
            return false;
        if (itr != events.begin() && (*--itr).s > start)
            return false;

        events.insert({start, end});
        return true;
    }
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */

// DAY 4 (858. Mirror Reflection)==============================================================================

// APPROACH 1 (Naive)

int mirrorReflection(int p, int q)
{
    int mod = p % q;
    int refs = (p + (q - 1)) / q;
    int rooms = 1;
    while (mod)
    {
        refs += ((p - (q - mod)) + (q - 1)) / q;
        rooms++;
        mod = (p - (q - mod)) % q;
    }
    return (refs & 1 ^ 1) ? 2 : (rooms & 1);
}

// APPROACH 2 (By Finding LCM)

int mirrorReflection(int p, int q)
{
    int lcm = p * q / __gcd(p, q);
    int m = lcm / p;
    int n = lcm / q;

    return n & 1 ^ 1 ? 2 : m & 1;
}

// APPROACH 3 (Concise)

int mirrorReflection(int p, int q)
{
    while ((p & 1 ^ 1) && (q & 1 ^ 1))
        p >>= 1, q >>= 1;

    return p & 1 ^ 1 ? 2 : q & 1;
}

// DAY 5 (377. Combination Sum IV)=================================================================================

int combinationSum4(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    vector<unsigned long long> dp(target + 1, 0);
    dp[0] = 1;

    for (int t = 1; t <= target; t++)
        for (int i = 0; i < nums.size() && nums[i] <= t; i++)
            dp[t] += dp[t - nums[i]];

    return dp[target];
}

// DAY 6 (1220. Count Vowels Permutation)===================================================================================

// APPROACH 1 (Memoized) --> time = O(n*5), space = O(n*5)

int m = 1e9 + 7;

unordered_map<char, int> mp;

int dfs(int n, char u, unordered_map<char, vector<char>> &gp, vector<vector<int>> &dp)
{
    if (n == 1)
        return 1;
    if (dp[mp[u]][n] != -1)
        return dp[mp[u]][n];

    int ans = 0;
    for (char v : gp[u])
        ans = ans % m + dfs(n - 1, v, gp, dp) % m % m;

    return dp[mp[u]][n] = ans % m;
}

int countVowelPermutation(int n)
{
    mp['a'] = 0;
    mp['e'] = 1;
    mp['i'] = 2;
    mp['o'] = 3;
    mp['u'] = 4;

    unordered_map<char, vector<char>> gp;
    gp['a'] = {'e'};
    gp['e'] = {'a', 'i'};
    gp['i'] = {'a', 'e', 'o', 'u'};
    gp['o'] = {'i', 'u'};
    gp['u'] = {'a'};

    int ans = 0;
    vector<vector<int>> dp(5, vector<int>(n + 1, -1));
    for (auto p : gp)
        ans = ans % m + dfs(n, p.first, gp, dp) % m % m;

    return ans % m;
}

// APPROACH 2 (No Space DP) --> time = O(n), space = O(1)

int m = 1e9 + 7;
int countVowelPermutation(int n)
{
    long pa, pe, pi, po, pu;
    pa = pe = pi = po = pu = 1;

    while (--n)
    {
        long a = pe % m;
        long e = (pa + pi) % m;
        long i = (pa + pe + po + pu) % m;
        long o = (pi + pu) % m;
        long u = pa % m;

        pa = a, pe = e, pi = i, po = o, pu = u;
    }

    return (pa + pe + pi + po + pu) % m;
}

// DAY 8 (300. Longest Increasing Subsequence)===========================================================================

int lengthOfLIS(vector<int>& nums) 
{
    vector<int> dp;
    for(int i = 0; i < nums.size(); i++)
    {
        int lo = 0, hi = dp.size();
        while(lo < hi)
        {
            int mid = lo + ((hi - lo)>>1);
            if(dp[mid] < nums[i]) lo = mid + 1;
            else hi = mid;
        }
        if(lo == dp.size()) dp.push_back(nums[i]);
        else dp[lo] = nums[i];
    }

    return dp.size();
}

// DAY 9 (823. Binary Trees With Factors)========================================================================================

// APPROACH 1 (Using Graphs) -> time - O(n*n), space - O(n)

unordered_map<int,int> dp;
int m = 1e9 + 7;

int dfs(int u, unordered_map<long,vector<pair<int,int>>> &gp)
{
    if(dp.count(u)) return dp[u];
    long ans = 0;

    for(pair<int,int> v : gp[u])
    {
        long lans = dfs(v.first, gp) % m;
        long rans = dfs(v.second, gp) % m;
        long curr = (lans % m * rans % m) % m;
        curr = curr * (v.first == v.second? 1 : 2) % m;
        ans = ans % m + curr % m % m;
    }

    return dp[u] = (ans + 1) % m;
}

int numFactoredBinaryTrees(vector<int>& arr) 
{
    int n = arr.size();
    unordered_set<int> st;
    for(int x : arr) st.insert(x);

    unordered_map<long,vector<pair<int,int>>> gp;
    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            if(st.count((long)arr[i] * arr[j]))
                gp[(long)arr[i] * arr[j]].push_back({arr[i], arr[j]});

    int ans = 0;
    for(int x : arr)
        ans = ans % m + dfs(x, gp) % m % m;
    return ans % m;
}

// APPROACH 2 (Mathematically) --> time - O((n * logn) + (n * sqrt(max(arr[i]))), space - O(n)

int m = 1e9 + 7;
int numFactoredBinaryTrees(vector<int>& arr) 
{
    int n = arr.size();
    sort(arr.begin(), arr.end());

    unordered_map<int,long> size;
    int ans = 0;

    for(int x : arr)
    {
        int mxf = sqrt(x);
        int ways = 1;
        for(int i = 0; arr[i] <= mxf; i++)
            if(x % arr[i] == 0)
                ways = ways % m + ((size[arr[i]] % m * size[x/arr[i]] % m) % m) % m * (arr[i] == x/arr[i]? 1 : 2) % m;
        size[x] = ways;
        ans = ans % m + ways % m % m;
    }

    return ans % m;
}

// DAY 10 (108. Convert Sorted Array to Binary Search Tree)===================================================================================

TreeNode* construct(int lo, int hi, vector<int> &nums)
{
    if(lo > hi) return nullptr;

    int mid = lo + ((hi - lo) >> 1);
    TreeNode* root = new TreeNode(nums[mid]);

    root->left = construct(lo, mid-1, nums);
    root->right = construct(mid+1, hi, nums);

    return root;
}

TreeNode* sortedArrayToBST(vector<int>& nums) 
{
    return construct(0, nums.size()-1, nums);
}

// DAY 11 (98. Validate Binary Search Tree)====================================================================================================================

// APPROACH 1 (Checking in Inorder traversal)

bool inorder(long &prev, TreeNode* node)
{
    if(!node) return true;

    bool lans = inorder(prev, node->left);

    if(node->val <= prev) return false;
    prev = node->val;

    bool rans = inorder(prev, node->right);

    return lans && rans;
}

bool isValidBST(TreeNode* root) 
{
    long prev = LONG_MIN;

    return inorder(prev, root);
}

// APPROACH 2 (Checking in Preorder traversal)

bool preorder(long mn, long mx, TreeNode* node)
{
    if(!node) return true;

    if(node->val <= mn || node->val >= mx) return false;

    bool lans = preorder(mn, node->val, node->left);
    bool rans = preorder(node->val, mx, node->right);

    return lans && rans;
}

bool isValidBST(TreeNode* root) 
{
    return preorder(LONG_MIN, LONG_MAX, root);
}

// DAY 12 (235. Lowest Common Ancestor of a Binary Search Tree)=================================================================================

// APPROACH 1 (Recursively)

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    if(!root) return root;

    if(root->val < p->val && root->val < q->val)
        return lowestCommonAncestor(root->right, p, q);
    if(root->val > p->val && root->val > q->val)
        return lowestCommonAncestor(root->left, p, q);

    return root;
}

// APPROACH 2 (Iteratively)

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
{
    int mn = min(p->val, q->val);
    int mx = max(p->val, q->val);

    while(root)
    {
        if(root->val < mn) root = root->right;
        else if(root->val > mx) root = root->left;
        else return root;
    }

    return nullptr;
}

// DAY 14 (126. Word Ladder II)========================================================================================

// APPROACH 1 (By storing the path in queue) [TLE] -> time = O(26 * m * n * n) [m = size of each word, n = size of wordList]

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) 
{
    unordered_map<string,int> time;
    for(int i = 0; i < wordList.size(); i++)
        time[wordList[i]] = INT_MAX;
    time[beginWord] = 0;

    if(!time.count(endWord)) return {};
    vector<vector<string>> ans;

    queue<pair<string, vector<string>>> que;
    que.push({beginWord, {beginWord}});

    while(!que.empty())
    {
        string tp = que.front().first;
        vector<string> currs = que.front().second;
        que.pop();
        if(tp == endWord) 
        {
            ans.push_back(currs);
            continue;
        }

        for(int i = 0; i < tp.size(); i++)
        {
            string next = tp;
            for(char x = 'a'; x <= 'z'; x++)
            {
                if(x == tp[i]) continue;
                next[i] = x;
                if(!time.count(next) || time[next] < currs.size()) continue;

                time[next] = currs.size();
                currs.push_back(next);
                que.push({next, currs});
                currs.pop_back();
            }
        }
    }

    return ans;
}
