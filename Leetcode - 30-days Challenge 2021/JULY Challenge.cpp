// DAY 1 (Gray Code)=====================================================================================

// METHOD 1 (Using binary string array then converted to decimal) --> >O(2^n * n)

vector<string> grayCode_(int n)
{
    if (n == 1)
        return {"0", "1"};

    vector<string> code = grayCode_(n - 1);
    vector<string> curr;

    for (int i = 0; i < code.size(); i++)
        curr.push_back('0' + code[i]);
    for (int i = code.size() - 1; i >= 0; i--)
        curr.push_back('1' + code[i]);

    return curr;
}

vector<int> grayCode(int n)
{
    vector<string> code = grayCode_(n);
    vector<int> ans;
    for (string s : code)
    {
        int x = 0;
        for (int i = 0; i < s.size(); i++)
            x = x * 2 + (s[i] - '0');
        ans.push_back(x);
    }
    return ans;
}

// METHOD 2 (Directly converted to decimal) --> O(2^n * n)

vector<int> grayCode(int n)
{
    if (n == 1)
        return {0, 1};
    vector<int> code = grayCode(n - 1);
    for (int i = code.size() - 1; i >= 0; i--)
        code.push_back(code[i] | (1 << (n - 1)));

    return code;
}

// DAY 2 (Find K Closest Elements)=====================================================================

// APPROACH 1 (Linear Search) --> O(k + klogk)

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    auto pos = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

    int i = pos - 1, j = pos;
    vector<int> ans(k);
    int idx = 0;
    while (i >= 0 && j < arr.size() && idx < k)
    {
        if ((abs(x - arr[i]) <= abs(x - arr[j])) || (abs(x - arr[i]) == abs(x - arr[j]) && arr[i] < arr[j]))
            ans[idx++] = arr[i--];
        else if (abs(x - arr[i]) > abs(x - arr[j]))
            ans[idx++] = arr[j++];
    }
    while (i >= 0 && idx < k)
        ans[idx++] = arr[i--];
    while (j < arr.size() && idx < k)
        ans[idx++] = arr[j++];

    sort(ans.begin(), ans.end());
    return ans;
}

// APPROACH 2 (Binary Search) --> O(logn)

vector<int> findClosestElements(vector<int> &arr, int k, int x)
{
    int l = 0, r = arr.size() - k;
    while (l < r)
    {
        int m = (l + r) >> 1;
        if (x - arr[m] > arr[m + k] - x)
            l = m + 1;
        else
            r = m;
    }
    vector<int> ans(arr.begin() + l, arr.begin() + l + k);
    return ans;
}

// DAY 3 (Max Sum of Rectangle No Larger than K)=============================================================================

// O(m*m*n*logn)

int maxSumSubmatrix(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            matrix[i][j] += matrix[i][j - 1];

    int ans = INT_MIN;
    for (int st = 0; st < m; st++)
    {
        for (int end = st; end < m; end++)
        {
            int psum = 0;
            set<int> psums = {0};
            for (int i = 0; i < n; i++)
            {
                int sum = matrix[i][end];
                if (st)
                    sum -= matrix[i][st - 1];

                psum += sum;
                auto itr = psums.lower_bound(psum - k);
                if (itr != psums.end())
                    ans = max(ans, psum - *itr);
                psums.insert(psum);
            }
        }
    }
    return ans;
}

// DAY 4 (Count Vowel Permutation)======================================================================

int mod = 1000000007;
int solution(int n, char c, unordered_map<char, vector<char>> &m, map<pair<char, int>, int> &dp)
{
    if (n == 0)
        return dp[{c, n}] = 1;
    if (dp.count({c, n}))
        return dp[{c, n}];

    int ans = 0;
    for (char x : m[c])
        ans = ((ans % mod) + (solution(n - 1, x, m, dp) % mod) % mod);

    return dp[{c, n}] = ans % mod;
}

