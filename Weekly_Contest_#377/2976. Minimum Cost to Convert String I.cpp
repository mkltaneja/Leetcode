
// Time = O(n + m + 26^3), Space = O(26*26)

class Solution {
public:
    
    #define ll long long
    ll INF = INT_MAX;
    
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) 
    {
        int n = source.size(), m = original.size();
        ll md[26][26];
        for(int i = 0; i < 26; i++)
        {
            for(int j = 0; j < 26; j++)
                md[i][j] = INF;
            md[i][i] = 0;
        }
        for(int i = 0; i < m; i++)
            md[original[i]-'a'][changed[i]-'a'] = min(md[original[i]-'a'][changed[i]-'a'], (ll)cost[i]);
        
        for(int k = 0; k < 26; k++)
            for(int i = 0; i < 26; i++)
                for(int j = 0; j < 26; j++)
                    md[i][j] = min(md[i][j], md[i][k] + md[k][j]);
        
        ll ans = 0;
        for(int i = 0; i < n; i++)
        {
            ll x = md[source[i]-'a'][target[i]-'a'];
            if(x >= INF) 
                return -1;
            ans += x;
        }
        
        return ans;
    }
};
