
// DAY 1 (77. Combinations)=================================================================================

vector<vector<int>> ans;
void dfs(int x, int n, int k, vector<int> &curr)
{
    if(curr.size() == k) 
    {
        ans.push_back(curr);
        return;
    }

    for(int y = x; y <= n; y++)
    {
        curr.push_back(y);
        dfs(y+1, n, k, curr);
        curr.pop_back();
    }
}

vector<vector<int>> combine(int n, int k) 
{
    vector<int> curr;
    dfs(1, n, k, curr);
    return ans;
}

// DAY 2 (46. Permutations)======================================================================================

vector<vector<int>> ans;
void dfs(int i, vector<int> &nums)
{
    if(i == nums.size()-1)
    {
        ans.push_back(nums);
        return;
    }

    for(int j = i; j < nums.size(); j++)
    {
        swap(nums[i], nums[j]);
        dfs(i+1, nums);
        swap(nums[i], nums[j]);
    }
}

vector<vector<int>> permute(vector<int>& nums)
{
    dfs(0, nums);
    return ans;
}

// DAY 3 (17. Letter Combinations of a Phone Number)================================================================================================

vector<string> keys = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string> ans;

void dfs(int i, string &word, string &digits)
{
    if(i == digits.size())
    {
        if(!word.empty())
            ans.push_back(word);
        return;
    }

    for(char c : keys[digits[i]-'2'])
    {
        word += c;
        dfs(i+1, word, digits);
        word.pop_back();
    }
}

vector<string> letterCombinations(string digits) 
{
    string word = "";
    dfs(0, word, digits);
    return ans;
}

// DAY 4 (139. Word Break)===============================================================================================

class Trie
{
    public:
    vector<Trie*> child;
    bool wordEnd;
    Trie()
    {
        this->child.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(string &word, Trie* root)
    {
        Trie* curr = root;
        for(char c : word)
        {
            if(!curr->child[c-'a'])
                curr->child[c-'a'] = new Trie();
            curr = curr->child[c-'a'];
        }
        curr->wordEnd = true;
    }
};
Trie* root = new Trie();

bool canSegment(int i, Trie* itr, string &s, vector<int> &dp)
{
    if(i == s.size()) return true;
    if(dp[i] != -1) return dp[i];

    Trie* curr = itr;
    for(int j = i; j < s.size() && curr->child[s[j]-'a']; j++)
    {
        Trie* nxt = curr->child[s[j]-'a'];
        if(nxt->wordEnd)
            if(canSegment(j+1, root, s, dp))
                return dp[j] = 1;
        curr = nxt;
    }
    return dp[i] = 0;
}

bool wordBreak(string s, vector<string>& wordDict) 
{
    for(string &word : wordDict)
        root->insert(word, root);
    
    Trie* itr = root;
    vector<int> dp(s.size(), -1);
    return canSegment(0, itr, s, dp);
}

// DAY 5 (95. Unique Binary Search Trees II)==================================================================

vector<TreeNode*> dfs(int l, int r)
{
    if(l >= r)
    {
        if(l == r) 
            return {new TreeNode(l)};
        return {nullptr};
    }


    vector<TreeNode*> currAns;
    for(int x = l; x <= r; x++)
    {
        vector<TreeNode*> lans = dfs(l, x-1);
        vector<TreeNode*> rans = dfs(x+1, r);

        for(TreeNode* lTree : lans)
            for(TreeNode* rTree : rans)
                currAns.push_back(new TreeNode(x, lTree, rTree));
    }

    return currAns;
}

vector<TreeNode*> generateTrees(int n) 
{
    return dfs(1, n);
}

// DAY 6 (920. Number of Music Playlists)====================================================================================

#define ll long long
int mod = 1e9 + 7;
ll nn = 0, kk = 0;
ll totalPlaylists(ll i, ll j, vector<vector<ll>> &dp)
{
    if(i == 0 && j == 0) return 1ll;
    if(i == 0 || j == 0) return 0ll;
    if(dp[i][j] != -1) return dp[i][j];

    ll uniqueSong = (totalPlaylists(i-1, j-1, dp) % mod
                     * (nn - (i - 1)) % mod) % mod;
    ll existingSong = i > kk? ((totalPlaylists(i, j-1, dp) % mod
                     * (i - kk) % mod) % mod) : 0ll;

    return dp[i][j] = (uniqueSong % mod + existingSong % mod) % mod;
}

int numMusicPlaylists(int n, int goal, int k) 
{
    nn = n, kk = k;
    vector<vector<ll>> dp(n+1, vector<ll>(goal+1, -1));
    return totalPlaylists(n, goal, dp);
}

// DAY 7 (74. Search a 2D Matrix)=============================================================================================

bool searchMatrix(vector<vector<int>>& matrix, int target) 
{
    int n = matrix.size(), m = matrix[0].size();
    int lo = 0, hi = n*m-1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        int r = mid / m;
        int c = mid % m;
        if(matrix[r][c] == target)
            return true;
        if(matrix[r][c] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return false;
}

// DAY 8 (33. Search in Rotated Sorted Array)======================================================================================

// APPROACH 1 (Using 2 loops - Find pivot then binary search) --> O(2*logn)

int findPivot(int n, vector<int> &nums)
{
    int lo = 0, hi = n-1;
    int ans = -1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(nums[mid] > nums[n-1])
            lo = mid + 1;
        else
        {
            ans = mid;
            hi = mid - 1;
        }
    }
    return ans;
}

int findTarget(int n, vector<int> &nums, int start, int target)
{
    int lo = start, hi = start + n - 1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        int idx = mid % n;
        if(nums[idx] == target)
            return idx;
        if(nums[idx] < target)
            lo = mid + 1;
        else hi = mid - 1;
    }

