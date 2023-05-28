// DAY 1 (1491. Average Salary Excluding the Minimum and Maximum Salary)===================================================================

double average(vector<int>& salary) 
{
    int minSalary = INT_MAX, maxSalary = INT_MIN, sumSalary = 0;
    for(int x : salary)
    {
        minSalary = min(minSalary, x);
        maxSalary = max(maxSalary, x);
        sumSalary += x;
    }
    sumSalary -= (minSalary + maxSalary);

    return 1.0*sumSalary / (salary.size()-2);
}

// DAY 2 (1822. Sign of the Product of an Array)==========================================================================================

int arraySign(vector<int>& nums) 
{
    int ans = 1;
    for(int x : nums)
        ans *= (x == 0)? 0 : (x > 0? 1 : -1);

    return ans;
}

// DAY 3 (2215. Find the Difference of Two Arrays)==================================================================================

vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) 
{
    int n = nums1.size(), m = nums2.size();

    unordered_set<int> st1, st2;
    for(int x : nums1)
        st1.insert(x);
    for(int x : nums2)
        st2.insert(x);

    vector<vector<int>> answer(2);
    for(int x : st1)
        if(!st2.count(x))
            answer[0].push_back(x);
    for(int x : st2)
        if(!st1.count(x))
            answer[1].push_back(x);

    return answer;
}

// DAY 4 (649. Dota2 Senate)========================================================================================================

string predictPartyVictory(string senate) 
{
    int n = senate.size();
    queue<int> q1, q2;
    for(int i = 0; i < n; i++)
        senate[i] == 'R'? q1.push(i) : q2.push(i);

    while(!q1.empty() && !q2.empty())
    {
        int i = q1.front();
        int j = q2.front();
        q1.pop();
        q2.pop();

        i < j? q1.push(i + n) : q2.push(j + n);
    }

    return q1.size() > q2.size()? "Radiant" : "Dire";
}

// DAY 5 (1456. Maximum Number of Vowels in a Substring of Given Length)=====================================================================

bool isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int maxVowels(string s, int k) 
{
    int ans = 0;
    unordered_map<char,int> cnt;
    for(int i = 0; i < s.size(); i++)
    {
        if(isVowel(s[i]))
            cnt[s[i]]++;
        if(i >= k && isVowel(s[i-k]))
            cnt[s[i-k]]--;
        ans = max({ans, cnt['a'] + cnt['e'] + cnt['i'] + cnt['o'] + cnt['u']});
    }
    return ans;
}

// DAY 6 (1498. Number of Subsequences That Satisfy the Given Sum Condition)=========================================================================

int mod = 1e9 + 7;

int binpowmod(int a, int b)
{
    long ans = 1;
    while(b)
    {
        if(b & 1)
            ans = (ans % mod * a % mod) % mod;
        a = ((long)a % mod * a % mod) % mod;
        b >>= 1;
    }

    return ans % mod;
}

int numSubseq(vector<int>& nums, int target) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int j = upper_bound(nums.begin() + i, nums.end(), target - nums[i]) - nums.begin();
        if(i == j) continue;
        int x = binpowmod(2, j - i - 1);
        ans = (ans % mod + x % mod) % mod;
    }

    return ans;
}

// DAY 8 (1572. Matrix Diagonal Sum)======================================================================================

int diagonalSum(vector<vector<int>>& mat) 
{
    int n = mat.size();
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += mat[i][i] + mat[i][n-i-1];
    return sum - ((n&1)? mat[n/2][n/2] : 0);
}

// DAY 9 (54. Spiral Matrix)============================================================================================

vector<int> spiralOrder(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    vector<int> ans(n*m);
    int x = 1, sr = 0, sc = 0, er = n-1, ec = m-1, k = 0;

    while(x <= n*m)
    {
        for(int c = sc; c <= ec && x <= n*m; c++, x++)
            ans[k++] = matrix[sr][c];
        sr++;
        for(int r = sr; r <= er && x <= n*m; r++, x++)
            ans[k++] = matrix[r][ec];
        ec--;
        for(int c = ec; c >= sc && x <= n*m; c--, x++)
            ans[k++] = matrix[er][c];
        er--;
        for(int r = er; r >= sr && x <= n*m; r--, x++)
            ans[k++] = matrix[r][sc];
        sc++;
    }

    return ans;
}

// DAY 10 (59. Spiral Matrix II)==========================================================================================

