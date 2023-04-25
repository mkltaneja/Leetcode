// DAY 1 (704. Binary Search)====================================================================================

int search(vector<int>& nums, int target) 
{
    int lo = 0, hi = nums.size()-1;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(nums[mid] == target)
            return mid;
        if(nums[mid] < target)
            lo = mid + 1;
        else hi = mid - 1;
    }

    return -1;
}

// DAY 2 (2300. Successful Pairs of Spells and Potions)==========================================================

#define ll long long
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) 
{
    int n = spells.size(), m = potions.size();
    vector<int> ans(n);

    sort(potions.begin(), potions.end());

    for(int i = 0; i < n; i++)
    {
        ll req = (success + spells[i] - 1) / spells[i];
        int lb = lower_bound(potions.begin(), potions.end(), req) - potions.begin();
        ans[i] = m - lb;
    }

    return ans;
}

// DAY 3 (881. Boats to Save People)===========================================================================

int numRescueBoats(vector<int>& people, int limit) 
{
    sort(people.begin(), people.end());
    int lo = 0, hi = people.size()-1;
    int boats = 0;
    while(lo <= hi)
    {
        if(people[lo] + people[hi] > limit)
            hi--;
        else lo++, hi--;
        boats++;
    }

    return boats;
}

// DAY 4 (2405. Optimal Partition of String)================================================================

int partitionString(string s) 
{
    int subs = 1;
    vector<int> mp(26,0);
    for(int i = 0, j = 0; i < s.size(); i++)
    {
        if(mp[s[i]-'a'])
        {
            mp.assign(26,0);
            subs++;
        }
        mp[s[i]-'a']++;
    }

    return subs;
}

// DAY 5 (2439. Minimize Maximum of Array)==============================================================================

int minimizeArrayValue(vector<int>& nums) 
{
    long sum = 0, ans = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        sum += nums[i];
        ans = max(ans, (sum + i) / (i+1));
    }

    return ans;
}

// DAY 6 (1254. Number of Closed Islands)=========================================================================

int n = 0, m = 0;
void dfs(int i, int j, vector<vector<int>> &grid)
{
    if(i == -1 || j == -1 || i == n || j == m || grid[i][j])
        return;
    grid[i][j] = 1;
    dfs(i+1, j, grid);
    dfs(i, j+1, grid);
    dfs(i-1, j, grid);
    dfs(i, j-1, grid);
}

int closedIsland(vector<vector<int>>& grid) 
{
    n = grid.size(), m = grid[0].size();
    for(int i = 0; i < n; i++)
    {
        if(grid[i][0] == 0)
            dfs(i, 0, grid);
        if(grid[i][m-1] == 0)
            dfs(i, m-1, grid);
    }
    for(int i = 0; i < m; i++)
    {
        if(grid[0][i] == 0)
            dfs(0, i, grid);
        if(grid[n-1][i] == 0)
            dfs(n-1, i, grid);
    }

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j]) continue;
            dfs(i, j, grid);
            ans++;
        }
    }

    return ans;
}

// DAY 7 (1020. Number of Enclaves)============================================================================

int n, m;
int dfs(int i, int j, bool &canReachBoundary, vector<vector<int>> &grid)
{
    if(i == -1 || j == -1 || i == n || j == m)
    {
        canReachBoundary = true;
        return 0;
    }
    if(!grid[i][j]) return 0;

    grid[i][j] = 0;

    return dfs(i+1, j, canReachBoundary, grid) + 
            dfs(i, j+1, canReachBoundary, grid) + 
            dfs(i-1, j, canReachBoundary, grid) + 
            dfs(i, j-1, canReachBoundary, grid) + 1;
}

int numEnclaves(vector<vector<int>>& grid) 
{
    n = grid.size(), m = grid[0].size();

    int cells = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(!grid[i][j]) continue;
            bool canReachBoundary = false;
            int count = dfs(i, j, canReachBoundary,  grid);
            cells += canReachBoundary? 0 : count;
        }
    }

    return cells;
}

