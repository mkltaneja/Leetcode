
// Time Compelxity = O(n^2)
// Space Compelxity = O(n^2)

class Solution {
public:
    int maximumLength(string s) 
    {
        int n = s.size();
        unordered_map<string, int> mp;
        for(int i = 0; i < n; i++)
        {
            int j = i;
            string curr = "";
            while(j < n && s[j] == s[i])
            {
                curr += s[j++];
                mp[curr]++;
            }
        }
        int ans = -1;
        for(auto p : mp)
            if(p.second >= 3)
                ans = max(ans, (int)p.first.size());
        return ans;
    }
};