vector<vector<int>> generateMatrix(int n) 
{
    vector<vector<int>> ans(n, vector<int> (n));
    int x = 1, sr = 0, sc = 0, er = n-1, ec = n-1;

    while(x <= n*n)
    {
        for(int c = sc; c <= ec && x <= n*n; c++)
            ans[sr][c] = x++;
        sr++;
        for(int r = sr; r <= er && x <= n*n; r++)
            ans[r][ec] = x++;
        ec--;
        for(int c = ec; c >= sc && x <= n*n; c--)
            ans[er][c] = x++;
        er--;
        for(int r = er; r >= sr && x <= n*n; r--)
            ans[r][sc] = x++;
        sc++;
    }

    return ans;
}

// DAY 11 (1035. Uncrossed Lines)=================================================================================================

int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) 
{
    int n = nums1.size(), m = nums2.size();

    vector<vector<int>> dp(n, vector<int> (m, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int x = i? dp[i-1][j] : 0;
            int y = j? dp[i][j-1] : 0;
            int z = nums1[i] == nums2[j]? ((i && j)? dp[i-1][j-1] + 1 : 1) : 0;

            dp[i][j] = max({x, y, z});
        }
    }

    return dp[n-1][m-1];
}

// DAY 12 (2140. Solving Questions With Brainpower)====================================================================================

#define ll long long
long long mostPoints(vector<vector<int>>& questions) 
{
    int n = questions.size();
    vector<ll> dp(n+1, 0);
    for(int i = n-1; i >= 0; i--)
    {
        ll inc = i+questions[i][1]+1 < n? dp[i+questions[i][1]+1] : 0;
        dp[i] = max(dp[i+1], inc + questions[i][0]);
    }

    return dp[0];
}

// DAY 13 (2466. Count Ways To Build Good Strings)=========================================================================================

int mod = 1e9 + 7;
int countGoodStrings(int low, int high, int zero, int one) 
{
    vector<int> dp(high+1, 0);
    dp[0] = 1;
    for(int len = min(zero, one); len <= high; len++)
    {
        if(len >= zero)
            dp[len] = (dp[len] % mod + dp[len-zero] % mod) % mod;
        if(len >= one)
            dp[len] = (dp[len] % mod + dp[len-one] % mod) % mod;
    }

    int ans = 0;
    for(int len = low; len <= high; len++)
        ans = (ans % mod + dp[len] % mod) % mod;

    return ans;
}

// DAY 14 (1799. Maximize Score After N Operations)====================================================================================

int gcd(int x, int y)
{
    return y % x == 0? x : gcd(y % x, x);
}

int dfs(int i, int x, int mask, vector<vector<int>> &pairs, vector<int> &dp)
{
    if(i == pairs.size())
        return 0;
    if(dp[mask] != -1) 
        return dp[mask];

    int inc = 0;
    if(!(mask & ((1 << pairs[i][1]) | (1 << pairs[i][2]))))
    {
        mask ^= (1 << pairs[i][1]) | (1 << pairs[i][2]);
        inc = dfs(0, x+1, mask, pairs, dp) + (pairs[i][0] * x);
        mask ^= (1 << pairs[i][1]) | (1 << pairs[i][2]);
    }

    int exc = dfs(i+1, x, mask, pairs, dp);

    return dp[mask] = max(inc, exc);
}

int maxScore(vector<int>& nums) 
{
    int n = nums.size();
    vector<vector<int>> pairs;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            pairs.push_back({gcd(nums[i], nums[j]), i, j});

    int mask = 0;
    vector<int> dp(1 << 14, -1);
    return dfs(0, 1, mask, pairs, dp);
}

// DAY 15 (1721. Swapping Nodes in a Linked List)================================================================================

ListNode* swapNodes(ListNode* head, int k) 
{
    int n = 0;
    ListNode* tmp = head;
    while(tmp)
    {
        tmp = tmp->next;
        n++;
    }

    int kk = n-k+1;
    if(k == kk) return head;
    if(kk < k) swap(k, kk);

    ListNode *prev1 = nullptr, *prev2 = nullptr;
    ListNode *node1 = head, *node2 = head;

    while(--kk)
    {
        if(--k > 0)
        {
            prev1 = node1;
            node1 = node1->next;
        }
        prev2 = node2;
        node2 = node2->next;
    }

    ListNode* tmpNxt = node1->next;
    if(prev1) prev1->next = node2;
    node1->next = node2->next;

    if(tmpNxt != node2)
    {
        prev2->next = node1;
        node2->next = tmpNxt;
    }
    else node2->next = node1;

    return head == node1? node2 : head;
}

// DAY 16 (24. Swap Nodes in Pairs)===============================================================================