// DAY 8 (133. Clone Graph)================================================================================

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:

    unordered_map<int, Node*> vis;
    Node* cloneGraph(Node* node) 
    {
        if(!node) return nullptr;
        if(vis.count(node->val)) return vis[node->val];
        
        Node* root = new Node(node->val);
        vis[node->val] = root;

        for(Node* neighbor : node->neighbors)
            root->neighbors.push_back(cloneGraph(neighbor));
        

        return root;
    }
};

// DAY 9 (1857. Largest Color Value in a Directed Graph)================================================================

int largestPathValue(string colors, vector<vector<int>>& edges) 
{
    int n = colors.size();
    vector<int> inDeg(n,0);
    vector<vector<int>> gp(n);
    for(vector<int> &e : edges)
    {
        gp[e[0]].push_back(e[1]);
        inDeg[e[1]]++;
    }

    queue<int> que;
    vector<vector<int>> dp(n, vector<int> (26, 0));
    for(int i = 0; i < n; i++)
        if(inDeg[i] == 0)
            que.push(i);

    int visCnt = 0;
    int maxColor = 0;
    while(!que.empty())
    {
        int u = que.front();
        que.pop();
        visCnt++;
        maxColor = max(maxColor, ++dp[u][colors[u]-'a']);

        for(int v : gp[u])
        {
            for(int c = 0; c < 26; c++)
                dp[v][c] = max(dp[v][c], dp[u][c]);
            if(--inDeg[v] == 0)
                que.push(v);
        }
    }

    return visCnt == n? maxColor : -1;
}

// DAY 10 (20. Valid Parentheses)================================================================================

bool isValid(string s) 
{
    stack<char> st;
    for(char &c : s)
    {
        if(c == '(' || c == '{' || c == '[')
            st.push(c);
        else 
        {
            if(st.empty()) return false;
            if(c == ')' && st.top() != '(')
                return false;
            if(c == '}' && st.top() != '{')
                return false;
            if(c == ']' && st.top() != '[')
                return false;
            st.pop();
        }
    }

    return st.empty();
}

// DAY 11 (2390. Removing Stars From a String)===============================================================

string removeStars(string s) 
{
    stack<char> st;
    for(char &c : s)
    {
        if(c != '*')
            st.push(c);
        else st.pop();
    }
    string ans = "";
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// DAY 12 (71. Simplify Path)=================================================================================

string simplifyPath(string path) 
{
    int n = path.size();
    vector<string> st;
    for(int i = 0; i < n; i++)
    {
        int j = i;
        string curr = "";
        while(j < n && path[j] != '/')
            curr += path[j++];

        if(curr == "..")
        {
            if(!st.empty())
                st.pop_back();
        }
        else if(!curr.empty() && curr != ".")
            st.push_back(curr);
        i = j;
    }
    string ans = "";
    for(string &s : st)
        ans += "/" + s;

    return ans.empty()? "/" : ans;
}

// DAY 13 (946. Validate Stack Sequences)==========================================================================

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) 
{
    int n = pushed.size();
    stack<int> st;
    for(int i = 0, j = 0; i < n && j < n; i++)
    {
        st.push(pushed[i]);
        while(!st.empty() && j < n && st.top() == popped[j])
        {
            st.pop();
            j++;
        }
    }

    return st.empty();
}

// DAY 14 (516. Longest Palindromic Subsequence)=====================================================================

int longestPalindromeSubseq(string s) 
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int len = 1; len <= n; len++)
    {
        for(int i = 0, j = len-1; j < n; i++, j++)
        {
            if(len == 1)
            {
                dp[i][j] = 1;
                continue;
            }
            int x = i+1 < n? dp[i+1][j] : 0;
            int y = j? dp[i][j-1] : 0;
            int z = (i+1 < n && j) && (s[i] == s[j])? dp[i+1][j-1] + 2 : 0;
            dp[i][j] = max({x, y, z});
        }
    }
    return dp[0][n-1];
}

