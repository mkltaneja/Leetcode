// DAY 1 (1704. Determine if String Halves Are Alike)===============================================================================

bool halvesAreAlike(string s) 
{
    int n = s.size();

    auto isVowel = [&](char c)
    {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int cnt = 0;
    for(int i = 0, j = n/2; j < n; i++, j++)
    {
        if(isVowel(s[i])) cnt++;
        if(isVowel(s[j])) cnt--;
    }
    return cnt == 0;
}

// DAY 2 (1657. Determine if Two Strings Are Close)==========================================================================

bool closeStrings(string word1, string word2) 
{
    vector<int> map1(26), map2(26);
    for(char &c : word1)
        map1[c-'a']++;
    for(char &c : word2)
        map2[c-'a']++;

    vector<int> unique1, unique2;
    for(int i = 0; i < 26; i++)
        if(map1[i])
            unique1.push_back(i);
    for(int i = 0; i < 26; i++)
        if(map2[i])
            unique2.push_back(i);

    sort(map1.begin(), map1.end());
    sort(map2.begin(), map2.end());

    return (unique1 == unique2) && (map1 == map2);
}

// DAY 3 (451. Sort Characters By Frequency)=====================================================================================

string frequencySort(string s) 
{
    unordered_map<char,int> mp;
    vector<pair<int,char>> map;
    for(char &c : s)
        mp[c]++;
    for(auto &p : mp)
        map.push_back({p.second, p.first});
    sort(map.rbegin(), map.rend());

    string ans = "";
    for(int i = 0; i < map.size(); i++)
        while(map[i].first--)
            ans += map[i].second;

    return ans;
}

// DAY (2256. Minimum Average Difference)========================================================================================

int minimumAverageDifference(vector<int>& nums) 
{
    int n = nums.size();
    long lsum = 0, rsum = 0, mn = INT_MAX;
    for(int x : nums)
        lsum += x;

    int ans = -1;
    for(int i = n-1; i >= 0; i--)
    {
        long ravg = i != n-1? (rsum / (n-i-1)) : 0;
        long lavg = lsum / (i+1);
        rsum += nums[i];
        lsum -= nums[i];

        long curr = abs(lavg - ravg);
        if(curr <= mn)
        {
            mn = curr;
            ans = i;
        }
    }

    return ans;
}

// DAY 5 (876. Middle of the Linked List)==================================================================================

ListNode* middleNode(ListNode* head) 
{
    ListNode* mid = head, *fast = head;
    while(fast && fast->next)
    {
        mid = mid->next;
        fast = fast->next->next;
    }

    return mid;
}

// DAY 6 (328. Odd Even Linked List)====================================================================================

ListNode* oddEvenList(ListNode* head) 
{
    if(!head || !head->next) return head;

    ListNode* oddHead = head, *evenHead = head->next;
    ListNode *odd = oddHead, *even = evenHead;
    while(odd->next && even->next)
    {
        odd->next = odd->next->next;
        odd = odd->next;
        even->next = even->next->next;
        even = even->next;
    }
    odd->next = evenHead;

    return head;
}

// DAY 7 (938. Range Sum of BST)===================================================================================

int rangeSumBST(TreeNode* root, int low, int high) 
{
    if(!root) return 0;
    if(root->val < low)
        return rangeSumBST(root->right, low, high);
    if(root->val > high)
        return rangeSumBST(root->left, low, high);
    return rangeSumBST(root->left, low, high) + rangeSumBST(root->right, low, high) + root->val;
}

// DAY 8 (872. Leaf-Similar Trees)===================================================================================

void addLeaves(TreeNode* root, vector<int> &leaves)
{
    if(!root) return;

    if(!root->left && !root->right) leaves.push_back(root->val);

    addLeaves(root->left, leaves);
    addLeaves(root->right, leaves);
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) 
{
    vector<int> leaves1, leaves2;
    addLeaves(root1, leaves1);
    addLeaves(root2, leaves2);

    return leaves1 == leaves2;
}

// DAY 9 (1026. Maximum Difference Between Node and Ancestor)=======================================================================

#define f first
#define s second

int maxDiff = -1e6;
void dfs(TreeNode* node, int mn, int mx)
{
    if(!node) return;

    mn = min(mn, node->val);
    mx = max(mx, node->val);
    dfs(node->left, mn, mx);
    dfs(node->right, mn, mx);
    maxDiff = max({maxDiff, abs(node->val - mn), abs(mx - node->val)});
}

int maxAncestorDiff(TreeNode* root) 
{
    dfs(root, root->val, root->val);
    return maxDiff;
}

// DAY 10 (1339. Maximum Product of Splitted Binary Tree)============================================================================

long maxProd = 0, sum = 0;

int sumDFS(TreeNode* node)
{
    if(!node) return 0;
    return sumDFS(node->left) + sumDFS(node->right) + node->val;
}

int split(TreeNode* node)
{
    if(!node) return 0;

    int lsum = split(node->left);
    int rsum = split(node->right);
    long currSum = lsum + rsum + node->val;
    long restSum = sum - (lsum + rsum + node->val);

    maxProd = max(maxProd, currSum * restSum);

    return currSum;
}

int maxProduct(TreeNode* root) 
{
    sum = sumDFS(root);
    split(root);
    return maxProd % (1000000007);
}

// DAY 11 (124. Binary Tree Maximum Path Sum)=======================================================================================

#define MN -30000001

int maxSum = MN;
int maxPathSum_helper(TreeNode* node)
{
    if(!node) return MN;

    int lsum = max(maxPathSum_helper(node->left), 0);
    int rsum = max(maxPathSum_helper(node->right), 0);
    maxSum = max({maxSum, lsum + node->val + rsum});

    return node->val + max({lsum, rsum});
}

int maxPathSum(TreeNode* root) 
{
    maxPathSum_helper(root);
    return maxSum;
}

// DAY 12 (70. Climbing Stairs)=================================================================================================

int climbStairs(int n) 
{
    if(n <= 1) return n;
    int ans = 1;
    int downDown = 1, down = 1;
    for(int i = 2; i <= n; i++)
    {
        ans = down + downDown;
        downDown = down;
        down = ans;
    }

    return ans;
}

// DAY 13 (931. Minimum Falling Path Sum)=======================================================================================

int minFallingPathSum(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> dp(n, vector<int>(m+1, INT_MAX));

    int ans = INT_MAX;
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = 0; j < m; j++)
        {
            int nextStep = i == n-1? 0 : min({(j? dp[i+1][j-1] : INT_MAX), dp[i+1][j], dp[i+1][j+1]});
            dp[i][j] = matrix[i][j] + nextStep;
            if(i == 0) ans = min(ans, dp[i][j]);
        }
    }

    return ans;
}

