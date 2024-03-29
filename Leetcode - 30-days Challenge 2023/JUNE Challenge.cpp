
// DAY 1 (1091. Shortest Path in Binary Matrix)=================================================================

int shortestPathBinaryMatrix(vector<vector<int>>& grid) 
{
  int n = grid.size(), m = grid[0].size();
  if(grid[0][0]) 
      return -1;
  if(n == 1 && m == 1)
      return 1;
  queue<pair<int,int>> que;
  que.push({0, 0});
  int dir[8][2] = {{1,0},{0,1},{-1,0},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};
  int len = 1;
  while(!que.empty())
  {
      int sz = que.size();
      while(sz--)
      {
          int i = que.front().first;
          int j = que.front().second;
          que.pop();

          for(auto [x, y] : dir)
          {
              int r = i + x, c = y + j;
              if(r == -1 || c == -1 || r == n || c == m || grid[r][c])
                  continue;
              if(r == n-1 && c == m-1)
                  return len+1;
              grid[r][c] = 1;
              que.push({r, c});
          }
      }
      len++;
  }

  return -1;
}

// DAY 2 (2101. Detonate the Maximum Bombs)=========================================================================================================

long euclidianDistance(vector<int> &bomb1, vector<int> &bomb2)
{
    long x1 = bomb1[0], y1 = bomb1[1];
    long x2 = bomb2[0], y2 = bomb2[1];

    long euclidianDist = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);

    return euclidianDist;
}

void dfs(int u, vector<vector<int>> &gp, unordered_set<int> &vis)
{
    vis.insert(u);
    for(int v : gp[u])
        if(!vis.count(v))
            dfs(v, gp, vis);
}

int maximumDetonation(vector<vector<int>>& bombs)
{
    int n = bombs.size();
    vector<vector<int>> gp(n);
    for(int i = 0; i < n; i++)
    {
        for(int j = i+1; j < n; j++)
        {
            long euclidianDist = euclidianDistance(bombs[i], bombs[j]);
            long r1square = (long)bombs[i][2]*bombs[i][2], 
                r2square = (long)bombs[j][2]*bombs[j][2];
            if(euclidianDist <= r1square)
                gp[i].push_back(j);
            if(euclidianDist <= r2square)
                gp[j].push_back(i);
        }
    }

    int maxBombs = 0;
    for(int i = 0; i < n; i++)
    {
        unordered_set<int> vis;
        dfs(i, gp, vis);
        maxBombs = max(maxBombs, (int)vis.size());
    }

    return maxBombs;
}

// DAY 3 (1376. Time Needed to Inform All Employees)===================================================================================

int totTime_dfs(int u, vector<int> &manager, vector<int> &informTime)
{
    if(manager[u] == -1)
        return informTime[u];

    informTime[u] += totTime_dfs(manager[u], manager, informTime);
    manager[u] = -1;

    return informTime[u];
}

int numOfMinutes(int n, int headID, vector<int>& manager, vector<int>& informTime) 
{
    int time = 0;
    for(int u = 0; u < n; u++)
        time = max(time, totTime_dfs(u, manager, informTime));
    return time;
}

// DAY 4 (547. Number of Provinces)============================================================================

class DSU
{
    public:
    int n;
    vector<int> par;
    DSU(int n)
    {
        this->n = n;
        this->par.resize(n);
        for(int i = 0; i < n; i++)
            par[i] = i;
    }

    int findPar(int u)
    {
        return par[u] = par[u] == u? u : findPar(par[u]);
    }
    void merge(int u, int v)
    {
        int pu = findPar(u), pv = findPar(v);
        if(pu == pv) return;
        par[pv] = pu;
    }
};

int findCircleNum(vector<vector<int>>& isConnected) 
{
    int n = isConnected.size();
    DSU dsu(n);
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(isConnected[i][j])
                dsu.merge(i, j);

    unordered_set<int> pars;
    for(int u = 0; u < n; u++)
        pars.insert(dsu.findPar(u));

    return pars.size();
}

// DAY 5 (1232. Check If It Is a Straight Line)=======================================================================

double getSlope(vector<int> &coordinate1, vector<int> &coordinate2)
{
    int x1 = coordinate1[0], y1 = coordinate1[1];
    int x2 = coordinate2[0], y2 = coordinate2[1];
    return x1 == x2? INT_MAX : (1.0 * (y2 - y1) / (x2 - x1));
}

