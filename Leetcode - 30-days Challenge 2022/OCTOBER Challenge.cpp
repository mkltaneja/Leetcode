// DAY 1 (91. Decode Ways)=======================================================================================

  int numDecodings(string s) 
  {
      int n = s.size();
      vector<int> dp(n+2,0);
      dp[n] = 1;
      for(int i = n-1; i >= 0; i--)
      {
          if(s[i] == '0') continue;
          dp[i] = dp[i+1] + (((s[i]-'0')*10 + (s[i+1]-'0') <= 26)? dp[i+2] : 0);
      }
      return dp[0];
  }
