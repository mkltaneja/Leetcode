
// APPROACH 1 (Dividing strings in half and taking minimum of all 1s and all 2s)

class Solution {
public:
    
    #define ll long long
    
    ll makeAllSame(string &s, char c)
    {
        ll ans = 0;
        ll i = 0, n = s.size();
        ll lastOcc = -1;
        while(i < n)
        {
            if(s[i] == c)
            {
                lastOcc = i++;
                continue;
            }
            ll j = i;
            while(j < n && s[j] != c)
                j++;
            ans += j + (lastOcc + 1);
            i = j;
        }
        return ans;
    }
    
    long long minimumCost(string s) 
    {
        int n = s.size();
        string s1 = s.substr(0,n/2);
        string s2 = s.substr(n/2);
        reverse(s2.begin(), s2.end());
        
        ll x = makeAllSame(s1, '0') + makeAllSame(s2, '0');
        ll y = makeAllSame(s1, '1') + makeAllSame(s2, '1');
        return min(x, y);
    }
};
