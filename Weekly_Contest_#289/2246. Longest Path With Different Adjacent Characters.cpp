
  #define f first
  #define s second

  pair<int,int> dfs(int u, vector<vector<int>> &gp, string &s) // {curvedpath, linearpath}
  {
      int mxpath = 0;
      vector<int> curr = {0,0}; 
      for(int v : gp[u])
      {
          pair<int,int> child = dfs(v, gp, s); // {curvedpath, linearpath}
          mxpath = max(mxpath, child.f);
          if(s[u] != s[v])
              curr.push_back(child.s);
      }
      sort(curr.rbegin(), curr.rend());

      return {max(mxpath, curr[0] + curr[1] + 1), curr[0] + 1};
  }

  int longestPath(vector<int>& parent, string s) 
  {
      int n = s.size();
      vector<vector<int>> gp(n);
      for(int i = 1; i < parent.size(); i++)
          gp[parent[i]].push_back(i);

      return dfs(0, gp, s).f;
  }
