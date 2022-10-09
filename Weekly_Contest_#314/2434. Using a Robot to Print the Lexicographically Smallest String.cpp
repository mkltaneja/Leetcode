class Solution {
public:
    string robotWithString(string s)
    {
        string ans = "";
        string t = "";
        vector<int> map(26,0);
        for(char c : s)
            map[c-'a']++;
        
        int j = 0;
        for(int i = 0; i < 26; i++)
        {
            while(!t.empty() && t.back() <= char(i+'a'))
            {
                ans += t.back();
                t.pop_back();
            }
            while(j < s.size() && map[i])
            {
                if(s[j]-'a' != i) 
                {
                    t += s[j];
                    map[s[j]-'a']--;
                }
                else
                {
                    ans += char(i+'a');
                    map[i]--;
                }
                j++;
            }
        }
        
        while(!t.empty())
        {
            ans += t.back();
            t.pop_back();
        }
        
        return ans;
    }
};
