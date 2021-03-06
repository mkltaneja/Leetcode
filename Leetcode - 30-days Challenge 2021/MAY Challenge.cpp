
// DAY 1 (Prefix and Suffix Search)======================================================================
class WordFilter
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

        void insert(string &word, trie *t)
        {
            trie *temp = t;
            for (char c : word)
            {
                if (!temp->v[c - 'a'])
                    temp->v[c - 'a'] = new trie();
                temp = temp->v[c - 'a'];
            }
            temp->wordEnd = true;
        }
    };

    void allwords(trie *curr, string word, vector<string> &words)
    {
        if (curr->wordEnd)
            words.push_back(word);
        for (int i = 0; i < 26; i++)
            if (curr->v[i])
                allwords(curr->v[i], word + (char)(i + 'a'), words);
    }

    trie *t;
    unordered_map<string, int> pos;
    WordFilter(vector<string> &words)
    {
        this->t = new trie();
        for (int i = 0; i < words.size(); i++)
        {
            string word = words[i];
            t->insert(word, t);
            pos[word] = i;
        }
    }

    int f(string prefix, string suffix)
    {
        trie *temp = t;
        vector<string> words;
        for (char c : prefix)
        {
            if (temp->v[c - 'a'] == nullptr)
                return -1;
            temp = temp->v[c - 'a'];
        }
        allwords(temp, prefix, words);

        int ansi = -1;
        for (string word : words)
        {
            int n = word.size(), m = suffix.size();
            if ((n >= m) && (word.substr(n - m) == suffix) && (pos[word] > ansi))
                ansi = pos[word];
        }
        return ansi;
    }
};

// DAY 2 (Course Schedule 3)======================================================================

// APPROACH 1 (Subsequence) --> <O(2^n)
// TLE

int subseq(int i, int day, vector<vector<int>> &v)
{
    if (i == v.size())
        return 0;

    int ans = 0;
    if (day + v[i][0] <= v[i][1])
        ans = subseq(i + 1, day + v[i][0], v) + 1;
    ans = max(ans, subseq(i + 1, day, v));

    return ans;
}

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b)
         { return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1]; });
    return subseq(0, 0, courses);
}

// APPROACH 2 (Greedy -- Taking the minimum durations to maximize course count) --> O(n*logn)
// METHOD 1
// AC

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b)
         { return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1]; });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        if (day + dur <= lim)
        {
            day += dur;
            pq.push(dur);
        }
        else if (!pq.empty() && pq.top() > dur)
        {
            day += dur - pq.top();
            pq.pop();
            pq.push(dur);
        }
    }
    return pq.size();
}

// METHOD 2 (Shorter version of METHOD 1)

int scheduleCourse(vector<vector<int>> &courses)
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b)
         { return (a[1] == b[1]) ? a[0] < b[0] : a[1] < b[1]; });

    priority_queue<int> pq;
    int day = 0;
    for (vector<int> v : courses)
    {
        int dur = v[0], lim = v[1];
        day += dur;
        pq.push(dur);
        if (day > lim)
        {
            day -= pq.top();
            pq.pop();
        }
    }
    return pq.size();
}

// DAY 3 (Running Sum of 1D Array)============================================

vector<int> runningSum(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
        nums[i] += nums[i - 1];
    return nums;
}

// DAY 4 (Non - Decreasing Array)=====================================================

// METHOD 1 (Comparing with Previous) --> O(n)
bool checkPossibility(vector<int> &nums)
{
    int n = nums.size();
    bool changed = false;
    int prev = nums[0];
    for (int i = 1; i < n; i++)
    {
        if (nums[i] >= prev)
        {
            prev = nums[i];
            continue;
        }
        if (changed)
            return false;
        changed = true;
        if (i - 2 == -1 || nums[i] >= nums[i - 2])
            prev = nums[i];
    }
    return true;
}

// DAY 5 (Jump Game 2)==================================================================

// APPROACH 1 (Using DP) --> O(n^2)