int countVowelPermutation(int n)
{
    unordered_map<char, vector<char>> m;
    m['#'] = {'a', 'e', 'i', 'o', 'u'};
    m['a'] = {'e'};
    m['e'] = {'a', 'i'};
    m['i'] = {'a', 'e', 'o', 'u'};
    m['o'] = {'i', 'u'};
    m['u'] = {'a'};

    map<pair<char, int>, int> dp;
    return solution(n, '#', m, dp) % mod;
}

// DAY 5 (Reshape The Matrix)============================================================================

vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c)
{
    int n = mat.size(), m = mat[0].size();
    if (n * m != r * c)
        return mat;
    vector<int> data(n * m);
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            data[k++] = mat[i][j];

    vector<vector<int>> ans(r, vector<int>(c));
    k = 0;
    for (int i = 0; i < ans.size(); i++)
        for (int j = 0; j < ans[0].size(); j++)
            ans[i][j] = data[k++];

    return ans;
}

// DAY 6 (Reduce Array Size to Half)=====================================================================================

int minSetSize(vector<int> &arr)
{
    int n = arr.size();
    unordered_map<int, int> m;
    for (int x : arr)
        m[x]++;
    vector<int> freq;
    for (auto p : m)
        freq.push_back(p.second);
    sort(freq.begin(), freq.end(), greater<int>());

    int x = 0, i = 0;
    while (x < n / 2 && i < freq.size())
        x += freq[i++];

    return i;
}

// DAY 7 (Kth Smallest Element in a Sorted Matrix)=================================================================================

int kthSmallest(vector<vector<int>> &matrix, int k)
{
    int n = matrix.size(), m = matrix[0].size();
    vector<int> lin(n * m);
    int x = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            lin[x++] = matrix[i][j];
    sort(lin.begin(), lin.end());
    return lin[k - 1];
}

// DAY 8 (Maximum Length of Repeated Subarray)=========================================================================

// APPROACH 1 (Maximum common substring -- DP) -> O(n*m)

int findLength(vector<int> &nums1, vector<int> &nums2)
{
    int n = nums1.size(), m = nums2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (nums1[i] != nums2[j])
                dp[i][j] = 0;
            else
            {
                dp[i][j] = 1;
                if (i && j)
                    dp[i][j] += dp[i - 1][j - 1];
            }
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}

// DAY 9 (Longest Common Subsequence)============================================================================

// APPROACH 1 (DP) --> O(n^2)

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();
    vector<int> maxlen(n, 1);

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (nums[j] < nums[i] && maxlen[j] + 1 > maxlen[i])
                maxlen[i] = maxlen[j] + 1;
        ans = max(ans, maxlen[i]);
    }
    return ans;
}

// APPROACH 2 (Optimized DP -- Greedy - [By updating the lis array and running binary search in it to choose the numbers optimally]) --> O(n*logn)

int lengthOfLIS(vector<int> &nums)
{
    int n = nums.size();

    vector<int> lis;
    for (int i = 0; i < n; i++)
    {
        if (lis.empty() || lis.back() < nums[i])
        {
            lis.push_back(nums[i]);
            continue;
        }
        int si = 0, ei = lis.size() - 1, idx = -1;
        while (si <= ei)
        {
            int mid = (si + ei) >> 1;
            if (lis[mid] < nums[i])
                si = mid + 1;
            else
                idx = mid, ei = mid - 1;
        }
        lis[idx] = nums[i];
    }
    return lis.size();
}

// DAY 11 (Find Median From Data Stream)===============================================================

class MedianFinder
{
public:
    priority_queue<int> max;
    priority_queue<int, vector<int>, greater<int>> min;
    /** initialize your data structure here. */
    MedianFinder()
    {
    }

    void addNum(int num)
    {
        if (max.empty() || num < max.top())
            max.push(num);
        else
            min.push(num);
        if (max.size() > min.size() + 1)
        {
            min.push(max.top());
            max.pop();
        }
        else if (min.size() > max.size() + 1)
        {
            max.push(min.top());
            min.pop();
        }
    }

