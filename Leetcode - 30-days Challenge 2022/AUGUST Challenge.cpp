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

// DAY 13 (30. Substring with Concatenation of All Words)=============================================================================

bool check(string s, int m, unordered_map<string,int> mp)
{
    for(int i = 0; i < s.size(); i += m)
    {
        string x = s.substr(i, m);
        if(mp[x]-- == 0) return false;
    }
    return true;
}

vector<int> findSubstring(string s, vector<string>& words) 
{
    int n = s.size();
    int m = words[0].size();
    int w = words.size() * m;

    unordered_map<string,int> mp;
    for(string word : words)
        mp[word]++;

    vector<int> ans;
    for(int i = 0; i <= n - w; i++)
    {
        if(check(s.substr(i, w), m, mp))
            ans.push_back(i);
    }

    return ans;
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

// APPROACH 2 (By Constructing Graph - BFS (to find all the possible parents) then DFS (to add all the paths)) [AC] -> time = O(n*n)

int start = -1, end = -1, n = 0;
vector<vector<int>> gp;
vector<int> minDist;
vector<vector<int>> parent;
vector<vector<int>> paths;

bool isConn(string x, string y)
{
    int diff = 0;
    for(int i = 0; i < x.size(); i++)
        diff += (x[i] != y[i]);
    return diff == 1;
}

void bfs()
{
    queue<int> que;
    que.push(start);
    minDist[start] = 0;
    parent[start] = {-1};

    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        if(u == end) continue;

        for(int v : gp[u])
        {
            if(minDist[v] > minDist[u] + 1)
            {
                minDist[v] = minDist[u] + 1;
                parent[v].clear();
                parent[v].push_back(u);
                que.push(v);
            }
            else if(minDist[v] == minDist[u] + 1)
                parent[v].push_back(u);
        }
    }
}

void dfs(int v, vector<int> &path)
{
    if(v == -1)
    {
        paths.push_back(path);
        return;
    }

    path.push_back(v);
    for(int u : parent[v])
        dfs(u, path);
    path.pop_back();
}

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) 
{
    n = wordList.size();
    for(int i = 0; i < n; i++)
    {
        if(wordList[i] == beginWord) start = i;
        else if(wordList[i] == endWord) end = i;
    }

    if(end == -1) return {};
    if(start == -1) 
    {
        wordList.push_back(beginWord);
        start = n++;
    }

    gp.resize(n);
    parent.resize(n);
    minDist.assign(n,INT_MAX);
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            if(isConn(wordList[i], wordList[j]))
            {
                gp[i].push_back(j);
                gp[j].push_back(i);
            }
        }
    }

    bfs();
    vector<int> path;
    dfs(end, path);

    vector<vector<string>> ans;
    for(vector<int> path : paths)
    {
        reverse(path.begin(), path.end());
        vector<string> curr;
        for(int x : path)
            curr.push_back(wordList[x]);
        ans.push_back(curr);
    }

    return ans;
}

// DAY 15 (13. Roman to Integer)=================================================================================================

int romanToInt(string s) 
{
    int n = s.size();
    unordered_map<char,int> mp;
    mp['I'] = 1;
    mp['V'] = 5;
    mp['X'] = 10;
    mp['L'] = 50;
    mp['C'] = 100;
    mp['D'] = 500;
    mp['M'] = 1000;

    int ans = 0;
    char p = '#';
    for(int i = n-1; i >= 0; i--)
    {
        if(p == '#' || mp[s[i]] >= mp[p])
            ans += mp[s[i]];
        else ans -= mp[s[i]];
        p = s[i];
    }

    return ans;
}

// DAY 16 (387. First Unique Character in a String)==============================================================================

int firstUniqChar(string s) 
{
    int cnt[26] = {0};
    for(int i = 0; i < s.size(); i++)
        cnt[s[i]-'a']++;

    for(int i = 0; i < s.size(); i++)
        if(cnt[s[i]-'a'] == 1) 
            return i;

    return -1;
}

// DAY 17 (804. Unique Morse Code Words)============================================================================================

