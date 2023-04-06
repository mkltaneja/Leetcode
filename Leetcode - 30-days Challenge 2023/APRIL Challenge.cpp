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