// DAY 15 (2218. Maximum Value of K Coins From Piles)========================================================================

int dfs(int i, int k, vector<vector<int>> &piles, vector<vector<int>> &dp)
{
    if(i == piles.size() || k == 0) return 0;
    if(dp[i][k] != -1) return dp[i][k];

    int ans = dfs(i+1, k, piles, dp);
    int sum = 0;
    for(int j = 0; j < piles[i].size() && j < k; j++)
    {
        sum += piles[i][j];
        ans = max(ans, dfs(i+1, k - j - 1, piles, dp) + sum);
    }
    return dp[i][k] = ans;
}

int maxValueOfCoins(vector<vector<int>>& piles, int k) 
{
    vector<vector<int>> dp(piles.size(), vector<int>(k+1, -1));
    return dfs(0, k, piles, dp);
}

// DAY 16 (1639. Number of Ways to Form a Target String Given a Dictionary)=======================================================

int mod = 1e9 + 7;

int numWays(vector<string>& words, string target) 
{
    int n = words[0].size(), m = target.size();
    vector<vector<int>> charCnt(n, vector<int>(26, 0));

    vector<int> dp(m+1, 0);
    dp[0] = 1;
    for(string &s : words)
        for(int i = 0; i < n; i++)
            charCnt[i][s[i]-'a']++;

    for(int i = 0; i < n; i++)
        for(int j = m-1; j >= 0; j--)
            dp[j+1] = ((dp[j+1] % mod) + 
            ((long)dp[j] % mod) * 
            (charCnt[i][target[j]-'a'] % mod)) % mod;

    return dp[m];
}

// DAY 17 (1431. Kids With the Greatest Number of Candies)=========================================================================

vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) 
{
    int maxCandies = 0;
    for(int iCandies : candies)
        maxCandies = max(maxCandies, iCandies);

    vector<bool> ans;
    for(int iCandies : candies)
    {
        if(iCandies + extraCandies >= maxCandies)
            ans.push_back(true);
        else
            ans.push_back(false);
    }

    return ans;
}

// DAY 18 (1768. Merge Strings Alternately)=================================================================================

string mergeAlternately(string word1, string word2) 
{
    int i = 0, j = 0, k = 0, n = word1.size(), m = word2.size();
    string ans = "";
    while(i < n && j < m)
        ans += ((k++) & 1)? word2[j++] : word1[i++];
    ans += i < n? word1.substr(i, n) : word2.substr(j, m);

    return ans;
}

// DAY 19 (1372. Longest ZigZag Path in a Binary Tree)======================================================================

// APPROACH 1 (Using DP) --> Amortized O(N)

map<pair<TreeNode*, int>, int> dp;

int zigZag(TreeNode* node, int dir)
{
    if(dp.count({node, dir})) return dp[{node, dir}];

    return !node? 0 : dp[{node, dir}] = 
        ((dir == 1? zigZag(node->left, -1) : zigZag(node->right, 1)) + 1);
}

int maxLen = 0;
void dfs(TreeNode* node)
{
    if(!node) return;

    maxLen = max({maxLen, zigZag(node->left, -1), zigZag(node->right, 1)});

    dfs(node->left);
    dfs(node->right);
}

int longestZigZag(TreeNode* root) 
{
    dfs(root);
    return maxLen;
}

// APPROACH 2 (Simple DFS) --> O(N) [OPTIMZIED]

int ans = 0;
int dfs(TreeNode* node, bool takeLeftAns)
{
    if(!node) return -1;

    int lans = dfs(node->left, false) + 1;
    int rans = dfs(node->right, true) + 1;
    ans = max({ans, lans, rans});

    return takeLeftAns? lans : rans;
}

int longestZigZag(TreeNode* root) 
{
    dfs(root, true);
    return ans;
}

// DAY 20 (662. Maximum Width of Binary Tree)===================================================================================

#define f first
#define s second
#define ull unsigned long long