int jump(vector<int> &nums)
{
    int n = nums.size();
    vector<int> jumps(n, n);
    jumps[n - 1] = 0;
    for (int i = n - 2; i >= 0; i--)
        for (int j = i + 1; j <= i + nums[i] && j < n; j++)
            jumps[i] = min(jumps[i], jumps[j] + 1);
    return jumps[0];
}

// APPROACH 2 (Storing max jumps at every "i" and updating total "jumps" whenever moves become 0) --> O(n)

int jump(vector<int> &nums)
{
    int n = nums.size();
    int jumps = 1;
    int jumplen = nums[0], moves = jumplen;
    for (int i = 1; i < n; i++)
    {
        if (i == n - 1)
            return jumps;
        jumplen = max(jumplen, i + nums[i]);
        if (--moves == 0)
        {
            moves = jumplen - i;
            jumps++;
        }
    }
    return 0;
}

// DAY 6 (Convert Sorted List to Binary Search Tree)===================================================

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution
{
public:
    TreeNode *constructBST(int st, int end, vector<int> &arr)
    {
        if (st > end)
            return nullptr;
        if (st == end)
            return new TreeNode(arr[st]);
        int mid = (st + end) >> 1;
        return new TreeNode(arr[mid], constructBST(st, mid - 1, arr), constructBST(mid + 1, end, arr));
    }

    TreeNode *sortedListToBST(ListNode *head)
    {
        vector<int> arr;
        while (head)
        {
            arr.push_back(head->val);
            head = head->next;
        }
        return constructBST(0, arr.size() - 1, arr);
    }
};

// DAY 7 (Delete Operation of 2 Strings)==============================================

int minDistance(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int a = (i - 1 >= 0) ? dp[i - 1][j] : 0;
            int b = (j - 1 >= 0) ? dp[i][j - 1] : 0;
            int c = (i - 1 >= 0 && j - 1 >= 0) ? dp[i - 1][j - 1] : 0;
            if (word1[i] == word2[j])
                dp[i][j] = c + 1;
            else
                dp[i][j] = max(a, b);
        }
    }
    int len = dp[n - 1][m - 1];
    return (n - len) + (m - len);
}

// DAY 8 (Super Palindromes)========================================================================

#define ll long long

bool ispal(string s)
{
    for (int i = 0; i < s.size() / 2; i++)
        if (s[i] != s[s.size() - i - 1])
            return false;
    return true;
}

int superpalindromesInRange(string left, string right)
{
    int ans = 0;
    ll l = stoll(left), r = stoll(right);

    if (l <= 1 && 1 <= r)
        ans++;
    if (l <= 4 && 4 <= r)
        ans++;
    if (l <= 9 && 9 <= r)
        ans++;

    for (ll i = 1; i <= 1e4; i++)
    {
        string s1 = to_string(i);
        string s2 = s1;
        reverse(s2.begin(), s2.end());
        ll n = stoll(s1 + s2);
        n *= n;
        if (n > r)
            break;
        if (ispal(to_string(n)))
        {
            if (n >= l)
            {
                // cout<<"even = "<<n<<endl;
                ans++;
            }
        }
        for (int x = 0; x <= 9; x++)
        {
            ll m = stoll(s1 + to_string(x) + s2);
            m *= m;
            if (m > r)
                break;
            if (m >= l && ispal(to_string(m)))
            {
                // cout<<"odd = "<<m<<endl;
                ans++;
            }
        }
    }

    return ans;
}
// DAY 9 (Construct Target Array with Mutiple Sums)=============================================

bool isPossible(vector<int> &target)
{
    long sum = 0;
    priority_queue<int> pq;
    for (int x : target)
    {
        if (x > 1)
            pq.push(x);
        sum += x;
    }

    while (!pq.empty())
    {
        int mx = pq.top();
        sum -= mx;
        pq.pop();

        if (sum <= 0 || mx - sum <= 0)
            return false;

        int n = mx % sum;
        sum += n;
        if (n > 1)
            pq.push(n);
    }
    return true;
}

// DAY 10 (Count Primes)=============================================================

// APPROACH 1 (Checking for prime for every number) --> O(n*sqrt(n))
// TLE

