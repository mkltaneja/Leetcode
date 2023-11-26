class Solution {
public:
    
    #define ll long long
    
    bool isVowel(char c)
    {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
    
    long long beautifulSubstrings(string s, int k)
    {
        ll ans = 0;
        unordered_map<int, unordered_map<int, ll>> mp;
        mp[0][0] = 1;
        int n = s.size();
        int cc = 0, v = 0, kk = k;
        
        for(int x = 1; x <= n; x++)
        {
            if(x * x % k == 0)
            {
                kk = x;
                break;
            }
        }
        
        for(char c : s)
        {
            if(isVowel(c)) v++;
            else cc++;
            
            int mn = min(cc, v);
            ans += mp[cc - v][mn % kk]++;
        }
        
        return ans;
    }
};