    return -1;
}

int search(vector<int>& nums, int target) 
{
    int n = nums.size();
    int start = findPivot(n, nums);
    return findTarget(n, nums, start, target);
}

// APPROACH 2 (Using 1 loop) --> time = (logn)

int search(vector<int>& nums, int target) 
{
    int n = nums.size();
    int lo = 0, hi = n-1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(nums[mid] == target)
            return mid;
        if(nums[mid] >= nums[lo])
        {
            if(target >= nums[lo] && target < nums[mid])
                hi = mid - 1;
            else lo = mid + 1;
        }
        else
        {
            if(target <= nums[hi] && target > nums[mid])
                lo = mid + 1;
            else hi = mid - 1;
        }
    }

    return -1;
}

// DAY 9 (2616. Minimize the Maximum Difference of Pairs)=========================================================================

int minimizeMax(vector<int>& nums, int p) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int lo = 0, hi = nums[n-1] - nums[0];
    while(lo < hi)
    {
        int candidate = lo + ((hi - lo) >> 1);
        int pairs = 0;
        for(int i = 0; i < n-1; i++)
            if(abs(nums[i+1] - nums[i]) <= candidate)
                pairs++, i++;
        if(pairs >= p)
            hi = candidate;
        else lo = candidate + 1;
    }

    return lo;
}

// DAY 10 (81. Search in Rotated Sorted Array II)===============================================================================================


bool hasAmbiguity(int lo, int mid, vector<int> &nums)
{
    return nums[mid] == nums[lo];
}

int existInFirst(int lo, int x, vector<int> &nums)
{
    return nums[lo] <= x;
}

bool search(vector<int>& nums, int target) 
{
    int lo = 0, hi = nums.size() - 1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);

        if(nums[mid] == target) return true;
        
        if(hasAmbiguity(lo, mid, nums))
        {
            lo++;
            continue;
        }

        int midInFirst = existInFirst(lo, nums[mid], nums);
        int tarInFirst = existInFirst(lo, target, nums);
        if(midInFirst ^ tarInFirst)
        {
            if(midInFirst)
                lo = mid + 1;
            else hi = mid - 1;
        }
        else 
        {
            if(nums[mid] < target)
                lo = mid + 1;
            else hi = mid - 1;
        }
    }

    return false;
}

// DAY 11 (518. Coin Change II)==================================================================

int change(int amount, vector<int>& coins) 
{
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for(int i = 0; i < coins.size(); i++)
    {
        vector<int> curr_dp = dp;
        for(int x = coins[i]; x <= amount; x++)
            dp[x] += dp[x - coins[i]];
    }
    return dp[amount];
}

// DAY 12 (63. Unique Paths II)==========================================================================

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) 
{
    int n = obstacleGrid.size(), m = obstacleGrid[0].size();
    vector<vector<long>> dp(n, vector<long>(m, 0));

    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            if(i == n-1 && j == m-1)
            {
                if(obstacleGrid[i][j] == 1)
                    return 0;
                dp[i][j] = 1;
                continue;
            }
            if(obstacleGrid[i][j] == 1) continue;

            long rAns = j == m-1? 0 : dp[i][j+1];
            long dAns = i == n-1? 0 : dp[i+1][j];
            dp[i][j] = rAns + dAns;
        }
    }

    return dp[0][0];
}

