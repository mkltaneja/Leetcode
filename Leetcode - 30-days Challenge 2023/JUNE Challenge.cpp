
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