ListNode* swapPairs(ListNode* head) 
{
    ListNode *prev = nullptr, *curr = head;
    while(curr && curr->next)
    {
        ListNode *nxt = curr->next->next;

        if(prev) prev->next = curr->next;
        else head = curr->next;
        curr->next->next = curr;
        curr->next = nxt;

        prev = curr;
        curr = curr->next;
    }

    return head;
}

// DAY 17 (2130. Maximum Twin Sum of a Linked List)======================================================================

ListNode* findMid(ListNode *head)
{
    ListNode *fast = head, *slow = head;
    while(fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

ListNode* reverse(ListNode* head)
{
    ListNode *curr = head, *prev = nullptr, *forw = head;
    while(curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    return prev;
}

int pairSum(ListNode* head) 
{
    ListNode *mid = findMid(head);
    ListNode *midNxt = mid->next;
    mid->next = nullptr;

    ListNode *head2 = reverse(midNxt);

    int maxSum = 0;
    while(head)
    {
        maxSum = max(maxSum, head->val + head2->val);
        head = head->next;
        head2 = head2->next;
    }

    return maxSum;
}

// DAY 18 (1557. Minimum Number of Vertices to Reach All Nodes)=========================================================================

vector<int> findSmallestSetOfVertices(int n, vector<vector<int>>& edges) 
{
    vector<int> inDeg(n,0);
    for(vector<int> &e : edges)
        inDeg[e[1]]++;

    vector<int> ans;
    for(int i = 0; i < n; i++)
        if(inDeg[i] == 0)
            ans.push_back(i);

    return ans;
}

// DAY 19 (785. Is Graph Bipartite?)========================================================================================

bool dfs(int u, int parColor, vector<int> &color, vector<vector<int>> &gp)
{
    if(color[u] == -1) 
        color[u] = parColor ^ 1;
    else if(color[u] == parColor)
        return false;
    else return true;

    for(int v : gp[u])
        if(!dfs(v, color[u], color, gp))
            return false;
    return true;
}

bool isBipartite(vector<vector<int>>& graph) 
{
    int n = graph.size();
    vector<int> color(n, -1);

    for(int i = 0; i < n; i++)
        if(color[i] == -1)
            if(!dfs(i, 0, color, graph))
                return false;
    return true;
}

// DAY 20 (399. Evaluate Division)======================================================================================

double getDivision_dfs(string num, string den, unordered_map<string, bool> &vis, unordered_map<string,vector<pair<string,double>>> &gp)
{
    if(num == den) return 1.0;

    vis[num] = 1;
    for(auto p : gp[num])
    {
        if(vis[p.first]) continue;
        double ret = getDivision_dfs(p.first, den, vis, gp);
        if(ret > 0)
            return ret * p.second;
    }
    return -1.0;
}

vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) 
{
    unordered_map<string,vector<pair<string,double>>> gp;
    for(int i = 0; i < equations.size(); i++)
    {
        string num = equations[i][0], den = equations[i][1];
        gp[num].push_back({den, values[i]});
        gp[den].push_back({num, 1.0/values[i]});
    }

    vector<double> ans(queries.size(), -1.0);
    for(int i = 0; i < queries.size(); i++)
    {
        string num = queries[i][0], den = queries[i][1];
        unordered_map<string, bool> vis;
        if(gp.count(num) && gp.count(den))
            ans[i] = getDivision_dfs(num, den, vis, gp);
    }

    return ans;
}

// DAY 21 (934. Shortest Bridge)=============================================================================

void addFirstIsland(int i, int j, int n, int m, vector<vector<int>> &grid, queue<pair<int,int>> &que)
{        
    grid[i][j] = -1;
    int surroundedLand = 0;

    if(i+1 < n)
    {
        if(grid[i+1][j] != 0)
        {
            surroundedLand++;
            if(grid[i+1][j] == 1)
                addFirstIsland(i+1, j, n, m, grid, que);
        }
    }
    if(j+1 < m)
    {
        if(grid[i][j+1] != 0)
        {
            surroundedLand++;
            if(grid[i][j+1] == 1)
                addFirstIsland(i, j+1, n, m, grid, que);
        }
    }
    if(i-1 >= 0)
    {
        if(grid[i-1][j] != 0)
        {
            surroundedLand++;
            if(grid[i-1][j] == 1)
                addFirstIsland(i-1, j, n, m, grid, que);
        }
    }
    if(j-1 >= 0)
    {
        if(grid[i][j-1] != 0)
        {
            surroundedLand++;
            if(grid[i][j-1] == 1)
                addFirstIsland(i, j-1, n, m, grid, que);
        }
    }

    if(surroundedLand != 4)
        que.push({i, j});
}

int shortestBridge(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    queue<pair<int,int>> que;
    for(int i = 0; i < n; i++)
    {
        bool foundIsland = false;
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 1)
            {
                addFirstIsland(i, j, n, m, grid, que);
                foundIsland = true;
                break;
            }
        }
        if(foundIsland) break;
    }

    int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
    int dist = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int i = que.front().first;
            int j = que.front().second;
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                int r = i + dir[d][0];
                int c = j + dir[d][1];

                if(r == -1 || c == -1 || r == n || c == m || grid[r][c] == -1)
                    continue;
                if(grid[r][c] == 1) return dist;

                que.push({r, c});
                grid[r][c] = -1;
            }
        }
        dist++;
    }
    return dist - 2;
}

