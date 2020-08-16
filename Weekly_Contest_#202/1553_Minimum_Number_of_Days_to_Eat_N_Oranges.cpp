
// Method 1 --> BFS (using queue)
// TLE
int minDays(int n) 
{
    queue<pair<int,int>> que;
    que.push({n,0});
    
    while(!que.empty())
    {
        auto tp = que.front();
        que.pop();
        int x = tp.first;
        int c = tp.second;
        // cout<<x<<" "<<c<<endl;
        
        if(x == 1)
            return c+1;
        
        if(x % 2 == 0)
            que.push({x/2, c+1});
        if(x % 3 == 0)
            que.push({x/3, c+1});
        if(x - 1 > 1)
            que.push({x-1, c+1});
    }
    return 0;
}
// Method 2 --> DFS (using DP)
// sub method 1 (naive)

int dfs(vector<int> &dp, int n)
{
    if(n == 1)
        return dp[n] = 1;
    if(dp[n] != -1)
        return dp[n];
    
    int count = INT_MAX;
    
    count = min(count, dfs(dp, n-1) + 1);
    if(n % 2 == 0)
        count = min(count, dfs(dp, n/2) + 1);
    if(n % 3 == 0)
        count = min(count, dfs(dp, n/3) + 1);
    return dp[n] = count;
}

int minDays(int n) 
{
    vector<int> dp(n+1,-1);
    return dfs(dp,n);
}

// sub method 2


int dfs(unordered_map<int,int> &dp, int n)
{
    if(n == 0)
        return dp[n] = 0;
    if(n == 1)
        return dp[n] = 1;
    if(dp.count(n))
        return dp[n];
    
    int count = n;
    // cout<<count<<endl;
    
    if(n % 2 == 0)
        count = min(count, dfs(dp, n/2) + 1);
    else if(n % 2 == 1)
        count = min(count, dfs(dp, n/2) + 2);
    
    if(n % 3 == 0)
        count = min(count, dfs(dp, n/3) + 1);
    else if(n % 3 == 1)
        count = min(count, dfs(dp, n/3) + 2);
    else if(n % 3 == 2)
        count = min(count, dfs(dp, n/3) + 3);
    
    return dp[n] = count;
}

int minDays(int n) 
{
    unordered_map<int,int> dp;  //here taking vector will give tle on the high values of n like 1e8
    return dfs(dp,n);
}