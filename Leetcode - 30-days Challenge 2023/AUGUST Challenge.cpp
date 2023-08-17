
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
