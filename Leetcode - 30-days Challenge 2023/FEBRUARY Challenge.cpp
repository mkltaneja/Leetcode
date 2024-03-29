// DAY 1 (1071. Greatest Common Divisor of Strings)=============================================================================

// APPROACH 1 (Finding prime factors)

int gcd(int x, int y)
{
    while(x)
    {
        int z = y % x;
        y = x;
        x = z;
    }
    return y;
}

string gcdOfStrings(string str1, string str2) 
{
    vector<int> pFacs;
    int n = str1.size(), m = str2.size();
    int x = gcd(n, m);
    for(int i = 1; i*i <= x; i++)
    {
        if(x % i) continue;
        pFacs.push_back(i);
        if(i != x/i)
            pFacs.push_back(x/i);
    }

    sort(pFacs.rbegin(), pFacs.rend());
    for(int pf : pFacs)
    {
        bool isAns = true;
        string check = str1.substr(0,pf);
        for(int i = 0; i < n && isAns; i += pf)
        {
            if(str1.substr(i,pf) != check)
                isAns = false;
        }
        for(int i = 0; i < m && isAns; i += pf)
        {
            if(str2.substr(i,pf) != check)
                isAns = false;
        }

        if(isAns) return check;
    }

    return "";
}

// APPROACH 2 (GCD Approach)

string gcdOfStrings(string str1, string str2) 
{
    if(str1.size() < str2.size())
        return gcdOfStrings(str2, str1);
    if(str2.empty()) return str1;
    return str1.substr(0,str2.size()) == str2? gcdOfStrings(str1.substr(str2.size()), str2) : "";
}

// DAY 4 (567. Permutation in String)=================================================================================

bool checkInclusion(string s1, string s2) 
{
    int n = s1.size(), m = s2.size();
    vector<int> mp1(26,0);
    unordered_map<char,int> mp2;
    for(char &c : s1)
        mp1[c-'a']++;

    for(int i = 0; i < 26; i++)
        if(mp1[i])
            mp2[char(i+'a')] = -mp1[i];

    for(int i = 0; i < m; i++)
    {
        if(++mp2[s2[i]] == 0)
            mp2.erase(s2[i]);
        if(i >= n)
            if(--mp2[s2[i - n]] == 0)
                mp2.erase(s2[i - n]);
        if(mp2.empty()) return true;
    }

    return false;
}

// DAY 5 (438. Find All Anagrams in a String)===============================================================================

vector<int> findAnagrams(string s, string p) 
{
    int n = s.size(), m = p.size();
    unordered_map<char,int> mp;
    for(char c : p)
        mp[c]--;

    vector<int> ans;
    for(int i = 0; i < n; i++)
    {
        if(++mp[s[i]] == 0)
            mp.erase(s[i]);
        if(i >= m)
            if(--mp[s[i-m]] == 0)
                mp.erase(s[i-m]);
        if(mp.size() == 0)
            ans.push_back(i-m+1);
    }

    return ans;
}

// DAY 6 (1470. Shuffle the Array)===============================================================================

vector<int> shuffle(vector<int>& nums, int n) 
{
    vector<int> ans(2*n);
    for(int i = 0; i < n; i++)
    {
        ans[2*i] = nums[i];
        ans[2*i+1] = nums[n+i];
    }

    return ans;
}

// DAY 7 (904. Fruit Into Baskets)=================================================================================

int totalFruit(vector<int>& fruits) 
{
    int n = fruits.size();
    vector<int> typeCnt(n,0);
    int tot = 0, ans = 0;
    for(int i = 0, j = 0; i < n; i++)
    {
        if(typeCnt[fruits[i]]++ == 0)
            tot++;
        while(j < i && tot > 2)
        {
            if(--typeCnt[fruits[j++]] == 0)
                tot--;
        }
        ans = max(ans, i-j+1);
    }

    return ans;
}

// DAY 8 (45. Jump Game II)=====================================================================

// APPROACH 1 (Finding min jumps required for every position) --> time = O(n^2)

int jump(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> dp(n, 1e4+1);
    dp[n-1] = 0;
    for(int i = n-2; i >= 0; i--)
        for(int j = i+1; j < n && j <= i+nums[i]; j++)
            dp[i] = min(dp[i], dp[j]+1);

    return dp[0];
}

// APPROACH 2 (By taking maxJump position everytime) --> time = O(n)

int jump(vector<int>& nums) 
{
    int n = nums.size();
    int minJumps = 0, maxPos = 0, prevPos = 0;
    for(int i = 0; i < n-1; i++)
    {
        maxPos = max(maxPos, i + nums[i]);
        if(prevPos == i)
        {
            prevPos = maxPos;
            minJumps++;
        }
    }

    return minJumps;
}

