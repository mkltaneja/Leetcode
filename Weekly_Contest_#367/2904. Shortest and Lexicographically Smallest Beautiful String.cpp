class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) 
    {
        int n = s.size();
        string ans = s + "#";
        int ones = 0;
        for(int i = 0, j = 0; i < n; i++)
        {
            ones += s[i] == '1';
            while(ones >= k)
            {
                if(ones == k)
                {
                    string curr = s.substr(j, i-j+1);
                    if(curr.size() < ans.size() || (curr.size() == ans.size() && curr < ans))
                        ans = curr;
                }
                ones -= s[j++] == '1';
            }
        }
        
        return ans.back() == '#'? "" : ans;
    }
};