// DAY 14 (198. House Robber)===================================================================================================

int rob(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> dp(n+1, 0);
    dp[n-1] = nums[n-1];
    for(int i = n-2; i >= 0; i--)
        dp[i] = max(dp[i+1], nums[i] + dp[i+2]);

    return dp[0];
}

// DAY 15 (1143. Longest Common Subsequence)============================================================================================

int longestCommonSubsequence(string text1, string text2) 
{
    int n = text1.size(), m = text2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    int ans = 0;
    for(int i = n-1; i >= 0; i--)
    {
        for(int j = m-1; j >= 0; j--)
        {
            int ip1 = dp[i+1][j];
            int jp1 = dp[i][j+1];
            int ijp1 = dp[i+1][j+1];
            dp[i][j] = text1[i] == text2[j]? max({ip1, jp1, ijp1+1}) : max(ip1, jp1);
            ans = max(ans, dp[i][j]);
        }
    }

    return ans;
}

// DAY 16 (232. Implement Queue using Stacks)================================================================================================

class MyQueue {
public:

    stack<int> st1, st2;
    MyQueue() {
        
    }

    void fill()
    {
        if(st2.empty())
        {
            while(!st1.empty())
            {
                st2.push(st1.top());
                st1.pop();
            }
        }
    }
    
    void push(int x) 
    {
        st1.push(x);
    }
    
    int pop() 
    {
        fill();
        int ans = st2.top();
        st2.pop();
        return ans;
    }
    
    int peek() 
    {
        fill();
        return st2.top();
    }
    