bool checkStraightLine(vector<vector<int>>& coordinates) 
{
    double slope = getSlope(coordinates[0], coordinates[1]);
    for(int i = 1; i+1 < coordinates.size(); i++)
        if(getSlope(coordinates[i], coordinates[i+1]) != slope)
            return false;
    return true;
}

// DAY 6 (1502. Can Make Arithmetic Progression From Sequence)============================================================

bool canMakeArithmeticProgression(vector<int>& arr) 
{
    sort(arr.begin(), arr.end());
    int d = arr[1] - arr[0];
    for(int i = 1; i+1 < arr.size(); i++)
        if(arr[i+1] - arr[i] != d)
            return false;
    return true;
}

// DAY 7 (1318. Minimum Flips to Make a OR b Equal to c)==================================================================

int minFlips(int a, int b, int c) 
{
    int flips = 0;
    while(a || b || c)
    {
        if(c & 1)
            flips += ((a & 1 ^ 1) && (b & 1 ^ 1))? 1 : 0;
        else 
            flips += (a & 1) + (b & 1);

        a >>= 1;
        b >>= 1;
        c >>= 1;
    }

    return flips;
}

// DAY 8 (1351. Count Negative Numbers in a Sorted Matrix)================================================================

int countNegatives(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    int stRow = 0, stCol = m-1, endRow = n, endCol = m;

    int negs = 0;
    while(stRow < endRow && stCol >= 0)
    {
        if(grid[stRow][stCol] >= 0)
            stRow++;
        else 
        {
            negs += (endRow - stRow) * (endCol - stCol);
            endCol = stCol--;
        }
    }

    return negs;
}

// DAY 9 (744. Find Smallest Letter Greater Than Target)========================================================


char nextGreatestLetter(vector<char>& letters, char target)
{
    int n = letters.size();
    int lo = 0, hi = n;
    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(letters[mid] <= target)
            lo = mid + 1;
        else hi = mid;
    }

    return letters[lo == n? 0 : lo];
}

// DAY 10 (1802. Maximum Value at a Given Index in a Bounded Array)==========================================================================

bool checkMid(int x, int n, int index, int maxSum)
{
    long sum = 0;
    if(x <= index)
        sum += 1l * x * (x+1) / 2 + (index - x + 1);
    else sum += 1l * (x - index + x) * (index + 1) / 2;

    long psum = sum;

    if(x <= n - index - 1)
        sum += 1l * (x - 1) * x / 2 + ((n - index - 1) - (x - 1));
    else sum += 1l * ((x - 1) + (x - (n - index - 1))) * (n - index - 1) / 2;

    return sum <= maxSum;
}


int maxValue(int n, int index, int maxSum) 
{
    int lo = 1, hi = maxSum, ans = -1;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(checkMid(mid, n, index, maxSum))
        {
            ans = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }

    return ans;
}

// DAY 11 (1146. Snapshot Array)====================================================================================

class SnapshotArray {
public:

    int n, snap_id;
    vector<vector<vector<int>>> snapIds_vs_val;
    SnapshotArray(int length) 
    {
        this->n = length;
        this->snapIds_vs_val.resize(n);
        this->snap_id = 0;
        for(int i = 0; i < n; i++)
            snapIds_vs_val[i].push_back({0, 0}); // {snap_id, val}
    }
    
    void set(int index, int val) 
    {
        if(snapIds_vs_val[index].back()[0] == snap_id)
            snapIds_vs_val[index].back()[1] = val;
        else snapIds_vs_val[index].push_back({snap_id, val});
    }
    
    int snap() 
    {
        return snap_id++;
    }
    
    int get(int index, int snap_id) 
    {
        int lo = 0, hi = snapIds_vs_val[index].size();
        while(lo < hi)
        {
            int mid = lo + ((hi - lo) >> 1);
            if(snapIds_vs_val[index][mid][0] <= snap_id)
                lo = mid + 1;
            else hi = mid;
        }
        return snapIds_vs_val[index][--lo][1];
    }
};

/**
 * Your SnapshotArray object will be instantiated and called as such:
 * SnapshotArray* obj = new SnapshotArray(length);
 * obj->set(index,val);
 * int param_2 = obj->snap();
 * int param_3 = obj->get(index,snap_id);
 */