    double findMedian()
    {
        double ans = (max.size() == min.size()) ? ((max.top() + min.top()) / 2.0) : ((min.size() > max.size()) ? min.top() : max.top());
        return ans;
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

// DAY 12 (Isomorphic Strings)==================================================================================================

bool isIsomorphic(string s, string t)
{
    if (s.size() != t.size())
        return false;
    unordered_map<char, char> map, mapped;
    for (int i = 0; i < s.size(); i++)
    {
        if (map[s[i]] == NULL && mapped[t[i]] == NULL)
            map[s[i]] = t[i], mapped[t[i]] = s[i];
        else if (map[s[i]] && map[s[i]] != t[i] || mapped[t[i]] && mapped[t[i]] != s[i])
            return false;
    }
    return true;
}

// DAY 13 (Find Peak Element)=================================================================================================

// APPROACH 1 (Linearly) --> O(n)

int findPeakElement(vector<int> &nums)
{
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        long l = i ? nums[i - 1] : LONG_MIN;
        long r = (i != n - 1) ? nums[i + 1] : LONG_MIN;
        if (nums[i] > l && nums[i] > r)
            return i;
    }
    return -1;
}

// APPROACH 2 (Binary Search) --> O(logn)

int findPeakElement(vector<int> &nums)
{
    int si = 0, ei = nums.size() - 1;
    while (si < ei)
    {
        int mid = (si + ei) >> 1;
        if (nums[mid] > nums[mid + 1])
            ei = mid;
        else
            si = mid + 1;
    }
    return ei;
}

// DAY 14 (Custom Sort String)=================================================================================================

string customSortString(string order, string str)
{
    vector<int> map(26, 0);
    for (char c : str)
        map[c - 'a']++;
    string ans = "";
    for (char c : order)
        while (map[c - 'a']--)
            ans += c;
    for (int i = 0; i < 26; i++)
        while (map[i]-- > 0)
            ans += char(i + 'a');
    return ans;
}

// DAY 15 (Valid Triangle Number)=====================================================================================

int triangleNumber(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int si = j + 1, ei = n - 1, x = -1;
            while (si <= ei)
            {
                int mid = (si + ei) >> 1;
                if (nums[i] + nums[j] <= nums[mid])
                    ei = mid - 1;
                else
                {
                    x = mid;
                    si = mid + 1;
                }
            }
            if (x != -1)
                ans += x - j;
        }
    }
    return ans;
}

// DAY 16 (4 Sum)==========================================================================================

vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    set<vector<int>> s;
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                for (int l = k + 1; l < n; l++)
                    if (nums[i] + nums[j] + nums[k] + nums[l] == target)
                        s.insert({nums[i], nums[j], nums[k], nums[l]});
    for (auto v : s)
        ans.push_back(v);

    return ans;
}

// DAY 17 (Three Equal Parts)============================================================================================

vector<int> threeEqualParts(vector<int> &arr)
{
    int n = arr.size();
    vector<int> oi;
    for (int i = 0; i < n; i++)
        if (arr[i])
            oi.push_back(i);
    int tot = oi.size();

    if (tot == 0)
        return {0, n - 1};
    if (tot % 3)
        return {-1, -1};
    int x = oi[0], y = oi[tot / 3], z = oi[2 * (tot / 3)];

    while (z < n && arr[x] == arr[y] && arr[x] == arr[z])
        x++, y++, z++;
    if (z == n)
        return {x - 1, y};
    return {-1, -1};
}

// DAY 18 (Reserve Nodes in K Group)====================================================================

ListNode *reverseKGroup(ListNode *head, int k)
{
    int n = 0;
    ListNode *itr = head;
    while (itr)
    {
        itr = itr->next;
        n++;
    }
    int x = n / k;
    ListNode *curr = head, *forw = curr, *prev = nullptr;
    ListNode *plast = nullptr, *last = head;
    while (x--)
    {
        for (int i = 0; i < k; i++)
        {
            forw = curr->next;
            curr->next = prev;
            prev = curr;
            curr = forw;
        }
        last->next = curr;
        if (plast == nullptr)
            head = prev;
        else
            plast->next = prev;
        plast = last;
        last = curr;
    }
    return head;
}

// DAY 19 (Lowest Common Ancestor of a Binary Search Tree)===============================================================================

TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
{
    if (!root)
        return root;
    if (root->val < min(p->val, q->val))
        return lowestCommonAncestor(root->right, p, q);
    else if (root->val > max(p->val, q->val))
        return lowestCommonAncestor(root->left, p, q);
    return root;
}

// DAY 20 (Shuffle An Array)==================================================================================
class Solution
{
public:
    vector<int> a, b;
    Solution(vector<int> &nums)
    {
        a = nums;
        b = nums;
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset()
    {
        b = a;
        return b;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle()
    {
        for (int i = 0; i < b.size(); i++)
        {
            int j = rand() % (i + 1);
            swap(b[i], b[j]);
        }
        return b;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */

// DAY 21 (Push Dominoes)=========================================================================

string pushDominoes(string dominoes)
{
    int n = dominoes.size();
    vector<int> force(n, 0);
    int f = 0;
    for (int i = 0; i < n; i++)
    {
        if (dominoes[i] == 'R')
            f = n;
        else if (dominoes[i] == 'L')
            f = 0;
        else
            f = max(f - 1, 0);
        force[i] += f;
    }
    for (int i = n - 1; i >= 0; i--)
    {
        if (dominoes[i] == 'L')
            f = n;
        else if (dominoes[i] == 'R')
            f = 0;
        else
            f = max(f - 1, 0);
        force[i] -= f;
    }

    string ans = "";
    for (int i = 0; i < n; i++)
        ans += (force[i] > 0) ? 'R' : ((force[i] < 0) ? 'L' : '.');

    return ans;
}

// DAY 22 (Partition Array Into Disjoint Intervals)===============================================================

int partitionDisjoint(vector<int> &nums)
{
    int mx = -1, n = nums.size();

    vector<int> minar(n, 0);
    minar[n - 1] = -1;
    for (int i = n - 2; i >= 0; i--)
        minar[i] = min(nums[i + 1], ((i != n - 2) ? minar[i + 1] : INT_MAX));

    for (int i = 0; i < n; i++)
    {
        mx = max(mx, nums[i]);
        if (mx <= minar[i])
            return i + 1;
    }
    return n;
}

// ḌAY 23 (Binary Tree Pruning)==========================================================================

TreeNode *pruneTree(TreeNode *root)
{
    if (!root)
        return root;

    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);

    if (!root->left && !root->right && root->val == 0)
        return nullptr;
    return root;
}

// DAY 24 (Word Ladder 2)===========================================================================================

#define f first
#define s second

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList)
{
    unordered_map<string, int> m;
    for (string s : wordList)
        m[s] = INT_MAX;
    m[beginWord] = 0;

    if (!m.count(endWord))
        return {};

    vector<vector<string>> ans;

    queue<pair<string, vector<string>>> que;
    que.push({beginWord, {beginWord}});

    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();

        if (tp.f == endWord)
        {
            ans.push_back(tp.s);
            continue;
        }

        for (int i = 0; i < tp.f.size(); i++)
        {
            string x = tp.f;
            for (int c = 'a'; c <= 'z'; c++)
            {
                if (c == x[i])
                    continue;
                x[i] = c;
                if (!m.count(x))
                    continue;
                if (m[x] < tp.s.size())
                    continue;

                m[x] = tp.s.size();
                tp.s.push_back(x);
                que.push({x, tp.s});
                tp.s.pop_back();
            }
        }
    }
    return ans;
}

// DAY 25 (Non-negative Integers without Consecutive Ones)====================================================================

int findIntegers(int n)
{
    vector<int> fib(32);
    fib[0] = 1, fib[1] = 2;
    for (int i = 2; i < 32; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    int ans = 0, pbit = 0;
    for (int i = 31; i >= 0; i--)
    {
        if (n & (1 << i))
        {
            ans += fib[i];
            if (pbit == 1)
                return ans;
            pbit = 1;
        }
        else
            pbit = 0;
    }
    return ans + 1;
}

// DAY 26 (Convert Sorted Array To Binary Search Tree)==================================================================================

TreeNode *merge(int si, int ei, vector<int> &nums)
{
    if (si > ei)
        return nullptr;
    if (si == ei)
        return new TreeNode(nums[si]);

    int mid = (si + ei) >> 1;

    TreeNode *l = merge(si, mid - 1, nums);
    TreeNode *r = merge(mid + 1, ei, nums);

    return new TreeNode(nums[mid], l, r);
}

TreeNode *sortedArrayToBST(vector<int> &nums)
{
    return merge(0, nums.size() - 1, nums);
}

// DAY 27 (3 Sum Closest)===================================================================

int threeSumClosest(vector<int> &nums, int target)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int minabs = INT_MAX, ans = target;
    for (int i = 0; i < n; i++)
    {
        int l = i + 1, r = n - 1;
        while (l < r)
        {
            int sum = nums[i] + nums[l] + nums[r];

            if (abs(target - sum) < minabs)
            {
                minabs = abs(target - sum);
                ans = sum;
            }

            if (sum == target)
                return target;
            if (sum < target)
                l++;
            else
                r--;
        }
    }
    return ans;
}

// DAY 28 (Beautiful Array)==============================================================================

vector<int> beautifulArray(int n)
{
    vector<int> ans = {1};
    while (ans.size() < n)
    {
        vector<int> curr;
        for (int x : ans)
            if (2 * x - 1 <= n)
                curr.push_back(2 * x - 1);
        for (int x : ans)
            if (2 * x <= n)
                curr.push_back(2 * x);
        ans = curr;
    }
    return ans;
}

// DAY 29 (01 Matrix)=========================================================================================

vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    queue<pair<int, int>> que;
    vector<vector<int>> ans(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!mat[i][j])
                que.push({i * m + j, 0});

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    while (!que.empty())
    {
        int x = que.front().first;
        int dist = que.front().second;
        que.pop();
        int i = x / m;
        int j = x % m;
        ans[i][j] = dist;

        for (int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0], c = j + dir[d][1];
            if (r >= 0 && c >= 0 && r < n && c < m && mat[r][c])
            {
                mat[r][c] = 0;
                que.push({r * m + c, dist + 1});
            }
        }
    }
    return ans;
}