// DAY 9 (2306. Naming a Company)=======================================================================

long long distinctNames(vector<string>& ideas) 
{
    vector<unordered_set<string>> suffix(26);
    for(string &s : ideas)
        suffix[s[0]-'a'].insert(s.substr(1));

    long long ans = 0;
    for(int i = 0; i < 26; i++)
    {
        for(int j = i+1; j < 26; j++)
        {
            long long cnt = 0;
            for(string suf : suffix[i])
                if(suffix[j].count(suf))
                    cnt++;
            ans += 2 * (suffix[i].size() - cnt) * (suffix[j].size() - cnt);
        }
    }

    return ans;
}

// DAY 10 (1162. As Far from Land as Possible)===============================================================

#define f first
#define s second
int maxDistance(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> que;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(grid[i][j])
                que.push({i, j});

    int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};

    int dist = -1;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int i = que.front().f;
            int j = que.front().s;
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];
                if(x == -1 || y == -1 || x == n || y == m || grid[x][y] != 0)
                    continue;

                grid[x][y] = -1;
                que.push({x, y});
            }
        }

        dist++;
    }

    return dist? dist : -1;
}

// DAY 11 (1129. Shortest Path with Alternating Colors)===========================================================================

#define f first
#define s second
vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>>& blueEdges) 
{
    vector<vector<int>> redGraph(n), blueGraph(n);
    for(vector<int> &v : redEdges)
        redGraph[v[0]].push_back(v[1]);
    for(vector<int> &v : blueEdges)
        blueGraph[v[0]].push_back(v[1]);

    queue<pair<int,int>> que;
    que.push({0, -1}); // -1 = no color, 0 = red, 1 = blue

    vector<int> minDist(n, -1);
    vector<bool> redVis(n, false), blueVis(n, false);
    minDist[0] = 0;
    redVis[0] = true;
    blueVis[0] = true;

    int dist = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int par = que.front().f;
            int color = que.front().s;
            que.pop();

            if(color == 0 || color == -1)
            {
                for(int child : blueGraph[par])
                {
                    if(blueVis[child] == false)
                    {
                        if(minDist[child] == -1)
                            minDist[child] = dist + 1;
                        blueVis[child] = true;
                        que.push({child, 1});
                    }
                }
            }

            if(color == 1 || color == -1)
            {
                for(int child : redGraph[par])
                {
                    if(redVis[child] == false)
                    {
                        if(minDist[child] == -1)
                            minDist[child] = dist + 1;
                        redVis[child] = true;
                        que.push({child, 0});
                    }
                }
            }
        }
        dist++;
    }

    return minDist;
}

// DAY 12 (2477. Minimum Fuel Cost to Report to the Capital)========================================================================

#define ll long long

ll fuel = 0;
ll totSeats, totCars = 0;
vector<vector<int>> graph;

int dfs(int p, int u)
{
    ll count = 1;
    for(int v : graph[u])
        if(v != p)
            count += dfs(u, v);

    fuel += (ll)totCars;
    ll newCars = (count + totSeats - 1) / totSeats;
    totCars = newCars;

    if(totCars == 0)
        return count;
    return count;
}

long long minimumFuelCost(vector<vector<int>>& roads, int seats) 
{
    int n = roads.size()+1;
    totSeats = seats;
    graph.resize(n);
    for(vector<int> &road : roads)
    {
        graph[road[0]].push_back(road[1]);
        graph[road[1]].push_back(road[0]);
    }

    dfs(-1, 0);
    return fuel;
}

// DAY 13 (1523. Count Odd Numbers in an Interval Range)=================================================================

int countOdds(int low, int high) 
{
    int n = high - low + 1;
    return (n + (low&1)) /2;
}

// DAY 14 (67. Add Binary)=================================================================================================

