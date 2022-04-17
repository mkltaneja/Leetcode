
  string digitSum(string s, int k) 
  {
      int n = s.size();
      while(n > k)
      {
          int i = 0;
          string tmp = "";
          while(i < n)
          {
              int x = 0, kk = k;
              while(i < n && kk--)
              {
                  x += s[i++]-'0';
              }
              tmp += to_string(x);
          }
          s = tmp;
          n = s.size();
      }
      return s;
  }