// DAY 12 (228. Summary Ranges)====================================================================================================

vector<string> summaryRanges(vector<int>& nums) 
{
    int n = nums.size();
    vector<string> ans;
    for(int i = 0; i < n; )
    {
        int st = nums[i];
        int j = i+1;
        while(j < n && nums[j] == nums[j-1] + 1)
            j++;

        if(j == i+1) ans.push_back(to_string(st));
        else ans.push_back(to_string(st) + "->" + to_string(nums[j-1]));
        i = j;
    }

    return ans;
}

// DAY 13 (2352. Equal Row and Column Pairs)=====================================================

int equalPairs(vector<vector<int>>& grid) 
{
    int n = grid.size(), ans = 0;
    map<vector<int>, int> mp;
    for(int i = 0; i < n; i++)
        mp[grid[i]]++;
    for(int i = 0; i < n; i++)
    {
        vector<int> col(n);
        for(int j = 0; j < n; j++)
            col[j] = grid[j][i];
        ans += mp[col];
    }

    return ans;
}

// DAY 14 (530. Minimum Absolute Difference in BST)=======================================================================

int getMinimumDifference(TreeNode* root) 
{
    int prevVal = -1e6, minDiff = 1e6;
    while(root)
    {
        if(!root->left)
        {
            minDiff = min(minDiff, root->val - prevVal);
            prevVal = root->val;
            root = root->right;
        }
        else 
        {
            TreeNode* left = root->left;
            while(left->right && left->right != root)
                left = left->right;
            if(!left->right)
            {
                left->right = root;
                root = root->left;
            }
            else 
            {
                minDiff = min(minDiff, root->val - prevVal);
                prevVal = root->val;
                root = root->right;
                left->right = nullptr;
            }
        }
    }

    return minDiff;
}

// DAY 15 (1161. Maximum Level Sum of a Binary Tree)============================================================================

int maxLevelSum(TreeNode* root) 
{
    int maxSum = INT_MIN, minLvl = INT_MAX, lvl = 1;
    queue<TreeNode*> que;
    que.push(root);
    while(!que.empty())
    {
        int sz = que.size();
        int currSum = 0;
        while(sz--)
        {
            TreeNode* node = que.front();
            que.pop();

            currSum += node->val;

            if(node->left)
                que.push(node->left);
            if(node->right)
                que.push(node->right);
        }
        if(currSum > maxSum)
        {
            maxSum = currSum;
            minLvl = lvl;
        }
        lvl++;
    }

    return minLvl;
}

// DAY 16 (1569. Number of Ways to Reorder Array to Get Same BST)===========================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

#define ll long long
const int MOD = 1e9 + 7;

void fill_nCr_table(int N, vector<vector<int>> &nCr)
{
    for(int n = 0; n <= N; n++)
    {
        nCr[n].assign(n+1, 1);
        for(int r = 1; r < n; r++)
            nCr[n][r] = (nCr[n-1][r] % MOD + nCr[n-1][r-1] % MOD) % MOD;
    }
}

int countNumOfWays_DFS(vector<int> &nodes, vector<vector<int>> &nCr)
{
    if(nodes.empty()) return 1;

    int root = nodes[0];
    int leftCount = 0, rightCount = 0;
    vector<int> leftTree, rightTree;
    for(int node : nodes)
    {
        if(node < root)
            leftTree.push_back(node);
        else if(node > root)
            rightTree.push_back(node);
    }
    leftCount = leftTree.size();
    rightCount = rightTree.size();
    
    ll leftWays = countNumOfWays_DFS(leftTree, nCr);
    ll rightWays = countNumOfWays_DFS(rightTree, nCr);
    ll subTreeWays = (leftWays % MOD * rightWays % MOD) % MOD;

    ll currWays = nCr[nodes.size()-1][rightCount];
    currWays = (currWays % MOD * subTreeWays % MOD) % MOD;
    return currWays % MOD;
}

int numOfWays(vector<int> &nums)
{
    int n = nums.size();
    vector<vector<int>> nCr(n+1);
    fill_nCr_table(n, nCr);
    return countNumOfWays_DFS(nums, nCr) - 1;
}