string addBinary(string a, string b) 
{
    int carry = 0;
    int i = a.size()-1, j = b.size()-1;
    string ans = "";
    while(i >= 0 || j >= 0)
    {
        int x = i >= 0? (a[i--]-'0') : 0;
        int y = j >= 0? (b[j--]-'0') : 0;
        int sum = x + y + carry;
        int curr = sum & 1;
        carry = sum >> 1;
        ans += char(curr + '0');
    }
    if(carry) ans += "1";

    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 15 (989. Add to Array-Form of Integer)================================================================================

vector<int> addToArrayForm(vector<int>& num, int k) 
{
    int carry = 0;
    int i = num.size()-1;
    while((k || carry) && i >= 0)
    {
        int sum = num[i] + (k%10) + carry;
        k /= 10;
        carry = sum / 10;
        num[i--] = sum % 10;
    }
    while(k || carry)
    {
        int sum = k%10 + carry;
        num.insert(num.begin(), sum%10);
        k /= 10;
        carry = sum/10;
    }

    return num;
}

// DAY 16 (104. Maximum Depth of Binary Tree)=================================================================================

int maxDepth(TreeNode* root) 
{
    return root? (max(maxDepth(root->left), maxDepth(root->right)) + 1) : 0;
}

// DAY 17 (783. Minimum Distance Between BST Nodes)================================================================================

int minDiffInBST(TreeNode* root) 
{
    int prev = -1e6;
    int minDiff = INT_MAX;
    while(root)
    {
        TreeNode* left = root->left;
        if(!left)
        {
            minDiff = min(minDiff, root->val - prev);
            prev = root->val;
            root = root->right;
        }
        else
        {
            TreeNode* right = left;
            while(right->right && right->right != root)
                right = right->right;
            if(!right->right)
            {
                right->right = root;
                root = left;
            }
            else
            {
                right->right = nullptr;
                minDiff = min(minDiff, root->val - prev);
                prev = root->val;
                root = root->right;
            }
        }
    }

    return minDiff;
}

// DAY 18 (226. Invert Binary Tree)============================================================================================

void swap(TreeNode* &nodeL, TreeNode* &nodeR)
{
    TreeNode* tmp = nodeL;
    nodeL = nodeR;
    nodeR = tmp;
}

TreeNode* invertTree(TreeNode* root) 
{
    if(!root) return nullptr;
    swap(root->left, root->right);
    invertTree(root->left);
    invertTree(root->right);
    return root;
}

// DAY 19 (103. Binary Tree Zigzag Level Order Traversal)======================================================================

vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
{
    vector<vector<int>> ans;
    if(!root) return ans;

    queue<TreeNode*> que;
    que.push(root);
    int lvl = 0;
    while(!que.empty())
    {
        int sz = que.size();
        vector<int> lvlNodes;
        while(sz--)
        {
            TreeNode* node = que.front();
            que.pop();
            lvlNodes.push_back(node->val);
            if(node->left) que.push(node->left);
            if(node->right) que.push(node->right);
        }
        if(lvl++ & 1) 
            reverse(lvlNodes.begin(), lvlNodes.end());
        ans.push_back(lvlNodes);
    }

    return ans;
}

// DAY 20 (35. Search Insert Position)========================================================================================

int searchInsert(vector<int>& nums, int target) 
{
    int lo = 0, hi = nums.size()-1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo)>>1);
        if(nums[mid] == target)
            return mid;
        if(nums[mid] < target)
            lo = mid + 1;
        else hi = mid - 1;
    }
    return lo;
}

// DAY 21 (540. Single Element in a Sorted Array)============================================================================

int singleNonDuplicate(vector<int>& nums) 
{
    int n = nums.size(), lo = 0, hi = n-1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo)>>1);
        int prev = mid? nums[mid-1] : INT_MIN;
        int nxt = mid+1 < n? nums[mid+1] : INT_MAX;

        if(prev != nums[mid] && nxt != nums[mid])
            return nums[mid];

        if(mid&1)
        {
            if(nums[mid] == prev)
                lo = mid + 1;
            else hi = mid - 1;
        }
        else 
        {
            if(nums[mid] == nxt)
                lo = mid + 2;
            else hi = mid - 2;
        }
    }

    return -1;
}

// DAY 22 (1011. Capacity To Ship Packages Within D Days)===================================================================

// APPROAC 1 (Finding the next upper linearly) --> time = O(n*logm)

bool check(int minW, int days, vector<int> &weights)
{
    int sum = 0;
    for(int x : weights)
    {
        if(x > minW || days == 0) return false;
        if(sum + x > minW) sum = x, days--;
        else sum += x;
    }
    days--;

    return days >= 0? true : false;
}

int shipWithinDays(vector<int>& weights, int days) 
{
    int lo = 1, hi = INT_MAX;
    while(lo < hi)
    {
        int mid = lo + ((hi - lo)>>1);
        int sum = 0;
        bool possible = check(mid, days, weights);
        if(possible) hi = mid;
        else lo = mid + 1;
    }

    return lo;
}

// APPROACH 2 (Finding next upper using upper_bound) --> time = O(logn*logm)

bool check(int minW, int days, vector<int> &psum)
{
    int i = 1;
    while(i < psum.size() && days--)
        i = upper_bound(psum.begin()+i, psum.end(), minW + psum[i-1]) - psum.begin();

    return days >= 0;
}

