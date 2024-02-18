
// Time Complexity = O(n*m*m)
// Space Complexity = O(26*n)

class Solution {
public:
    
    #define ll long long
    
    vector<int> findLPS(string &s)
    {
        vector<int> lps(s.size(), 0);
        for(int i = 1, len = 0; i < s.size(); )
        {
            if(s[i] == s[len])
                lps[i++] = ++len;
            else
            {
                if(len) len = lps[len-1];
                else i++;
            }
        }
        return lps;
    }
    
    long long countPrefixSuffixPairs(vector<string>& words) 
    {
        int n = words.size();
        unordered_map<string, ll> mp;
        vector<unordered_map<ll, ll>> lens(26);
        ll ans = 0;

        for(string s : words)
        {
            vector<int> lps = findLPS(s);
            int len = lps.back();
            if(len == s.size()-1)
            {
                ans += mp[s]++;
                char c = s[0];
                int tmp = len;
                unordered_map<ll,ll> tmp2 = lens[c-'a'];
                while(tmp)
                {
                    if(tmp2.count(tmp))
                        ans += tmp2[tmp];
                    tmp--;
                }
                lens[c-'a'][len+1]++;
                continue;
            }
            while(len)
            {
                string p = s.substr(0, len);
                ans += mp.count(p)? mp[p] : 0;
                len = lps[len-1];
            }
            ans += mp.count(s)? mp[s] : 0;
            mp[s]++;
        }
        
        return ans;
    }
};