// DAY 13 (2369. Check if There is a Valid Partition For The Array)=============================================================================

bool validPartition(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> dp(n+1);
    dp[0] = 1;
    dp[1] = 0;
    for(int i = 1; i < n; i++)
    {
        int a = nums[i];
        int b = nums[i-1];
        if(a == b) 
            dp[(i)+1] = dp[(i-2)+1];
        
        if(i == 1) continue;

        int c = nums[i-2];
        if(a == b && b == c || a == b+1 && b == c+1)
            dp[(i)+1] |= dp[(i-3)+1];
    }

    return dp[n];
}

// DAY 14 (215. Kth Largest Element in an Array)==================================================================================

int findKthLargest(vector<int>& nums, int k) 
{
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int x : nums)
    {
        pq.push(x);
        if(pq.size() > k)
            pq.pop();
    }
    return pq.top();
}

// DAY 15 (86. Partition List)====================================================================================

ListNode* partition(ListNode* head, int x) 
{
    ListNode *lessHead = new ListNode(INT_MIN), *lessItr = lessHead;
    ListNode *moreHead = new ListNode(INT_MIN), *moreItr = moreHead;
    ListNode *itr = head;

    while(itr)
    {
        if(itr->val >= x)
        {
            moreItr->next = itr;
            moreItr = moreItr->next;
        }
        else 
        {
            lessItr->next = itr;
            lessItr = lessItr->next;
        }
        itr = itr->next;
    }
    moreHead = moreHead->next;
    lessItr->next = moreHead;
    moreItr->next = nullptr;

    return lessHead->next;
}

// DAY 16 (239. Sliding Window Maximum)======================================================================

// APPROACH 1 (Using Priority Queue) --> time = O(n*logn), space = O(2*n)

#define f first
#define s second
vector<int> maxSlidingWindow(vector<int>& nums, int k) 
{
    int n = nums.size();
    priority_queue<pair<int,int>> pq;
    vector<int> ans(n-k+1);
    for(int i = 0; i < n; i++)
    {
        pq.push({nums[i], i});
        while(pq.size() > k && pq.top().s <= i-k)
            pq.pop();
        if(i+1 >= k)
            ans[i-k] = pq.top().f;
    }
    return ans;
}

// APPROACH 2 (Using Deque) --> time = O(2*n), space = O(2*n)

#define f first
#define s second
vector<int> maxSlidingWindow(vector<int>& nums, int k) 
{
    int n = nums.size();
    deque<pair<int,int>> dq;
    vector<int> ans(n-k+1);
    for(int i = 0; i < n; i++)
    {
        while(!dq.empty() && (dq.back().s <= i-k || dq.back().f <= nums[i]))
            dq.pop_back();
        dq.push_back({nums[i], i});
        while(!dq.empty() && dq.front().s <= i-k)
            dq.pop_front();
        if(i+1 >= k)
            ans[i+1-k] = dq.front().f;
    }
    return ans;
}

// APPROACH 3 (Using Prefix Max, and Suffix Max arrays) --> time = O(2*n), space = O(3*n)

vector<int> maxSlidingWindow(vector<int>& nums, int k) 
{
    int n = nums.size();
    vector<int> ans(n-k+1), pmax(n), smax(n);
    pmax[0] = nums[0];
    smax[n-1] = nums[n-1];
    for(int i = 1, j = n-2; i < n && j >= 0; i++, j--)
    {
        if(i % k == 0)
            pmax[i] = nums[i];
        else pmax[i] = max(pmax[i-1], nums[i]);

        if(j % k == k-1)
            smax[j] = nums[j];
        else smax[j] = max(smax[j+1], nums[j]);
    }

    for(int i = 0; i < n-k+1; i++)
        ans[i] = max(smax[i], pmax[i+k-1]);
    return ans;
}

// DAY 17 (542. 01 Matrix)==============================================================================

// APPROACH 1 (Using BFS) --> time = O(n*m), space = O(n*m)

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) 
{
    int n = mat.size(), m = mat[0].size();
    queue<vector<int>> que;
    vector<vector<int>> ans(n, vector<int> (m, 0));
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(!mat[i][j])
                que.push({i, j, 0});
    
    while(!que.empty())
    {
        int x = que.front()[0];
        int y = que.front()[1];
        int dist = que.front()[2];
        que.pop();

        for(int d = 0; d < 4; d++)
        {
            int dx = dir[d][0], dy = dir[d][1];
            int r = x + dx;
            int c = y + dy;
            if(r == -1 || c == -1 || r == n || c == m || mat[r][c] != 1)
                continue;
            mat[r][c] = 0;
            ans[r][c] = dist + 1;
            que.push({r, c, dist + 1});
        }
    }

    return ans;
}