int shipWithinDays(vector<int>& weights, int days) 
{
    int n = weights.size();
    vector<int> psum(n+1,0);
    for(int i = 0; i < n; i++)
        psum[i+1] = weights[i] + psum[i];
    int lo = 1, hi = INT_MAX;
    while(lo < hi)
    {
        int mid = lo + ((hi - lo)>>1);
        int sum = 0;
        bool possible = check(mid, days, psum);
        if(possible) hi = mid;
        else lo = mid + 1;
    }

    return lo;
}

// DAY 23 (502. IPO)=====================================================================================================

#define f first
#define s second
int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) 
{
    int n = capital.size();
    vector<pair<int,int>> capProf(n);
    for(int i = 0; i < n; i++)
        capProf[i] = {capital[i], profits[i]};
    sort(capProf.begin(), capProf.end());

    priority_queue<int> pq;
    int i = 0;
    while(i < n && w >= capProf[i].f)
        pq.push(capProf[i++].s);

    while(!pq.empty() && k--)
    {
        w += pq.top();
        pq.pop();

        while(i < n && w >= capProf[i].f)
            pq.push(capProf[i++].s);
    }

    return w;
}

// DAY 24 (1675. Minimize Deviation in Array)===================================================================================

int minimumDeviation(vector<int>& nums) 
{
    priority_queue<int> pq;
    int mn = INT_MAX;
    for(int x : nums)
    {
        x *= (x&1)? 2 : 1;
        mn = min(mn, x);
        pq.push(x);
    }

    int ans = pq.top() - mn;
    while(pq.top()&1^1)
    {
        int x = pq.top();
        pq.pop();

        x >>= 1;
        mn = min(mn, x);
        pq.push(x);
        ans = min(ans, pq.top() - mn);
    }

    return ans;
}

// DAY 25 (121. Best Time to Buy and Sell Stock)===============================================================================

int maxProfit(vector<int>& prices) 
{
    int minBuy = INT_MAX, ans = 0;
    for(int x : prices)
    {
        ans = max(ans, x - minBuy);
        minBuy = min(minBuy, x);
    }
    return ans;
}

// DAY 26 (72. Edit Distance)=======================================================================================

int minDistance(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n+1, vector<int> (m+1, 0));
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= m; j++)
        {
            if(!i || !j)
            {
                dp[i][j] = i? i : j;
                continue;
            }
            if(word1[i-1] == word2[j-1]) 
                dp[i][j] = i && j? dp[i-1][j-1] : 0;
            else 
                dp[i][j] = min({dp[i][j-1], dp[i-1][j], dp[i-1][j-1]}) + 1;
        }
    }

    return dp[n][m];
}

// DAY 27 (427. Construct Quad Tree)===============================================================================

/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;
    
    Node() {
        val = false;
        isLeaf = false;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = NULL;
        topRight = NULL;
        bottomLeft = NULL;
        bottomRight = NULL;
    }
    
    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:

    Node* dfs(int rowSt, int colSt, int rowEnd, int colEnd, int x, vector<vector<int>> &grid)
    {
        if(x == 1)
            return new Node(grid[rowSt][colSt], true);
        
        int rowMid = (rowSt + rowEnd) / 2;
        int colMid = (colSt + colEnd) / 2;
        Node* topLeft = dfs(rowSt, colSt, rowMid, colMid, x/2, grid);
        Node* topRight = dfs(rowSt, colMid, rowMid, colEnd, x/2, grid);
        Node* bottomLeft = dfs(rowMid, colSt, rowEnd, colMid, x/2, grid);
        Node* bottomRight = dfs(rowMid, colMid, rowEnd, colEnd, x/2, grid);

        int tlVal = topLeft->isLeaf? topLeft->val : 2;
        int trVal = topRight->isLeaf? topRight->val : 3;
        int blVal = bottomLeft->isLeaf? bottomLeft->val : 4;
        int brVal = bottomRight->isLeaf? bottomRight->val : 5;

        if(tlVal == trVal && tlVal == blVal && tlVal == brVal)
            return new Node(tlVal, true);
        return new Node(0, false, topLeft, topRight, bottomLeft, bottomRight);
    }

    Node* construct(vector<vector<int>>& grid) 
    {
        return dfs(0, 0, grid.size(), grid.size(), grid.size(), grid);
    }
};

// DAY 28 (652. Find Duplicate Subtrees)===================================================================================

vector<TreeNode*> ans;
unordered_map<string, int> vis;
string dfs(TreeNode* node)
{
    if(!node) return "";

    string curr = "";
    curr += "(" + dfs(node->left) + to_string(node->val) + dfs(node->right) + ")";

    if(vis[curr]++ == 1)
        ans.push_back(node);

    return curr;
}

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) 
{
    dfs(root);
    return ans;
}