int countPrimes(int n)
{
    int ans = 0;
    for (int i = 2; i < n; i++)
    {
        bool isprime = true;
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                isprime = false;
                break;
            }
        }
        if (isprime)
            ans++;
    }
    return ans;
}

// APPROACH 2 (Prime Seive) --> O(n*log(log(n)))========================================

int countPrimes(int n)
{
    int ans = 0;
    vector<bool> prime(n, true);
    for (int i = 2; i * i < n; i++)
    {
        if (!prime[i])
            continue;
        for (int j = i * i; j < n; j += i)
            prime[j] = false;
    }

    for (int i = 2; i < n; i++)
        if (prime[i])
            ans++;

    return ans;
}

// DAY 11 (Maximum Points You can Obtain drom Cards)============================================================

// APPROACH 1 (DP) --> O(n^2)
// TLE
int dfs(int st, int end, int k, vector<int> &points, vector<vector<int>> &dp)
{
    if (k == 0)
        return 0;
    if (dp[st][end] != -1)
        return dp[st][end];

    int left = dfs(st + 1, end, k - 1, points, dp) + points[st];
    int right = dfs(st, end - 1, k - 1, points, dp) + points[end];

    return dp[st][end] = max(left, right);
}

int maxScore(vector<int> &cardPoints, int k)
{
    int n = cardPoints.size();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return dfs(0, n - 1, k, cardPoints, dp);
}

// APPROACH 2 (Sliding Window -- to see the min sum of subarray of size (n-k)) --> O(n)
// AC

int maxScore(vector<int> &cardPoints, int k)
{
    int n = cardPoints.size(), m = n - k;
    int totsum = 0;
    for (int x : cardPoints)
        totsum += x;

    int sum = 0, minsum = totsum;
    for (int i = 0; i < n; i++)
    {
        sum += cardPoints[i];
        if (i >= m)
            sum -= cardPoints[i - m];
        if (i >= m - 1)
            minsum = min(minsum, sum);
    }
    return totsum - minsum;
}

// DAY 12 (Range Sum Query 2D Immutable)=============================================================