// APPROACH 2 (Using Tabulated form of DFS) --> time = O(n*m), space = O(1)

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) 
{
    int n = mat.size(), m = mat[0].size();
    int inf = n + m;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(mat[i][j] == 0) continue;
            mat[i][j] = min(i? mat[i-1][j] : inf, j? mat[i][j-1] : inf) + 1;
        }
    }
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            if(mat[i][j] == 0) continue;
            mat[i][j] = min({mat[i][j], 
                            i != n-1? mat[i+1][j] + 1 : inf, 
                            j != m-1? mat[i][j+1] + 1 : inf});
        }
    }
    
    return mat;
}

// DAY 18 (1615. Maximal Network Rank)==================================================================================

int maximalNetworkRank(int n, vector<vector<int>>& roads) 
{
    vector<vector<int>> graph(n, vector<int>(n, 0));
    vector<int> rank(n);
    for(vector<int> &road : roads)
    {
        int u = road[0], v = road[1];
        rank[u]++;
        rank[v]++;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    int ans = 0;
    for(int u = 0; u < n; u++)
    {
        for(int v = u+1; v < n; v++)
        {
            int netRank = rank[u] + rank[v] - graph[u][v];
            ans = max(ans, netRank);
        }
    }

    return ans;
}

// DAY 19 (1489. Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree)===================================================================================

class DSU
{
    public:
    int n, maxSize;
    vector<int> par, psize;

    DSU(int n)
    {
        this->n = n;
        this->maxSize = 1;
        this->par.resize(n);
        this->psize.assign(n, 1);
        for(int i = 0; i < n; i++)
            par[i] = i;
    }

    int findPar(int u)
    {
        return par[u] = par[u] == u? u : findPar(par[u]);
    }
    bool merge(int u, int v)
    {
        int pu = findPar(u);
        int pv = findPar(v);
        if(pu == pv) return false;
        if(psize[pu] < psize[pv])
            swap(pu, pv);
        par[pv] = pu;
        psize[pu] += psize[pv];
        maxSize = max(maxSize, psize[pu]);

        return true;
    }
};

vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) 
{
    int m = edges.size();
    for(int i = 0; i < m; i++)
        edges[i].push_back(i);
    
    sort(edges.begin(), edges.end(), [](auto const &a, auto const &b){
        return a[2] < b[2];
    });
    
    DSU stdMST(n);
    int stdMSTwt = 0;
    for(auto &e : edges)
        if(stdMST.merge(e[0], e[1]))
            stdMSTwt += e[2];
    
    vector<vector<int>> ans(2);
    for(int i = 0; i < m; i++)
    {
        DSU iCritical(n);
        int iCriticalwt = 0;
        for(int j = 0; j < m; j++)
            if(j != i && iCritical.merge(edges[j][0], edges[j][1]))
                iCriticalwt += edges[j][2];

        // Check if edge "i" is critical -> if ignoring it makes graph disconnected, or increases the weight of MST
        if(iCritical.maxSize < n || iCriticalwt > stdMSTwt)
        {
            ans[0].push_back(edges[i][3]);
            continue;
        }

        // Else check for Pseudo-Critical
        DSU iPseudoCritical(n);
        iPseudoCritical.merge(edges[i][0], edges[i][1]);
        int iPseudoCriticalwt = edges[i][2];
        for(int j = 0; j < m; j++)
            if(j != i && iPseudoCritical.merge(edges[j][0], edges[j][1]))
                iPseudoCriticalwt += edges[j][2];

        // If adding it gives equal weight as standard MST, then its the Pseudo-Critical Edge
        if(iPseudoCriticalwt == stdMSTwt)
            ans[1].push_back(edges[i][3]);
    }

    return ans;
}

// DAY 20 (1203. Sort Items by Groups Respecting Dependencies)=========================================================================

vector<int> groupOrder, itemOrder;

bool bfs(queue<int> &que, vector<vector<int>> &gp, vector<int> &inDeg, vector<int> &order)
{
    for(int i = 0; i < inDeg.size(); i++)
        if(inDeg[i] == 0)
            que.push(i);
    
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int u = que.front();
            que.pop();
            order.push_back(u);

            for(int v : gp[u])
                if(--inDeg[v] == 0)
                    que.push(v);
        }
    }

    return true;
}

vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems)
{
    int x = 0;
    for(int i = 0; i < n; i++)
        if(group[i] == -1)
            group[i] = m + x++;

    vector<vector<int>> itemGp(n), groupGp(m+x);
    vector<int> itemInDeg(n, 0), groupInDeg(m+x, 0);
    queue<int> itemQue, groupQue;
    vector<int> itemVis(n), groupVis(m+x);
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < beforeItems[i].size(); j++)
        {
            itemGp[beforeItems[i][j]].push_back(i);
            itemInDeg[i]++;
            
            if(group[i] == group[beforeItems[i][j]]) continue;

            groupGp[group[beforeItems[i][j]]].push_back(group[i]);
            groupInDeg[group[i]]++;
        }
    }

    bfs(itemQue, itemGp, itemInDeg, itemOrder);
    if(itemOrder.size() != n)
        return {};

    bfs(groupQue, groupGp, groupInDeg, groupOrder);
    if(groupOrder.size() != m+x)
        return {};

    vector<int> ans;
    unordered_map<int,vector<int>> mp;
    for(int item : itemOrder)
        mp[group[item]].push_back(item);
    for(int group : groupOrder)
        for(int item : mp[group])
            ans.push_back(item);

    return ans;
}

// DAY 21 (459. Repeated Substring Pattern)===============================================================

// APPROACH 1 (Checking the original string in between the double of it) --> time = O(2*n + n^2), space = O(2*n)

bool repeatedSubstringPattern(string s) 
{
    string s2 = s + s;
    string s2Mid = s2.substr(1, s2.size()-2);

    return s2Mid.find(s) != -1;
}

// APPROACH 2 (Checking just using the prefix and suffix of string) --> time = O(n*p), space = O(1) [p = total prime numbers] [OPTIMIZED]

bool repeatedSubstringPattern(string s) 
{
    int n = s.size();
    for(int i = n/2; i >= 1; i--)
        if(n % i == 0)
            if(s.substr(0, n-i) == s.substr(i))
                return true;
    return false;
}

// DAY 22 (168. Excel Sheet Column Title)=============================================================================

string convertToTitle(int columnNumber) 
{
    string columnTitle = "";
    while(columnNumber)
    {
        columnTitle += char((--columnNumber % 26) + 'A');
        columnNumber /= 26;
    }
    reverse(columnTitle.begin(), columnTitle.end());
    return columnTitle;
}

// DAY 23 (767. Reorganize String)===============================================================================================

#define f first
#define s second

string reorganizeString(string s) 
{
    priority_queue<pair<int,char>> pq;
    vector<int> countMap(26, 0);
    for(char c : s)
        countMap[c-'a']++;
    for(int i = 0; i < 26; i++)
        if(countMap[i])
            pq.push({countMap[i], char(i+'a')});
    
    char prevChar = '#';
    string ans = "";

    while(!pq.empty())
    {
        int topCount = pq.top().f;
        char topChar = pq.top().s;
        pq.pop();

        if(prevChar == topChar)
        {
            if(pq.empty()) return "";
            int nextCount = pq.top().f;
            char nextChar = pq.top().s;
            pq.pop();

            ans += nextChar;
            pq.push({topCount, topChar});
            if(--nextCount)
                pq.push({nextCount, nextChar});
        }
        else 
        {
            ans += topChar;
            if(--topCount)
                pq.push({topCount, topChar});
        }
        prevChar = ans.back();
    }

    return ans;
}

// DAY 24 (68. Text Justification)=================================================================================================

vector<string> fullJustify(vector<string>& words, int maxWidth) 
{
    vector<string> ans;
    int i = 0, n = words.size();
    while(i < n)
    {
        int j = i;
        int gaps = 0, totalWordsLen = 0;
        string line = "";
        while(j < n && totalWordsLen + words[j].size() + gaps <= maxWidth)
        {
            totalWordsLen += words[j++].size();
            gaps++;
        }
        gaps--;

        int endSpaces = j == n? maxWidth - totalWordsLen - gaps : 0;
        int spaces = endSpaces? gaps : maxWidth - totalWordsLen;
        int equalSpaces = gaps? spaces / gaps : spaces;
        int extraSpaces = gaps? spaces % gaps : 0;
        if(endSpaces && equalSpaces)
            endSpaces--;
        int k = i;
        while(k < j)
        {
            line += words[k++];
            int blanks = equalSpaces;
            while(line.size() < maxWidth && blanks--)
                line += " ";
            if(line.size() < maxWidth && extraSpaces-- > 0)
                line += " ";
        }
        while(endSpaces--)
            line += " ";
        ans.push_back(line);

        i = j;
    }
    return ans;
}