    bool empty() 
    {
        return st1.empty() && st2.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// DAY 17 (150. Evaluate Reverse Polish Notation)=======================================================================

int evalRPN(vector<string>& tokens) 
{
    stack<long> st;
    auto isNum = [&](char &c){
        return (c >= '0' && c <= '9');
    };
    for(string &token: tokens)
    {
        if(isNum(token[0]) || (token.size() > 1 && isNum(token[1])))
            st.push(stoi(token));
        else 
        {
            long x = st.top();
            st.pop();
            long y = st.top();
            st.pop();

            if(token == "+")
                st.push(y+x);
            else if(token == "-")
                st.push(y-x);
            else if(token == "*")
                st.push(y*x);
            else if(token == "/")
                st.push(y/x);
        }
        cout<<token<<", ";
    }
    cout<<endl;

    return st.top();
}

// DAY 18 (739. Daily Temperatures)================================================================================

vector<int> dailyTemperatures(vector<int>& temperatures) 
{
    int n = temperatures.size();
    stack<int> st;
    vector<int> ans(n, 0);
    for(int i = 0; i < n; i++)
    {
        while(!st.empty() && temperatures[i] > temperatures[st.top()])
        {
            ans[st.top()] = i - st.top();
            st.pop();
        }
        st.push(i);
    }

    return ans;
}

// DAY 19 (1971. Find if Path Exists in Graph)=====================================================================

vector<int> par;
int findpar(int x)
{
    return par[x] == x? x : findpar(par[x]);
}

void merge(int x, int y)
{
    int px = findpar(x);
    int py = findpar(y);
    if(px == py) return;

    par[px] = py;
}

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) 
{
    par.resize(n+1);
    for(int i = 0; i <= n; i++)
        par[i] = i;
    for(vector<int> &e : edges)
        merge(e[0], e[1]);

    return findpar(source) == findpar(destination);
}

// DAY 20 (841. Keys and Rooms)======================================================================================

bool canVisitAllRooms(vector<vector<int>>& rooms) 
{
    int n = rooms.size();

    vector<int> vis(n);
    queue<int> que;
    que.push(0);
    vis[0] = 1;

    while(!que.empty())
    {
        for(int key : rooms[que.front()])
        {
            if(!vis[key])
            {
                que.push(key);
                vis[key] = 1;
            }
        }
        que.pop();
    }

    for(int i = 0; i < n; i++)
        if(!vis[i])
            return false;
    return true;
}

// DAY 21 (886. Possible Bipartition)==================================================================================


vector<vector<int>> gp;
vector<int> color;

bool isBipartite(int u, int clr)
{
    if(color[u] == (clr^1)) return false;
    if(color[u] != -1) return true;

    color[u] = clr;

    for(int v : gp[u])
        if(!isBipartite(v, clr ^ 1))
            return false;

    return true;
}

bool possibleBipartition(int n, vector<vector<int>>& dislikes) 
{
    gp.resize(n+1);
    color.assign(n+1, -1);

    for(vector<int> &dislike : dislikes)
    {
        int u = dislike[0], v = dislike[1];
        gp[u].push_back(v);
        gp[v].push_back(u);
    }

    for(int i = 1; i <= n; i++)
        if(color[i] == -1 && !isBipartite(i, 0))
            return false;

    return true;
}

// DAY 23 (834. Sum of Distances in Tree)====================================================================================

vector<int> cnt;
vector<int> ans;
vector<vector<int>> gp;

void dfsPost(int u, int p)
{
    for(int v : gp[u])
    {
        if(v == p) continue;

        dfsPost(v, u);
        cnt[u] += cnt[v];
        ans[u] += cnt[v] + ans[v];
    }
}

void dfsPre(int u, int p)
{
    for(int v : gp[u])
    {
        if(v == p) continue;

        ans[v] = (ans[u] - cnt[v]) + (gp.size() - cnt[v]);
        dfsPre(v, u);
    }
}

vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) 
{
    cout<<n<<endl;
    cnt.assign(n, 1);
    ans.assign(n, 0);
    gp.resize(n);
    for(int i = 0; i < edges.size(); i++)
    {
        gp[edges[i][0]].push_back(edges[i][1]);
        gp[edges[i][1]].push_back(edges[i][0]);
    }
    dfsPost(0, -1);
    dfsPre(0, -1);

    return ans;
}

// DAY 23 (309. Best Time to Buy and Sell Stock with Cooldown)===================================================================================

// dp0 = max value with not holding any stock
// dp1 = max value with holding some stocks
int maxProfit(vector<int>& prices) 
{
    int dp0 = 0, pdp0 = 0, dp1 = INT_MIN;
    for(int &x : prices)
    {
        int temp = dp0;
        dp0 = max(dp0, dp1 + x);
        dp1 = max(dp1, pdp0 - x);
        pdp0 = temp;
    }

    return dp0;
}

// DAY 24 (790. Domino and Tromino Tiling)==================================================================================

int mod = 1e9 + 7;
int numTilings(int n) 
{
    if(n <= 2) return n;

    long ans = 0;
    long a = 1, b = 1, c = 2;

    for(int i = 3; i <= n; i++)
    {
        ans = (c*2 + a) % mod;
        a = b;
        b = c;
        c = ans;
    }

    return ans;
}

// DAY 25 (2389. Longest Subsequence With Limited Sum)=====================================================================

vector<int> answerQueries(vector<int>& nums, vector<int>& queries) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    vector<int> psum(n);
    for(int i = 0; i < n; i++)
        psum[i] += nums[i] + (i? psum[i-1] : 0);

    vector<int> ans;
    for(int q : queries)
    {
        int lb = upper_bound(psum.begin(), psum.end(), q) - psum.begin();
        ans.push_back(lb);
    }

    return ans;
}

// DAY 26 (55. Jump Game)===================================================================================

bool canJump(vector<int>& nums) 
{
    int maxJump = 0;
    int n = nums.size();
    for(int i = 0; i < n; i++)
    {
        maxJump = max(maxJump-1, nums[i]);
        if(i != n-1 && maxJump == 0) return false;
    }

    return true;
}

// DAY 27 (2279. Maximum Bags With Full Capacity of Rocks)===========================================================

int maximumBags(vector<int>& capacity, vector<int>& rocks, int additionalRocks) 
{
    int n = capacity.size();
    vector<int> remaining(n);
    for(int i = 0; i < n; i++)
        remaining[i] = capacity[i] - rocks[i];
    sort(remaining.begin(), remaining.end());

    int ans = 0;
    while(ans < n && additionalRocks >= remaining[ans])
        additionalRocks -= min(remaining[ans++], additionalRocks);

    return ans;
}