// DAY 22 (347. Top K Frequent Elements)==========================================================================

vector<int> topKFrequent(vector<int>& nums, int k) 
{
    unordered_map<int,int> cnt;
    for(int x : nums)
        cnt[x]++;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(auto p : cnt)
    {
        pq.push({p.second, p.first});
        if(pq.size() > k) pq.pop();
    }

    vector<int> ans;
    while(k--)
    {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

// DAY 23 703. Kth Largest Element in a Stream)============================================================================================

class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
    KthLargest(int k, vector<int>& nums) 
    {
        this->k = k;
        for(int x : nums)
        {
            pq.push(x);
            if(pq.size() > k)
                pq.pop();
        }
    }
    
    int add(int val) 
    {
        pq.push(val);
        if(pq.size() > k)
            pq.pop();
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

// DAY 24 (2542. Maximum Subsequence Score)==========================================================================

#define ll long long
#define f first
#define s second

long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) 
{
    int n = nums1.size();
    vector<pair<int,int>> numsComb(n);
    for(int i = 0; i < n; i++)
        numsComb[i] = {nums2[i], nums1[i]};
    sort(numsComb.begin(), numsComb.end());

    ll maxAns = -1, sum = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int i = n-1; i >= 0; i--)
    {
        sum += numsComb[i].s;
        pq.push(numsComb[i].s);
        if(pq.size() > k)
        {
            sum -= pq.top();
            pq.pop();
        }
        if(pq.size() == k)
            maxAns = max(maxAns, sum * numsComb[i].f);
    }

    return maxAns;
}

// DAY 25 (837. New 21 Game)===============================================================================================

double new21Game(int n, int k, int maxPts) 
{
    if(k == 0 || n >= k + maxPts)
        return 1.0;

    vector<double> dp(n+1, 0.0);
    dp[0] = 1.0;
    double runningSum = dp[0];
    for(int i = 1; i <= n; i++)
    {
        dp[i] = 1.0 * runningSum/maxPts;

        if(i < k)
            runningSum += dp[i];
        if(i >= maxPts)
            runningSum -= dp[i-maxPts];
    }

    double ans = 0.0;
    for(int i = k; i <= n; i++)
        ans += dp[i];

    return ans;
}

// DAY 26 (1140. Stone Game II)=========================================================================

int dfs(int i, bool isAlice, int m, vector<int> &piles, vector<vector<vector<int>>> &dp)
{
    if(i == piles.size()) 
        return 0;
    if(dp[i][m][isAlice] != -1)
        return dp[i][m][isAlice];

    int ans = isAlice? 0 : 1e7;
    int stones = 0;
    for(int x = 1; x <= min(2*m, (int)piles.size()-i); x++)
    {
        stones += piles[i+x-1];
        if(isAlice)
            ans = max(ans, dfs(i+x, false, max(m, x), piles, dp) + stones);
        else
            ans = min(ans, dfs(i+x, true, max(m, x), piles, dp));
    }
    return dp[i][m][isAlice] = ans;
}

int stoneGameII(vector<int>& piles) 
{
    int n = piles.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n+1, vector<int> (2, -1)));
    return dfs(0, true, 1, piles, dp);
}

// DAY 27 (1406. Stone Game III)====================================================================================

// APPROACH 1 (Using 2D DP)

int dfs(int i, int n, bool isAlice, vector<int> &stones, vector<vector<int>> &dp)
{
    if(i >= n) return 0;
    if(dp[i][isAlice] != -1) return dp[i][isAlice];

    int oneStone = dfs(i+1, n, !isAlice, stones, dp);
    int twoStones = dfs(i+2, n, !isAlice, stones, dp);
    int threeStones = dfs(i+3, n, !isAlice, stones, dp);
    int tillFirst = stones[i];
    int tillSecond = (i+1 < n? stones[i+1] : 0) + tillFirst;
    int tillThird = (i+2 < n? stones[i+2] : 0) + tillSecond;

    return dp[i][isAlice] = isAlice? 
        max({oneStone + tillFirst, twoStones + tillSecond, threeStones + tillThird})
        : min({oneStone, twoStones, threeStones});
}