// DAY 25 (97. Interleaving String)============================================================================================================

bool dfs(int i, int j, string &s1, string &s2, string &s3, vector<vector<int>> &dp)
{
    if(i+j == s3.size())
        return true;
    if(dp[i][j] != -1)
        return dp[i][j];

    if(i < s1.size() && s3[i+j] == s1[i])
        if(dfs(i+1, j, s1, s2, s3, dp))
            return dp[i][j] = true;
    if(j < s2.size() && s3[i+j] == s2[j])
        if(dfs(i, j+1, s1, s2, s3, dp))
            return dp[i][j] = true;
    
    return dp[i][j] = false;
}

bool isInterleave(string s1, string s2, string s3) 
{
    if(s3.size() != s1.size() + s2.size())
        return false;
    vector<vector<int>> dp(s1.size()+1, vector<int> (s2.size()+1, -1));
    return dfs(0, 0, s1, s2, s3, dp);
}

// DAY 26 (646. Maximum Length of Pair Chain)================================================================================================

// APPROACH 2 (Using binary search to find last short start)  -->  time = O(n*logn), space = O(n)

int upperBound(int end, int lo, int hi, vector<vector<int>> &pairs)
{
    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(pairs[mid][0] <= end)
            lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int findLongestChain(vector<vector<int>>& pairs) 
{
    int n = pairs.size();
    sort(pairs.begin(), pairs.end());
    vector<int> dp(n+1, 1);
    dp[n] = 0;
    for(int i = n-2; i >= 0; i--)
    {
        int ub = upperBound(pairs[i][1], i+1, n, pairs);
        dp[i] = max(dp[i+1], dp[ub] + 1);
    }
    return dp[0];
}

// APPROACH 2 (Moving Greedily to find count short end)  -->  time = O(n), space = O(1)  [OPTIMIZED]

int findLongestChain(vector<vector<int>>& pairs) 
{
    int n = pairs.size();
    sort(pairs.begin(), pairs.end(), [](auto const &a, auto const &b){
        return a[1] < b[1];
    });

    int chainSize = 1;
    int lastEnd = pairs[0][1];
    for(int i = 1; i < n; i++)
    {
        if(pairs[i][0] > lastEnd)
        {
            chainSize++;
            lastEnd = pairs[i][1];
        }
    }

    return chainSize;
}

// DAY 27 (403. Frog Jump)=================================================================================

unordered_map<int,int> stonesMap;
int n;
int dp[2005][2005];

bool dfs(int i, int jump, vector<int> &stones)
{
    if(i == n-1) return true;
    if(jump <= 0 || i < 0 || i >= n) return false;
    if(dp[i][jump] != -1) return dp[i][jump];

    bool kp1 = stonesMap.count(stones[i] + jump + 1) && dfs(stonesMap[stones[i] + jump + 1], jump + 1, stones);
    bool k = stonesMap.count(stones[i] + jump) && dfs(stonesMap[stones[i] + jump], jump, stones);
    bool km1 = stonesMap.count(stones[i] + jump - 1) && dfs(stonesMap[stones[i] + jump - 1], jump - 1, stones);

    return dp[i][jump] = kp1 || k || km1;
}

bool canCross(vector<int>& stones) 
{
    if(stones[1] - stones[0] != 1)
        return false;
    
    n = stones.size();
    memset(dp, -1, sizeof(dp));
    for(int i = 0; i < n; i++)
        stonesMap[stones[i]] = i;
    return dfs(1, 1, stones);
}

// DAY 28 (225. Implement Stack using Queues)=========================================================================================

class MyStack {
public:

    queue<int> que;
    int size;
    MyStack() 
    {
        this->size = 0;
    }
    
    void push(int x) 
    {
        que.push(x);
        int currSize = size++;
        while(currSize--)
        {
            que.push(que.front());
            que.pop();
        }
    }
    
    int pop() 
    {
        int top = que.front();
        que.pop();
        size--;
        return top;
    }
    
    int top() 
    {
        return que.front();
    }
    
    bool empty() 
    {
        return size == 0;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