int uniqueMorseRepresentations(vector<string>& words) 
{
    vector<string> map = {".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

    unordered_set<string> st;
    for(string word : words)
    {
        string res = "";
        for(char c : word)
            res += map[c-'a'];
        st.insert(res);
    }

    return st.size();
}

// DAY 18 (1338. Reduce Array Size to The Half)================================================================================================

int minSetSize(vector<int>& arr) 
{
    int n = arr.size();
    unordered_map<int,int> mp;
    for(int x : arr) mp[x]++;

    vector<int> cnts;
    for(auto p : mp)
        cnts.push_back(p.second);
    sort(cnts.rbegin(), cnts.rend());

    int ans = 0;
    while(n > arr.size()/2)
        n -= cnts[ans++];

    return ans;
}

// DAY 19 (659. Split Array into Consecutive Subsequences)===========================================================================================================

bool isPossible(vector<int>& nums) 
{
    unordered_map<int,int> cnt, nxt;
    for(int x : nums)
        cnt[x]++;

    for(int x : nums)
    {
        if(cnt[x] == 0) continue;

        if(nxt[x])
        {
            nxt[x]--;
            cnt[x]--;
            nxt[x+1]++;
        }
        else if(cnt[x] && cnt[x+1] && cnt[x+2])
        {
            cnt[x]--;
            cnt[x+1]--;
            cnt[x+2]--;
            nxt[x+3]++;
        }
        else return false;
    }

    return true;
}

// DAY 20 (871. Minimum Number of Refueling Stops)=============================================================================================

int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) 
{
    int n = stations.size();
    long lpos = 0, fuel = startFuel, stops = 0;
    priority_queue<long> maxFuel;
    for(int i = 0; i <= n; i++)
    {
        int x = i == n? target : stations[i][0];
        int dist = x - lpos;
        while(!maxFuel.empty() && dist > fuel)
        {
            fuel += maxFuel.top();
            maxFuel.pop();
            stops++;
        }
        if(dist > fuel) return -1;

        fuel -= dist;
        if(i == n) continue;
        lpos = stations[i][0];
        maxFuel.push(stations[i][1]);
    }

    return stops;
}

// DAY 21 (936. Stamping The Sequence)=========================================================================================================

int n, m;
vector<int> reverse_stamp(string &target, string &stamp)
{
    vector<int> curr;
    for(int i = 0; i < n; i++)
    {
        int j = i, k = 0;
        bool nonstar = false;
        while(j < n && k < m && (target[j] == stamp[k] || target[j] == '*'))
        {
            if(target[j] == stamp[k]) nonstar = true;
            j++, k++;
        }
        if(k == m && nonstar) 
        {
            curr.push_back(i);
            k = 0;
            while(k < m)
                target[i+k++] = '*';
        }
    }
    return curr;
}

