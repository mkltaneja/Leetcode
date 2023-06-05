
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
