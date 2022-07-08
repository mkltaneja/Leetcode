//  DAY 1 (1710. Maximum Units on a Truck)========================================================================================================

int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) 
{
    sort(boxTypes.begin(), boxTypes.end(), [](auto const &a, auto const &b){
        return a[1] > b[1];
    });
    int ans = 0;
    for(vector<int> v : boxTypes)
    {
        ans += min(truckSize, v[0]) * v[1];
        truckSize -= min(truckSize, v[0]);
    }
    return ans;
}

//  DAY 2 (1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts)========================================================================================================

int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts)
{
    horizontalCuts.insert(horizontalCuts.begin(), 0);
    horizontalCuts.push_back(h);
    verticalCuts.insert(verticalCuts.begin(), 0);
    verticalCuts.push_back(w);
    sort(horizontalCuts.begin(), horizontalCuts.end());
    sort(verticalCuts.begin(), verticalCuts.end());
    int mxw = 0, mxh = 0;
    for(int i = 0; i < horizontalCuts.size()-1; i++)
        mxh = max(mxh, horizontalCuts[i+1] - horizontalCuts[i]);
    for(int i = 0; i < verticalCuts.size()-1; i++)
        mxw = max(mxw, verticalCuts[i+1] - verticalCuts[i]);

    return (long)mxh * mxw % 1000000007;
}

//  DAY 3 (376. Wiggle Subsequence)========================================================================================================

int wiggleMaxLength(vector<int>& nums) 
{
    int n = nums.size();
    int ans = 1, i = 1;

    while(i < n && nums[i] == nums[0]) i++;
    if(i == n) return ans;

    int up = nums[i] > nums[0];
    while(i < n)
    {
        while(up && i < n && nums[i] >= nums[i-1]) i++;
        while(!up && i < n && nums[i] <= nums[i-1]) i++;
        up ^= 1;
        ans++;
    }

    return ans;
}

//  DAY 4 (135. Candy)========================================================================================================

// APPROACH 1 --> O(n*logn)

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    vector<pair<int,int>> ri(n);
    for(int i = 0; i < n; i++)
        ri[i] = {ratings[i], i};

    sort(ri.begin(), ri.end());
    vector<int> candies(n);
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int j = ri[i].second;
        int lans = (j && ratings[j-1] < ratings[j])? candies[j-1] + 1 : 1;
        int rans = (j+1 < n && ratings[j+1] < ratings[j])? candies[j+1] + 1 : 1;
        candies[j] = max(lans, rans);
        ans += candies[j];
    }

    return ans;
}

// APPROACH 2 --> O(n)

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    int ans = 0;

    vector<int> candies(n,1);
    for(int i = 1; i < n; i++)
        if(ratings[i] > ratings[i-1])
            candies[i] = candies[i-1] + 1;
    for(int i = n-2; i >= 0; i--)
        if(ratings[i] > ratings[i+1])
            candies[i] = max(candies[i], candies[i+1] + 1);
    for(int i = 0; i < n; i++)
        ans += candies[i];

    return ans;
}

// DAY 5 (128. Longest Consecutive Sequence)====================================================================================

int longestConsecutive(vector<int>& nums) 
{
    unordered_map<int,int> mp;
    for(int x : nums)
    {
        if(mp.count(x)) continue;
        mp[x] = 1;
        if(!mp.count(x-1) && !mp.count(x+1)) continue;
        if(mp.count(x-1) && mp.count(x+1))
        {
            int lcnt = mp[x - (mp[x-1])];
            int rcnt = mp[x + (mp[x+1])];
            mp[x - (mp[x-1])] = lcnt + rcnt + 1;
            mp[x + (mp[x+1])] = lcnt + rcnt + 1;
        }
        else 
        {
            if(mp.count(x-1))
                mp[x] = ++mp[x - mp[x-1]];
            else if(mp.count(x+1))
                mp[x] = ++mp[x + (mp[x+1])];
        }
    }
    
    int ans = 0;
    for(auto p : mp)
        ans = max(ans, p.second);
    
    return ans;
}

// DAY 6 (509. Fibonacci Number)===================================================================================================

int fib(int n) 
{
    if(n <= 1) return n;
    int a = 0, b = 1, ans = 1;
    for(int i = 2; i <= n; i++)
    {
        ans = a + b;
        a = b;
        b = ans;
    }
    return ans;
}

// DAY 7 (97. Interleaving String)=============================================================================================

// APPROACH 1 (Usin 2D DP)

bool dfs(int i, int j, int k, int n, int m, int nm, string &s1, string &s2, string &s3, vector<vector<int>> &dp)
{
    if(i == n && j == m && k == nm) return true;
    if(k == nm) return false;
    if(dp[i][j] != -1) return dp[i][j];
    
    bool ans = false;
    if(i < n && s1[i] == s3[k])
        ans |= dfs(i+1, j, k+1, n, m, nm, s1, s2, s3, dp);
    if(j < m && s2[j] == s3[k])
        ans |= dfs(i, j+1, k+1, n, m, nm, s1, s2, s3, dp);
    
    return dp[i][j] = ans;
}

bool isInterleave(string s1, string s2, string s3) 
{
    int n = s1.size(), m = s2.size(), nm = s3.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
    return dfs(0, 0, 0, n, m, nm, s1, s2, s3, dp);
}

// DAY 8 (1473. Paint House III)===================================================================================================

int dfs(int i, int nbr, int lastc, int m, int n, vector<vector<int>> &cost, vector<int> &houses, int target, vector<vector<vector<int>>> &dp)
{
    if(nbr > target) return -1;
    if(i == m)
    {
        if(nbr == target) return 0;
        return -1;
    }
    if(dp[i][nbr][lastc] != INT_MAX) return dp[i][nbr][lastc];
    
    if(houses[i])
    {
        if(houses[i] == lastc)
            return dp[i][nbr][lastc] = dfs(i+1, nbr, houses[i], m, n, cost, houses, target, dp);
        else return dp[i][nbr][lastc] = dfs(i+1, nbr+1, houses[i], m, n, cost, houses, target, dp);
    }
    else
    {
        int ans = INT_MAX;
        for(int j = 0; j < n; j++)
        {
            int curr = 0;
            if(j+1 == lastc)
                curr = dfs(i+1, nbr, j+1, m, n, cost, houses, target, dp);
            else curr = dfs(i+1, nbr+1, j+1, m, n, cost, houses, target, dp);
            if(curr == -1) continue;
            ans = min(ans, curr + cost[i][j]);
        }
        return dp[i][nbr][lastc] = ans == INT_MAX? -1 : ans;
    }
}

int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) 
{
    vector<vector<vector<int>>> dp(m, vector<vector<int>>(target+1, vector<int>(n+1, INT_MAX)));
    return dfs(0, 0, 0, m, n, cost, houses, target, dp);
}