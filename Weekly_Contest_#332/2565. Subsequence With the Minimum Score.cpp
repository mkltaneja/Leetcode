class Solution {
public:
    int minimumScore(string s, string t) 
    {
        int n = s.size(), m = t.size();
        vector<int> pre(n);
        int j = 0;
        for(int i = 0; i < n; i++)
        {
            if(j < m && s[i] == t[j]) j++;
            pre[i] = j;
        }
        
        int ans = m - j;
        j = m-1;
        
        for(int i = n-1; i >= 0; i--)
        {
            ans = min(ans, max(0, j - pre[i] + 1));
            if(j >= 0 && s[i] == t[j]) j--;
        }
        ans = min(ans, j+1);
        
        return ans;
    }
};