// DAY 17 (1187. Make Array Strictly Increasing)============================================================================

int dfs(int i, int previ, int prev, int n, int m, vector<int> &a, vector<int> &b, vector<vector<int>> &dp)
{
    if(i == n) return 0;

    previ = upper_bound(b.begin() + previ, b.end(), prev) - b.begin();
    if(dp[i][previ] != -1) return dp[i][previ];
    if(previ == m && a[i] <= prev) return 1e5;

    int replace = 1e5, same = 1e5;

    if(previ != m)
        replace = dfs(i+1, previ+1, b[previ], n, m, a, b, dp) + 1;
    if(a[i] > prev)
        same = dfs(i+1, previ, a[i], n, m, a, b, dp);
    
    return dp[i][previ] = min(replace, same);
}

int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) 
{
    int n = arr1.size(), m = arr2.size();
    sort(arr2.begin(), arr2.end());
    vector<vector<int>> dp(n, vector<int>(m+1, -1));
    int ans = dfs(0, 0, -1, n, m, arr1, arr2, dp);
    return ans >= 1e5? -1 : ans;
}

// DAY 18 (2328. Number of Increasing Paths in a Grid)===================================================================

int mod = 1e9 + 7;
int ans = 0;
int dfs(int i, int j, int n, int m, int prev, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if(i == -1 || j == -1 || i == n || j == m || grid[i][j] <= prev)
        return 0;
    if(dp[i][j] != -1)
        return dp[i][j];
    
    prev = grid[i][j];
    int ip1 = dfs(i+1, j, n, m, prev, grid, dp);
    int jp1 = dfs(i, j+1, n, m, prev, grid, dp);
    int im1 = dfs(i-1, j, n, m, prev, grid, dp);
    int jm1 = dfs(i, j-1, n, m, prev, grid, dp);

    int curr = ((ip1 % mod + jp1 % mod) % mod + 
        (im1 % mod + jm1 % mod) % mod) % mod;

    return dp[i][j] = (curr + 1) % mod;
}

int countPaths(vector<vector<int>>& grid)
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> dp(n, vector<int> (m, -1));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(dp[i][j] == -1)
                dfs(i, j, n, m, -1, grid, dp);
            ans = (ans % mod + dp[i][j] % mod) % mod;
        }
    }

    return ans;
}

// DAY 19 (1732. Find the Highest Altitude)=====================================================================================

int largestAltitude(vector<int>& gain) 
{
    int h = 0, maxh = 0;
    for(int g : gain)
    {
        h += g;
        maxh = max(maxh, h);
    }

    return maxh;
}

// DAY 20 (2090. K Radius Subarray Averages)===================================================================================

vector<int> getAverages(vector<int>& nums, int k) 
{
    long sum = 0, n = nums.size();
    vector<int> ans(n, -1);
    for(int i = 0; i < n; i++)
    {
        sum += nums[i];
        if(i >= 2*k+1) sum -= nums[i - (2*k+1)];
        if(i >= 2*k)
            ans[i-k] = sum / (2*k+1);
    }
    return ans;
}

// DAY 21 (2448. Minimum Cost to Make Array Equal)=============================================================================

#define ll long long
long long minCost(vector<int>& nums, vector<int>& cost) 
{
    int n = nums.size();
    vector<vector<int>> numsCost(n, vector<int>(2));
    ll lSum = 0, rSum = 0, lCost = 0, rCost = 0;
    for(int i = 0; i < n; i++)
    {
        numsCost[i] = {nums[i], cost[i]};
        rSum += cost[i];
        rCost += (ll)nums[i] * cost[i];
    }
    sort(numsCost.begin(), numsCost.end());
    
    ll ans = LONG_LONG_MAX, prevDist = 0;
    for(int i = 0; i < n; i++)
    {
        int dist = numsCost[i][0] - prevDist;
        prevDist = numsCost[i][0];

        lCost += lSum * dist;
        rCost -= rSum * dist;

        lSum += numsCost[i][1];
        rSum -= numsCost[i][1];

        ans = min(ans, lCost + rCost);
    }

    return ans;
}

// DAY 22 (714. Best Time to Buy and Sell Stock with Transaction Fee)====================================================================