unordered_map<int,ull> minLeft;
ull maxWidth = 0;

void dfs(int d, ull x, TreeNode* node)
{
    if(!node) return;

    if(!minLeft.count(d))
        minLeft[d] = x;

    maxWidth = max(maxWidth, x - minLeft[d] + 1);

    dfs(d+1, 2*x, node->left);
    dfs(d+1, 2*x+1, node->right);
}

int widthOfBinaryTree(TreeNode* root) 
{
    dfs(0, 0, root);
    return maxWidth;
}

// DAY 21 (879. Profitable Schemes)=============================================================================================

int mod = 1e9 + 7;
int dfs(int i, int prof, int n, int minP, vector<int>& group, vector<int>& profit, vector<vector<vector<int>>> &dp)
{
    if(n < 0) return 0;

    if(i == group.size()) return prof >= minP;
    if(dp[i][prof][n] != -1)
        return dp[i][prof][n];

    return 
        dp[i][prof][n] = 
        ((dfs(i+1, prof + min(minP - prof, profit[i]), n - group[i], 
            minP, group, profit, dp)) % mod
        + (dfs(i+1, prof, n, minP, group, profit, dp) % mod)) % mod;
}

int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) 
{
    int m = group.size();
    vector<vector<vector<int>>> dp(m, vector<vector<int>> (minProfit+1, vector<int> (n+1, -1)));
    return dfs(0, 0, n, minProfit, group, profit, dp);
}

// DAY 22 (1312. Minimum Insertion Steps to Make a String Palindrome)==============================================================

int minInsertions(string s) 
{
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int maxComSubseq = 1;
    for(int len = 1; len <= n; len++)
    {
        for(int i = 0, j = len-1; j < n; i++, j++)
        {
            if(len == 1)
            {
                dp[i][j] = 1;
                continue;
            }
            int exci = dp[i+1][j];
            int excj = dp[i][j-1];
            int excij = s[i] == s[j]? (dp[i+1][j-1] + 2) : 0;

            dp[i][j] = max({exci, excj, excij});
            maxComSubseq = max(maxComSubseq, dp[i][j]);
        }
    }

    return n - maxComSubseq;
}

// DAY 23 (1416. Restore The Array)======================================================================================

int mod = 1e9 + 7;
int numberOfArrays(string s, int k) 
{
    int n = s.size();
    vector<int> dp(n+1, 0);
    dp[n] = 1;
    for(int i = n-1; i >= 0; i--)
    {
        long x = 0;
        if(s[i] == '0') continue;
        for(int j = i; j < n; j++)
        {
            x = x*10 + (s[j]-'0');
            if(x > k) break;
            dp[i] = (dp[i] % mod + dp[j+1] % mod) % mod;
        }
    }

    return dp[0];
}

// DAY 24 (1046. Last Stone Weight)===================================================================================

int lastStoneWeight(vector<int>& stones) 
{
    priority_queue<int> pq;
    for(int stone : stones)
        pq.push(stone);

    while(pq.size() > 1)
    {
        int stone1 = pq.top();
        pq.pop();
        int stone2 = pq.top();
        pq.pop();

        int rem = stone1 - stone2;
        pq.push(rem);
    }

    return pq.top();
}

// DAY 25 (2336. Smallest Number in Infinite Set)==================================================================

class SmallestInfiniteSet {
public:

    set<int> st;
    int last = 1;
    SmallestInfiniteSet() 
    {
        
    }
    
    int popSmallest() 
    {
        if(st.empty()) st.insert(last++);

        int ans = *st.begin();
        st.erase(st.begin());
        return ans;
    }
    
    void addBack(int num) 
    {
        if(num <= last && !st.count(num))
        {
            if(num == last) last++;
            st.insert(num);
        }
    }
};

/**
 * Your SmallestInfiniteSet object will be instantiated and called as such:
 * SmallestInfiniteSet* obj = new SmallestInfiniteSet();
 * int param_1 = obj->popSmallest();
 * obj->addBack(num);
 */