// APPROACH 1 (Precalculating Prefix sum) --> O(max(n*(no. of calls), n*m))
// AC
class NumMatrix
{
public:
    vector<vector<int>> psum;
    int n, m;
    NumMatrix(vector<vector<int>> &matrix)
    {
        this->n = matrix.size();
        this->m = matrix[0].size();
        this->psum.assign(n, vector<int>(m));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                psum[i][j] = matrix[i][j] + ((j - 1 != -1) ? psum[i][j - 1] : 0);
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int sum = 0;
        for (int i = row1; i <= row2; i++)
            sum += psum[i][col2] - ((col1 - 1 != -1) ? psum[i][col1 - 1] : 0);
        return sum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

// APPROACH 2 (PRecalculating the Prefix sum - more Smartly) --> O(max((no. of calls), n*m))
class NumMatrix
{
public:
    vector<vector<int>> psum;
    int n, m;
    NumMatrix(vector<vector<int>> &matrix)
    {
        this->n = matrix.size();
        this->m = matrix[0].size();
        this->psum.assign(n, vector<int>(m));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int upper = (i - 1 >= 0) ? psum[i - 1][j] : 0;
                int left = (j - 1 >= 0) ? psum[i][j - 1] : 0;
                int diag = (i - 1 >= 0 && j - 1 >= 0) ? psum[i - 1][j - 1] : 0;
                psum[i][j] = (upper + left - diag) + matrix[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        int upper = (row1 - 1 >= 0) ? psum[row1 - 1][col2] : 0;
        int left = (col1 - 1 >= 0) ? psum[row2][col1 - 1] : 0;
        int diag = (row1 - 1 >= 0 && col1 - 1 >= 0) ? psum[row1 - 1][col1 - 1] : 0;

        int sum = psum[row2][col2] - (upper + left - diag);

        return sum;
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

// DAY 13 (Ambiguous Coordinates)=======================================================================

bool isvalid(string &s, int decpos)
{
    if (decpos && s[s.size() - 1] == '0')
        return false;
    if (s.size() > 1 && decpos != 1 && s[0] == '0')
        return false;
    return true;
}

void addDecimal(string &l, string &r, vector<string> &ans)
{
    vector<string> ls;
    for (int i = 0; i < l.size(); i++)
        if (isvalid(l, i))
            ls.push_back(l.substr(0, i) + (i ? "." : "") + l.substr(i));
    for (int i = 0; i < r.size(); i++)
    {
        if (isvalid(r, i))
        {
            string y = r.substr(0, i) + (i ? "." : "") + r.substr(i);
            for (string x : ls)
                ans.push_back("(" + x + ", " + y + ")");
        }
    }
}

vector<string> ambiguousCoordinates(string s)
{
    int n = s.size();
    vector<string> ans;
    for (int i = 1; i < n - 2; i++)
    {
        string l = s.substr(1, i);
        string r = s.substr(i + 1, (n - 1) - (i + 1));
        // cout<<l<<", "<<r<<endl;
        addDecimal(l, r, ans);
    }
    return ans;
}

// DAY 14 (Flatten Binary Tree to Linked List)===================================================

// APPROACH 1 (Keeping a global pointer variable)
TreeNode *list = new TreeNode(-1);
void preorder(TreeNode *node)
{
    if (!node)
        return;
    list->right = new TreeNode(node->val);
    list = list->right;
    // cout<<list->val<<endl;
    preorder(node->left);
    preorder(node->right);
}

void flatten(TreeNode *root)
{
    if (!root)
        return;
    TreeNode *head = list;
    preorder(root);
    *root = *head->right;
}

// APPROACH 2 (Standard Approach -- Keeping faith at every node to flatten their children)

void flatten(TreeNode *root)
{
    if (!root || (!root->left && !root->right))
        return;
    flatten(root->left);
    flatten(root->right);

    TreeNode *r = root->right;
    root->right = root->left;
    root->left = nullptr;
    while (root->right)
        root = root->right;
    root->right = r;
}

// DAY 15 (Valid Number)=======================================================================

bool isalpha(char c)
{
    c = tolower(c);
    return (c >= 'a' && c <= 'z');
}

bool isnum(char c)
{
    return (c >= '0' && c <= '9');
}

bool isNumber(string s)
{
    // cout<<s<<": \n";
    int n = s.size();
    bool e = false, num = false, dec = false;
    for (int i = 0; i < n; i++)
    {
        if (isnum(s[i]))
        {
            // cout<<s[i]<<" --> "<<"num\n";
            num = true;
            continue;
        }
        if (isalpha(s[i]))
        {
            // cout<<s[i]<<" --> "<<"alpha\n";
            if (e)
                return false;
            if (s[i] != 'e' && s[i] != 'E')
                return false;
            if (i == 0 || i == n - 1)
                return false;
            if (!num)
                return false;
            e = true;
        }
        else if (s[i] == '.')
        {
            // cout<<s[i]<<" --> "<<"dec\n";
            if (dec || e)
                return false;
            // if((i+1 != n && !isnum(s[i+1])) && (i-1 != -1 && !isnum(s[i-1]))) return false;
            dec = true;
        }
        else if (s[i] == '+' || s[i] == '-')
        {
            // cout<<s[i]<<" --> "<<"sign\n";
            if (dec && !e)
                return false;
            if (i - 1 != -1 && (s[i - 1] != 'e' && s[i - 1] != 'E'))
                return false;
            if (i == n - 1)
                return false;
            if (s[i + 1] == 'e' || s[i + 1] == 'E')
                return false;
        }
    }
    // cout<<endl;
    return num;
}

// DAY 16 (Binary Tree Cameras)=====================================================================

// 0 --> unmonitered, and needs camera
// 1 --> camera present, can monitor parent too
// 2 --> monitored, doesn't need camera
int ans = 0;
int mincameras(TreeNode *node)
{
    if (!node)
        return 2;
    if (!node->left && !node->right)
        return 0;
    auto l = mincameras(node->left);
    auto r = mincameras(node->right);

    if ((l && r) == 0)
    {
        ans++;
        return 1;
    }
    if (l == 2 && r == 2)
        return 0;
    return 2;
}

int minCameraCover(TreeNode *root)
{
    return (mincameras(root) == 0) ? ans + 1 : ans;
}

// DAY 17 (Longest String Chain)===================================================================

int longestStrChain(vector<string> &words)
{
    unordered_map<int, set<string>> mlen;
    for (auto s : words)
        mlen[s.size()].insert(s);
    unordered_map<string, int> dp;

    int ans = 1;
    for (int i = 16; i >= 0; i--)
    {
        if (mlen[i - 1].empty())
            continue;
        for (string par : mlen[i])
        {
            int pval = dp.count(par) ? dp[par] : 1;
            for (int j = 0; j < par.size(); j++)
            {
                string pred = par.substr(0, j) + par.substr(j + 1);
                int cval = dp.count(pred) ? dp[pred] : 1;
                if (mlen[i - 1].find(pred) != mlen[i - 1].end() && pval >= cval)
                {
                    dp[pred] = pval + 1;
                    ans = max(ans, pval + 1);
                }
            }
        }
    }
    return ans;
}

// DAY 18 (Find Duplicate File in the System)====================================================================

// APPROACH 1 (Naive Approach)

vector<vector<string>> findDuplicate(vector<string> &paths)
{
    unordered_map<string, vector<string>> res;
    for (string files : paths)
    {
        string path = "";
        int i = 0;
        while (files[i] != ' ')
            path += files[i++];
        i++;
        string file = "";
        while (i < files.size())
        {
            if (files[i] == '(')
            {
                i++;
                string content = "";
                while (files[i] != ')')
                    content += files[i++];
                res[content].push_back(path + '/' + file);
                file = "";
                i += 2;
            }
            if (i >= files.size())
                break;
            file += files[i++];
        }
    }

    vector<vector<string>> ans;
    for (auto p : res)
        if (p.second.size() > 1)
            ans.push_back(p.second);

    return ans;
}

// APPROACH 2 (Using String property - find)

vector<vector<string>> findDuplicate(vector<string> &paths)
{
    unordered_map<string, vector<string>> res;
    // cout<<string::npos<<endl;
    for (string files : paths)
    {
        int spacei = files.find(' ');
        string path = files.substr(0, spacei);
        while (spacei != string::npos)
        {
            int openi = files.find('(', spacei);
            string file = files.substr(spacei + 1, openi - spacei - 1);
            int closei = files.find(')', openi);
            string content = files.substr(openi + 1, closei - openi - 1);
            res[content].push_back(path + '/' + file);
            spacei = files.find(' ', closei);
        }
    }

    vector<vector<string>> ans;
    for (auto p : res)
        if (p.second.size() > 1)
            ans.push_back(p.second);

    return ans;
}

// DAY 19 (Minimum Moves to Equal Array Elements 2)==============================================================

int minMoves2(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int moves = 0;
    int med = nums[nums.size() / 2];
    for (int x : nums)
        moves += abs(med - x);
    return moves;
}

// DAY 20 (Binary Tree Level Order Traversal)=========================================================

// APPROACH 1 (BFS)

vector<vector<int>> levelOrder(TreeNode *root)
{
    if (!root)
        return {};
    vector<vector<int>> ans;
    queue<TreeNode *> que;
    que.push(root);
    while (!que.empty())
    {
        int sz = que.size();
        vector<int> temp;
        while (sz--)
        {
            TreeNode *top = que.front();
            que.pop();
            temp.push_back(top->val);
            if (top->left)
                que.push(top->left);
            if (top->right)
                que.push(top->right);
        }
        ans.push_back(temp);
    }
    return ans;
}

// APPROACH 2 (DFS)

void dfs(TreeNode *node, vector<vector<int>> &ans, int depth)
{
    if (!node)
        return;

    if (depth == ans.size())
        ans.push_back(vector<int>());
    ans[depth].push_back(node->val);

    dfs(node->left, ans, depth + 1);
    dfs(node->right, ans, depth + 1);
}

vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> ans;
    dfs(root, ans, 0);
    return ans;
}

// DAY 21 (Find and Replace Pattern)==============================================================

bool isvalid(string &s, string &pat)
{
    vector<char> map1(26);
    vector<char> map2(26);
    for (int i = 0; i < s.size(); i++)
    {
        if (map1[pat[i] - 'a'] != NULL && map1[pat[i] - 'a'] != s[i])
            return false;
        if (map2[s[i] - 'a'] != NULL && map2[s[i] - 'a'] != pat[i])
            return false;
        map1[pat[i] - 'a'] = s[i];
        map2[s[i] - 'a'] = pat[i];
    }
    return true;
}

vector<string> findAndReplacePattern(vector<string> &words, string pattern)
{
    vector<string> ans;
    for (string s : words)
        if (isvalid(s, pattern))
            ans.push_back(s);
    return ans;
}

// DAY 22 (N-Queens)====================================================================================

vector<string> board;
vector<vector<string>> ans;
int row = 0, col = 0, ldiag = 0, rdiag = 0;

bool isSafeHere(int r, int c, int n)
{
    if ((row & (1 << r)) || (col & (1 << c)) || (ldiag & (1 << (r + c))) || (rdiag & (1 << ((r - c) + (n - 1)))))
        return false;
    return true;
}

void nQueen(int idx, int placed, int n)
{
    if (placed == n)
    {
        ans.push_back(board);
        return;
    }
    for (int i = idx; i < n * n; i++)
    {
        int r = i / n, c = i % n;
        if (isSafeHere(r, c, n))
        {
            row ^= (1 << r);
            col ^= (1 << c);
            ldiag ^= (1 << (r + c));
            rdiag ^= (1 << ((r - c) + (n - 1)));
            board[r][c] = 'Q';
            nQueen(i + 1, placed + 1, n);
            board[r][c] = '.';
            row ^= (1 << r);
            col ^= (1 << c);
            ldiag ^= (1 << (r + c));
            rdiag ^= (1 << ((r - c) + (n - 1)));
        }
    }
}

vector<vector<string>> solveNQueens(int n)
{
    string line = "";
    for (int i = 0; i < n; i++)
        line += '.';
    board.resize(n, line);
    nQueen(0, 0, n);
    return ans;
}

// DAY 24 (To Lower case)========================================================================

string toLowerCase(string s)
{
    for (char &c : s)
        if (c - 'A' >= 0 && c - 'A' < 26)
            c = (c - 'A' + 'a');
    return s;
}

// DAY 25 (Evaluate Reverse Polish Notation)============================================================

bool isnum(string &s)
{
    if (s.size() == 1 && (s[0] - '0' < 0 || s[0] - '0' > 9))
        return false;
    return true;
}

int evalRPN(vector<string> &tokens)
{
    stack<int> st;
    for (string x : tokens)
    {
        if (isnum(x))
            st.push(stoi(x));
        else
        {
            int b = st.top();
            st.pop();
            int a = st.top();
            st.pop();
            int num;
            if (x == "+")
                num = a + b;
            else if (x == "-")
                num = a - b;
            else if (x == "*")
                num = a * b;
            else if (x == "/")
                num = a / b;
            st.push(num);
        }
    }
    return st.top();
}

// DAY 26 (Partition Into Minimum Number of Deci-Binary Numbers)=============================================

int minPartitions(string n)
{
    int ans = 0;
    for (char c : n)
    {
        ans = max(ans, c - '0');
        if (ans == 9)
            break;
    }
    return ans;
}

// DAY 27 (Maximum Product of Word Lengths)============================================================================

int maxProduct(vector<string> &words)
{
    int n = words.size();
    vector<int> map(n, 0);
    for (int i = 0; i < n; i++)
        for (char c : words[i])
            map[i] |= (1 << (c - 'a'));
    int ans = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if ((map[i] & map[j]) == 0)
                ans = max(ans, (int)(words[i].size() * words[j].size()));
    return ans;
}

// DAY 29 (Maximum Erasure Value)===================================================================================

int maximumUniqueSubarray(vector<int> &nums)
{
    unordered_map<int, int> m;
    int score = 0, maxscore = 0;

    int i = 0, j = 0;
    while (i < nums.size())
    {
        m[nums[i]]++;
        while (m[nums[i]] == 2)
        {
            m[nums[j]]--;
            score -= nums[j++];
        }
        score += nums[i++];
        maxscore = max(maxscore, score);
    }
    return maxscore;
}

// DAY 30 (Maximum Gap)================================================================================

int maximumGap(vector<int> &nums)
{
    int n = nums.size();
    if (n < 2)
        return 0;
    int mn = *min_element(nums.begin(), nums.end());
    int mx = *max_element(nums.begin(), nums.end());

    // Here bucket sort will be used, where we will make buckets, each of length "sz"

    int gap = ((mx - mn) + (n - 2)) / (n - 1); // Ceil of min value of maximum possible gaps
    // Note:- 1. Maximum gaps will always be from maximum value of previous bucket and minimum value of                         current bucket
    //  2. Count of bucket will be n-1 and and we are considering for n-2 elements (as we already                         considered mn and mx) so there may be an empty bucket also
    vector<int> minbucket(n - 1, INT_MAX);
    vector<int> maxbucket(n - 1, INT_MIN);

    for (int i = 0; i < n; i++)
    {
        if (nums[i] == mn || nums[i] == mx)
            continue;
        int id = (nums[i] - mn) / gap;
        minbucket[id] = min(minbucket[id], nums[i]);
        maxbucket[id] = max(maxbucket[id], nums[i]);
    }

    int ans = 0;
    int pmax = mn;
    for (int i = 0; i < n - 1; i++)
    {
        if (minbucket[i] == INT_MAX)
            continue;
        ans = max(ans, minbucket[i] - pmax);
        pmax = maxbucket[i];
    }
    ans = max(ans, mx - pmax);

    return ans;
}

// DAY 31 (Search Suggestion System)===========================================================================

// APPROACH 1 (Using Trie) --> O(m*x + n*(26^x)) [n = searchWord.size(), m = products.size(), x = average size of product[i]]
// AC

class trie
{
public:
    vector<trie *> child;
    bool wordEnd;
    trie()
    {
        this->child.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(trie *t, string &word)
    {
        for (char c : word)
        {
            if (!t->child[c - 'a'])
                t->child[c - 'a'] = new trie();
            t = t->child[c - 'a'];
        }
        t->wordEnd = true;
    }
};

bool findSuggestions(trie *t, vector<string> &words, string &word)
{
    if (t->wordEnd)
        words.push_back(word);
    if (words.size() == 3)
        return true;

    for (int i = 0; i < 26; i++)
    {
        if (t->child[i])
        {
            word += (char)(i + 'a');
            if (findSuggestions(t->child[i], words, word))
                return true;
            word.pop_back();
        }
    }
    return false;
}

vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord)
{
    trie *t = new trie();
    for (string word : products)
        t->insert(t, word);

    vector<vector<string>> suggestions(searchWord.size());
    string word = "";
    for (int i = 0; i < searchWord.size(); i++)
    {
        if (t->child[searchWord[i] - 'a'])
            t = t->child[searchWord[i] - 'a'];
        else
            break;
        word = searchWord.substr(0, i + 1);
        findSuggestions(t, suggestions[i], word);
    }
    return suggestions;
}

// APPROACH 2 [OPTIMIZED] (Sort and find words for every characted in one traversal) --> O((m*x)*log(m*x) + n) [n = searchWord.size(), m = products.size(), x = average size of product[i]]
// AC

vector<vector<string>> suggestedProducts(vector<string> &products, string searchWord)
{
    sort(products.begin(), products.end());

    int n = searchWord.size();
    vector<vector<string>> suggestions(n);

    int l = 0, r = products.size() - 1;

    for (int i = 0; i < n; i++)
    {
        char c = searchWord[i];

        while (l <= r && (products[l].size() <= i || products[l][i] < c))
            l++;
        while (l <= r && (products[r].size() <= i || products[r][i] > c))
            r--;

        for (int j = 0; (j < 3) && (l + j <= r); j++)
            suggestions[i].push_back(products[l + j]);
    }
    return suggestions;
}