int maxProfit(vector<int>& prices, int fee) 
{
    int buyMax = INT_MIN, sellMax = 0;
    for(int x : prices)
    {
        int prevBuyMax = buyMax;
        buyMax = max(buyMax, sellMax - x - fee);
        sellMax = max(sellMax, prevBuyMax + x);
    }
    return sellMax;
}

// DAY 23 (1027. Longest Arithmetic Subsequence)=====================================================================================

int longestArithSeqLength(vector<int>& nums) 
{
    int n = nums.size();
    vector<unordered_map<int,int>> diffMax(n);
    int maxLen = 0;
    for(int i = 1; i < n; i++)
    {
        for(int j = 0; j < i; j++)
        {
            int diff = nums[i] - nums[j];
            int diff_i = diffMax[i][diff];
            int diff_j = diffMax[j][diff];
            int diffMaxVal = (diff_j? diff_j : 1) + 1;

            maxLen = max(maxLen, diffMaxVal);
            diffMax[i][diff] = diffMaxVal;
        }
    }

    return maxLen;
}

// DAY 24 (956. Tallest Billboard)=============================================================================

#define MAXDIFF 5000
int dfs(int i, int diff, vector<vector<int>> &dp, vector<int> &rods)
{
    if(i == rods.size()) return diff == 0? 0 : INT_MIN;

    if(dp[i][diff + MAXDIFF] != -1) return dp[i][diff + MAXDIFF];

    int roda = rods[i] + dfs(i+1, diff + rods[i], dp, rods);
    int rodb = rods[i] + dfs(i+1, diff - rods[i], dp, rods);
    int rodn = dfs(i+1, diff, dp, rods);

    return dp[i][diff + MAXDIFF] = max({roda, rodb, rodn});
}

int tallestBillboard(vector<int>& rods) 
{
    int n = rods.size();
    vector<vector<int>> dp(n, vector<int> (2*MAXDIFF, -1));
    return dfs(0, 0, dp, rods)/2;
}

// DAY 25 (1575. Count All Possible Routes)======================================================================

int mod = 1e9 + 7;
int dfs(int st, int end, int fuel, vector<int> &locations, vector<vector<int>> &dp)
{
    if(fuel < 0) 
        return 0;
    if(dp[st][fuel] != -1)
        return dp[st][fuel];
    int ans = st == end;

    for(int i = 0; i < locations.size(); i++)
    {
        if(i == st) continue;
        int useFuel = abs(locations[i] - locations[st]);
        ans = (ans % mod + dfs(i, end, fuel - useFuel, locations, dp) % mod) % mod;
    }

    return dp[st][fuel] = ans;
}

int countRoutes(vector<int>& locations, int start, int finish, int fuel) 
{
    int n = locations.size();
    vector<vector<int>> dp(n, vector<int> (fuel+1, -1));
    return dfs(start, finish, fuel, locations, dp);
}

// DAY 26 (2462. Total Cost to Hire K Workers)=====================================================================

#define ll long long
long long totalCost(vector<int>& costs, int k, int candidates) 
{
    int n = costs.size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for(int i = 0; i < candidates && i < n/2; i++)
    {
        pq.push({costs[i], i, 1});
        pq.push({costs[n-i-1], n-i-1, 2});
    }
    if(candidates > (n>>1) && (n & 1))
        pq.push({costs[n>>1], n>>1, 1});
    int part1 = candidates, part2 = n-candidates-1;

    ll ans = 0;
    while(k--)
    {
        int cost = pq.top()[0];
        int idx = pq.top()[1];
        int turn = pq.top()[2];
        pq.pop();

        ans += (ll)cost;
        if(part1 > part2) continue;
        if(turn == 1)
            pq.push({costs[part1], part1++, 1});
        else pq.push({costs[part2], part2--, 2});
    }

    return ans;
}

// DAY 27 (373. Find K Pairs with Smallest Sums)=================================================================================

#define f first
#define s second
vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) 
{
    int n = nums1.size();
    int m = nums2.size();
    
    vector<vector<int>> ans;
    priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
    pq.push({nums1[0] + nums2[0], {0, 0}});

    set<pair<int,int>> vis;

    while(!pq.empty() && k--)
    {
        int x = pq.top().f;
        int i = pq.top().s.f;
        int j = pq.top().s.s;
        pq.pop();
        ans.push_back({nums1[i], nums2[j]});

        if(i+1 < n && !vis.count({i+1, j}))
        {
            pq.push({nums1[i+1] + nums2[j], {i+1, j}});
            vis.insert({i+1, j});
        }
        if(j+1 < m && !vis.count({i, j+1}))
        {
            pq.push({nums1[i] + nums2[j+1], {i, j+1}});
            vis.insert({i, j+1});
        }
    }

    return ans;
}

