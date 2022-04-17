
  #define f first
  #define s second
  pair<int,int> cnt(int x)
  {
      int two = 0, five = 0;
      while(x && x%2 == 0)
          two++, x /= 2;
      while(x && x%5 == 0)
          five++, x /= 5;

      return {two, five};
  }

  int maxTrailingZeros(vector<vector<int>>& grid) 
  {
      int n = grid.size(), m = grid[0].size();
      vector<vector<pair<int,int>>> lr(n, vector<pair<int,int>>(m)), rl(n, vector<pair<int,int>>(m));
      vector<vector<pair<int,int>>> ud(n, vector<pair<int,int>>(m)), du(n, vector<pair<int,int>>(m));
      for(int i = 0; i < n; i++)
      {
          pair<int,int> tf = {0,0};
          for(int j = 0; j < m; j++)
          {
              pair<int,int> curr1 = cnt(grid[i][j]);
              pair<int,int> curr2 = cnt(grid[i][m-j-1]);
              lr[i][j].f = curr1.f + (j? lr[i][j-1].f : 0);
              lr[i][j].s = curr1.s + (j? lr[i][j-1].s : 0);
              rl[i][m-j-1].f = curr2.f + (j? rl[i][m-j].f : 0);
              rl[i][m-j-1].s = curr2.s + (j? rl[i][m-j].s : 0);
          }
      }
      for(int j = 0; j < m; j++)
      {
          pair<int,int> tf = {0,0};
          for(int i = 0; i < n; i++)
          {
              pair<int,int> curr1 = cnt(grid[i][j]);
              pair<int,int> curr2 = cnt(grid[n-i-1][j]);
              ud[i][j].f = curr1.f + (i? ud[i-1][j].f : 0);
              ud[i][j].s = curr1.s + (i? ud[i-1][j].s : 0);
              du[n-i-1][j].f = curr2.f + (i? du[n-i][j].f : 0);
              du[n-i-1][j].s = curr2.s + (i? du[n-i][j].s : 0);
          }
      }

      int ans = 0;
      for(int i = 0; i < n; i++)
      {
          for(int j = 0; j < m; j++)
          {
              pair<int,int> tf = cnt(grid[i][j]);
              int t1 = lr[i][j].f;
              int f1 = lr[i][j].s;
              int t2 = rl[i][j].f;
              int f2 = rl[i][j].s;
              int t3 = ud[i][j].f;
              int f3 = ud[i][j].s;
              int t4 = du[i][j].f;
              int f4 = du[i][j].s;
              int a = min(t1 + t3 - tf.f, f1 + f3 - tf.s);
              int b = min(t2 + t3 - tf.f, f2 + f3 - tf.s);
              int c = min(t1 + t4 - tf.f, f1 + f4 - tf.s);
              int d = min(t2 + t4 - tf.f, f2 + f4 - tf.s);
              ans = max({ans, a, b, c, d});
          }
      }

      return ans;
  }
