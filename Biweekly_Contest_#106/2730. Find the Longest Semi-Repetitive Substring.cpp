class Solution {
public:
    int longestSemiRepetitiveSubstring(string s) 
    {
        int n = s.size();
        int ans = 0, found = -1, last = -1, lastp = -1;
        for(int i = 0; i+1 < n; i++)
        {
            if(s[i] == s[i+1])
            {
                last = lastp;
                lastp = i;
            }
            ans = max(ans, i - last + 1);
        }
        return ans == 0? n : ans;
    }
};
