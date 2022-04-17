
  int minimumRounds(vector<int>& tasks) 
  {
      unordered_map<int,int> mp;
      for(int x : tasks)
          mp[x]++;

      int ans = 0;
      for(auto p : mp)
      {
          if(p.second == 1) return -1;
          if(p.second % 3 == 0) ans += p.second / 3;
          if(p.second % 3 == 1) ans += p.second / 3 + 1;
          if(p.second % 3 == 2) ans += p.second / 3 + 1;
      }
      return ans;
  }
