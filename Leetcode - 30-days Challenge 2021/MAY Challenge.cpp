
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