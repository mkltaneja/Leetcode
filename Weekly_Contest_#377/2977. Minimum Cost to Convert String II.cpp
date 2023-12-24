
// Time = O(m^3 + n^2), Space = O(m^2 + n)

class Solution {
public:
    
    #define ll long long
    ll INF = 1e12;
    ll md[500][500];
    
    ll dfs(string &source, string &target, unordered_map<string, int> &label)
    {
        int n = source.size();
        vector<ll> dp(n+1, INF);
        dp[n] = 0;
        
        unordered_set<int> lensSt;
        vector<int> lens;
        for(auto node : label)
            lensSt.insert(node.first.size());
        for(int len : lensSt)
            lens.push_back(len);
        sort(lens.begin(), lens.end());
        
        for(int i = n-1; i >= 0; i--)
        {
            if(source[i] == target[i])
                dp[i] = min(dp[i], dp[i+1]);
            for(int l : lens)
            {
                if(i+l > n) break;
                
                string currSource = source.substr(i, l);
                string currTarget = target.substr(i, l);
                if(label.count(currSource) && label.count(currTarget))
                {
                    int u = label[currSource];
                    int v = label[currTarget];
                    dp[i] = min(dp[i], md[u][v] + dp[i+l]);
                }
            }
        }
        
        return dp[0];
    }
    
    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) 
    {
        ll n = source.size(), m = original.size();
        unordered_map<string, int> label;
        
        for(int i = 0; i < m; i++)
        {
            label[original[i]] = 0;
        }
        for(int i = 0; i < m; i++)
        {
            label[changed[i]] = 0;
        }
        int total = 0;
        for(auto &p : label)
            p.second = total++;
        
        for(int i = 0; i < total; i++)
        {
            for(int j = 0; j < total; j++)
                md[i][j] = INF;
            md[i][i] = 0;
        }
        for(int i = 0; i < m; i++)
        {
            int u = label[original[i]];
            int v = label[changed[i]];
            md[u][v] = min(md[u][v], (ll)cost[i]);
        }
        
        for(int k = 0; k < total; k++)
            for(int i = 0; i < total; i++)
                for(int j = 0; j < total; j++)
                    md[i][j] = min(md[i][j], md[i][k] + md[k][j]);

        ll ans = dfs(source, target, label);
        
        return ans >= INF? -1 : ans;
    }
};
