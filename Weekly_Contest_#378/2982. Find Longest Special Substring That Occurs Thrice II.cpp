
// Time Complexity = O(26*(n*logn + n))
// Space Complexity = O(max(26, n))

class Solution {
public:
    int maximumLength(string s) 
    {
        int n = s.size();
        int ans = -1;
        vector<unordered_map<int,int>> mp(26);
        for(int i = 0; i < n; )
        {
            int j = i;
            while(j < n && s[j] == s[i])
                j++;
            mp[s[i]-'a'][j-i]++;
            i = j;
        }
        
        char c = 'a';
        for(auto p : mp)
        {
            c++;
            if(p.empty()) continue;
            vector<pair<int,int>> tmp;
            for(auto p2 : p)
                tmp.push_back(p2);
            sort(tmp.rbegin(), tmp.rend());

            for(int i = 0; i < tmp.size(); i++)
            {
                if(tmp[i].second >= 3 || i)
                    ans = max(ans, tmp[i].first);
                if(tmp[i].first >= 3)
                {
                    ans = max(ans, tmp[i].first - 2);
                    if(tmp[i].second > 1)
                        ans = max(ans, tmp[i].first - 1);
                }
            }
        }
        
        return ans;
    }
};

// "iiiiifffffffoooookkkfffffffnnxxxxxx"
// "aaaa"
// "abcdef"
// "abcaba"
// "abaac"
// "abaaac"
// "aaaabbbaabbbaabbb"
// "aada"
// "aaabaa"