vector<int> movesToStamp(string stamp, string target) 
{
    n = target.size(), m = stamp.size();
    string init = string(n, '*');

    vector<int> ans;
    while(target != init)
    {
        vector<int> curr = reverse_stamp(target, stamp);
        if(curr.empty()) return {};

        for(int i : curr)
            ans.push_back(i);
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// DAY 22 (342. Power of Four)=================================================================================

bool isPowerOfFour(int n) 
{
    return (n > 0) && ((n & (n-1)) == 0) && (n & 0x55555555);
}

// DAY 23 (234. Palindrome Linked List)========================================================================

bool isPalindrome(ListNode* head) 
{
    int n = 0;
    ListNode* itr = head;
    while(itr)
    {
        itr = itr->next;
        n++;
    }
    int x = n/2;

    ListNode* curr = head, *prev = nullptr, *forw = head;
    while(x--)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }

    ListNode* h1 = prev;
    ListNode* h2 = n&1? curr->next : curr;

    while(h1 && h2 && h1->val == h2->val)
    {
        h1 = h1->next;
        h2 = h2->next;
    }

    return !(h1 && h2);
}

// DAY 25 (326. Power of Three)========================================================================================

bool isPowerOfThree(int n) 
{
    return n > 0 && ((int)pow(3, 19) % n == 0);
}

// DAY 26 (383. Ransom Note)==================================================================================

bool canConstruct(string ransomNote, string magazine) 
{
    vector<int> map(26);
    for(char c : magazine)
        map[c-'a']++;
    for(char c : ransomNote)
        if(map[c-'a']-- == 0)
            return false;
    return true;
}

// DAY 26 (869. Reordered Power of 2)================================================================================

bool reorderedPowerOf2(int n) 
{
    string nn = to_string(n);
    string tmp = nn;
    sort(nn.begin(), nn.end());
    sort(tmp.rbegin(), tmp.rend());
    int last = stoi(tmp);

    long x = 1;
    while(x <= last)
    {
        string curr = to_string(x);
        sort(curr.begin(), curr.end());
        if(curr == nn) return true;
        x *= 2;
    }
    return false;
}

// DAY 27 (363. Max Sum of Rectangle No Larger Than K)===================================================================

int maxSumSubmatrix(vector<vector<int>>& matrix, int k) 
{
    int n = matrix.size(), m = matrix[0].size();
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            matrix[i][j] += j? matrix[i][j-1] : 0;

    int ans = INT_MIN;
    for(int st = 0; st < m; st++)
    {
        for(int end = st; end < m; end++)
        {
            set<int> psums = {0};
            int sum = 0;
            for(int i = 0; i < n; i++)
            {
                sum += matrix[i][end] - (st? matrix[i][st-1] : 0);
                auto itr = psums.lower_bound(sum - k);
                if(itr != psums.end())
                    ans = max(ans, sum - *itr);
                psums.insert(sum);
            }
        }
    }

    return ans;
}

// DAY 28 (1329. Sort the Matrix Diagonally)=========================================================================================

vector<vector<int>> diagonalSort(vector<vector<int>>& mat) 
{
    int n = mat.size(), m = mat[0].size();
    for(int i = n-1; i >= 0; i--)
    {
        vector<int> tmp;
        for(int ii = i, j = 0; ii < n && j < m; ii++, j++)
            tmp.push_back(mat[ii][j]);
        sort(tmp.begin(), tmp.end());
        for(int ii = i, j = 0, x = 0; ii < n && j < m; ii++, j++, x++)
            mat[ii][j] = tmp[x];
    }

    for(int j = 1; j < m; j++)
    {
        vector<int> tmp;
        for(int jj = j, i = 0; jj < m && i < n; jj++, i++)
        {
            tmp.push_back(mat[i][jj]);
        }
        sort(tmp.begin(), tmp.end());
        for(int jj = j, i = 0, x = 0; jj < m && i < n; jj++, i++, x++)
            mat[i][jj] = tmp[x];
    }

    return mat;
}

// DAY 29 (200. Number of Islands)=========================================================================================

void dfs(int i, int j, int n, int m, vector<vector<char>> &grid)
{
    if(i == -1 || j == -1 || i == n || j == m || grid[i][j] == '0')
        return;
    grid[i][j] = '0';

    dfs(i+1, j, n, m, grid);
    dfs(i, j+1, n, m, grid);
    dfs(i-1, j, n, m, grid);
    dfs(i, j-1, n, m, grid);
}

int numIslands(vector<vector<char>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    int islands = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j] == '1')
                islands++, dfs(i, j, n, m, grid);
    return islands;
}

// DAY 30 (48. Rotate Image)===================================================================================

void rotate(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < m; j++)
            swap(matrix[i][j], matrix[j][i]);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m/2; j++)
            swap(matrix[i][j], matrix[i][m-j-1]);
}

// DAY 31 (417. Pacific Atlantic Water Flow)========================================================================

void dfs(int i, int j, int n, int m, int prev, vector<vector<bool>> &vis, vector<vector<int>> &heights)
{
    if(i == n || j == m || i == -1 || j == -1 || vis[i][j] || heights[i][j] < prev) return;

    vis[i][j] = true;
    dfs(i+1, j, n, m, heights[i][j], vis, heights);
    dfs(i, j+1, n, m, heights[i][j], vis, heights);
    dfs(i-1, j, n, m, heights[i][j], vis, heights);
    dfs(i, j-1, n, m, heights[i][j], vis, heights);
}

vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) 
{
    int n = heights.size(), m = heights[0].size();
    vector<vector<int>> ans;
    vector<vector<bool>> pacific(n, vector<bool>(m, false));
    vector<vector<bool>> atlantic(n, vector<bool>(m, false));

    for(int i = 0; i < n; i++)
    {
        dfs(i, 0, n, m, INT_MIN, pacific, heights);
        dfs(i, m-1, n, m, INT_MIN, atlantic, heights);
    }
    for(int i = 0; i < m; i++)
    {
        dfs(0, i, n, m, INT_MIN, pacific, heights);
        dfs(n-1, i, n, m, INT_MIN, atlantic, heights);
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(pacific[i][j] && atlantic[i][j])
                ans.push_back({i,j});

    return ans;
}