// DAY 30 (Map Sum Pairs)=============================================================================
class MapSum
{
public:
    /** Initialize your data structure here. */

    class trie
    {
    public:
        vector<trie *> t;
        int sum;
        int wordAns;
        trie()
        {
            this->t.assign(26, nullptr);
            this->sum = 0;
            this->wordAns = 0;
        }
    };

    trie *map;
    MapSum()
    {
        this->map = new trie();
    }

    void insert(string key, int val)
    {
        trie *temp = map;
        for (char c : key)
        {
            if (!temp->t[c - 'a'])
                temp->t[c - 'a'] = new trie();
            temp = temp->t[c - 'a'];
        }
        int x = 0;
        if (temp->wordAns)
            x = temp->wordAns;

        temp = map;
        for (char c : key)
        {
            temp = temp->t[c - 'a'];
            temp->sum += val - x;
        }
        temp->wordAns = val;
    }

    int sum(string prefix)
    {
        trie *temp = map;
        int ans = 0;
        for (char c : prefix)
        {
            if (!temp->t[c - 'a'])
                return 0;
            temp = temp->t[c - 'a'];
        }
        return temp->sum;
    }
};

/**
 * Your MapSum object will be instantiated and called as such:
 * MapSum* obj = new MapSum();
 * obj->insert(key,val);
 * int param_2 = obj->sum(prefix);
 */

// DAY 31 (Trapping Rain water)========================================================================

int trap(vector<int> &height)
{
    int n = height.size();
    if (n <= 2)
        return 0;
    int lmax = height[0], rmax = height[n - 1];
    int l = 1, r = n - 2;

    int water = 0;
    while (l <= r)
    {
        if (lmax < rmax)
        {
            if (height[l] < lmax)
                water += lmax - height[l++];
            else
                lmax = height[l++];
        }
        else
        {
            if (height[r] < rmax)
                water += rmax - height[r--];
            else
                rmax = height[r--];
        }
    }
    return water;
}