// DAY 28 (1514. Path with Maximum Probability)==================================================================================

double ans = -1;

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) 
{
    vector<vector<pair<int,double>>> gp(n);
    for(int i = 0; i < edges.size(); i++)
    {
        int u = edges[i][0], v = edges[i][1];
        double prob = succProb[i];
        gp[u].push_back({v, prob});
        gp[v].push_back({u, prob});
    }

    priority_queue<pair<double,int>> pq;
    pq.push({1.0, start});
    vector<double> maxProb(n, 0.0);
    maxProb[start] = 1.0;

    while(!pq.empty())
    {
        double prob = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if(u == end) 
            return prob;

        for(pair<int,double> child : gp[u])
        {
            int childNode = child.first;
            double childProb = child.second;

            if(prob * childProb > maxProb[childNode])
            {
                maxProb[childNode] = prob * childProb;
                pq.push({maxProb[childNode], childNode});
            }
        }
    }

    return maxProb[end];
}

// DAY 29 (864. Shortest Path to Get All Keys)===================================================================================

int shortestPathAllKeys(vector<string>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    int sti = -1, stj = -1, totKeys = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == '@')
            {
                sti = i;
                stj = j;
            }
            if(grid[i][j] >= 'a' && grid[i][j] <= 'z')
                totKeys++;
        }
    }
    if(sti == -1) return -1;
    if(totKeys == 0) return 0;

    int allKeys = (1 << totKeys) - 1;
    queue<vector<int>> que;
    vector<vector<vector<bool>>> vis(n, vector<vector<bool>> (m, vector<bool> (allKeys+1, false)));
    int keysVisited = 0;
    que.push({sti, stj, 0});
    vis[sti][stj][0] = true;
    int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int lvl = 0;

    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int i = que.front()[0];
            int j = que.front()[1];
            int keysVis = que.front()[2];
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                int r = i + dir[d][0];
                int c = j + dir[d][1];
                int newKeysVis = keysVis;

                if(r == -1 || r == n || c == -1 || c == m || vis[r][c][keysVis] || grid[r][c] == '#')
                    continue;
                if(grid[r][c] >= 'A' && grid[r][c] <= 'Z' && (keysVis & (1 << (grid[r][c]-'A'))) == 0)
                    continue;
                if(grid[r][c] >= 'a' && grid[r][c] <= 'z')
                    newKeysVis |= (1 << (grid[r][c] - 'a'));
                
                if(newKeysVis == allKeys) return lvl + 1;

                vis[r][c][newKeysVis] = true;
                que.push({r, c, newKeysVis});
            }
        }
        lvl++;
    }

    return -1;
}

// DAY 30 (1970. Last Day Where You Can Still Cross)====================================================================

bool hasPath(int row, int col, vector<vector<int>> &grid)
{
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    queue<pair<int,int>> que;
    for(int i = 0; i < col; i++)
    {
        if(grid[0][i]) continue;
        que.push({0, i});
        grid[0][i] = 2;
    }
    while(!que.empty())
    {
        int i = que.front().first;
        int j = que.front().second;
        que.pop();

        if(i == row-1) return true;

        for(int d = 0; d < 4; d++)
        {
            int r = i + dir[d][0];
            int c = j + dir[d][1];

            if(r == -1 || c == -1 || r == row || c == col || grid[r][c])
                continue;
            if(r == row-1) return true;
            que.push({r, c});
            grid[r][c] = 2;
        }
    }

    return false;
}

int latestDayToCross(int row, int col, vector<vector<int>>& cells) 
{
    int lo = 0, hi = row * col - 1, ans = -1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        vector<vector<int>> grid(row, vector<int> (col, 0));
        for(int i = 0; i <= mid; i++)
            grid[cells[i][0]-1][cells[i][1]-1] = 1;
        bool poss = hasPath(row, col, grid);
        if(poss)
        {
            ans = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }

    return ans + 1;
}
