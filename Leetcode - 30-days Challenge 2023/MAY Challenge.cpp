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