string stoneGameIII(vector<int>& stoneValue) 
{
    int n = stoneValue.size();
    int totSum = 0;
    for(int val : stoneValue)
        totSum += val;

    vector<vector<int>> dp(n, vector<int> (2, -1));
    int maxAlice = dfs(0, n, true, stoneValue, dp);
    int maxBob = totSum - maxAlice;

    return maxAlice > maxBob? "Alice" : (maxBob > maxAlice? "Bob" : "Tie");
}

// APPROACH 2 (Using 1D DP)

int dfs(int i, int n, vector<int> &stones, vector<int> &dp)
{
    if(i >= n) return 0;
    if(dp[i] != -1) return dp[i];

    int oneStone = dfs(i+1, n, stones, dp);
    int twoStones = dfs(i+2, n, stones, dp);
    int threeStones = dfs(i+3, n, stones, dp);

    int tillFirst = stones[i];
    int tillSecond = (i+1 < n? stones[i+1] : 0) + tillFirst;
    int tillThird = (i+2 < n? stones[i+2] : 0) + tillSecond;

    return dp[i] = max({tillFirst - oneStone, tillSecond - twoStones, tillThird - threeStones});
}

string stoneGameIII(vector<int>& stoneValue) 
{
    int n = stoneValue.size();
    vector<int> dp(n, -1);

    int ans = dfs(0, n, stoneValue, dp);

    return ans > 0? "Alice" : ans < 0? "Bob" : "Tie";
}

// METHOD 2 (Tabulated)

string stoneGameIII(vector<int>& stoneValue) 
{
    int n = stoneValue.size();
    vector<int> dp(n+1, 0);
    for(int i = n-1; i >= 0; i--)
    {
        dp[i] = stoneValue[i] - dp[i+1];
        if(i+2 <= n)
            dp[i] = max(dp[i], stoneValue[i] + stoneValue[i+1] - dp[i+2]);
        if(i+3 <= n)
            dp[i] = max(dp[i], stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - dp[i+3]);
    }

    return dp[0] > 0? "Alice" : dp[0] < 0? "Bob" : "Tie";
}

// METHOD 3 (OPTIMIZED Tabulation )

string stoneGameIII(vector<int>& stoneValue) 
{
    int n = stoneValue.size();
    vector<int> dp(3, 0);
    for(int i = n-1; i >= 0; i--)
    {
        int curr = stoneValue[i] - dp[(i+1) % 3];
        if(i+2 <= n)
            curr = max(curr, stoneValue[i] + stoneValue[i+1] - dp[(i+2) % 3]);
        if(i+3 <= n)
            curr = max(curr, stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - dp[(i+3) % 3]);

        dp[i % 3] = curr;
    }

    return dp[0] > 0? "Alice" : dp[0] < 0? "Bob" : "Tie";
}

// DAY 28 (1547. Minimum Cost to Cut a Stick)==================================================================

// METHOD 1 (Memoized) [TLE]

int minCostCuts(int left, int right, vector<int> &cuts, vector<vector<int>> &dp)
{
    if(left+1 == right) return 0;
    if(dp[left][right] != -1) 
        dp[left][right];

    int ans = INT_MAX;
    for(int x = left+1; x < right; x++)
    {
        ans = min(ans, 
                minCostCuts(left, x, cuts, dp) + 
                minCostCuts(x, right, cuts, dp));
    }
    return dp[left][right] = ans + (cuts[right] - cuts[left]);
}

int minCost(int n, vector<int>& cuts) 
{
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    vector<vector<int>> dp(n+1, vector<int> (n+1, -1));
    return minCostCuts(0, cuts.size()-1, cuts, dp);
}

// METHOD 2 (Tabulated)

int minCostCuts(int m, vector<int> &cuts, vector<vector<int>> &dp)
{
    for(int len = 1; len <= m; len++)
    {
        for(int left = 0, right = len; right < m; left++, right++)
        {
            if(len == 1)
                dp[left][right] = 0;
            else
            {
                int minCost = INT_MAX;
                for(int x = left+1; x < right; x++)
                    minCost = min(minCost, dp[left][x] + dp[x][right]);
                dp[left][right] = minCost + (cuts[right] - cuts[left]);
            }
        }
    }

    return dp[0][m-1];
}

int minCost(int n, vector<int>& cuts) 
{
    sort(cuts.begin(), cuts.end());
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);
    int m = cuts.size();
    vector<vector<int>> dp(m+1, vector<int> (m+1, 0));
    return minCostCuts(m, cuts, dp);
}
