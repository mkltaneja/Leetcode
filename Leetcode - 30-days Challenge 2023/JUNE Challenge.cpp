
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
