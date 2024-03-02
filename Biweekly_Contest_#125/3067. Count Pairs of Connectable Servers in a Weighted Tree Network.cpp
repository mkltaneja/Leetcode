
// APPROACH 1 (Using Maps -> More scalable for if sum of lengths of path should be divisible by signalSpeed)

// Time Complexity = >O(n^2)
// Space Complexity = O(2*n)

class Solution {
public:
    
    void dfs(int u, int p, int d, int ss, vector<vector<vector<int>>> &gp, unordered_map<int, int> &mods)
    {
        mods[d]++;
        for(vector<int> &c : gp[u])
            if(c[0] != p)
                dfs(c[0], u, (d + c[1]) % ss, ss, gp, mods);
    }
    
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) 
    {
        int n = edges.size() + 1;
        vector<vector<vector<int>>> gp(n);
        vector<int> ans(n);
        for(auto e : edges)
        {
            gp[e[0]].push_back({e[1], e[2]});
            gp[e[1]].push_back({e[0], e[2]});
        }
        
        for(int p = 0; p < n; p++)
        {
            unordered_map<int, int> totMods;
            for(vector<int> &c : gp[p])
            {
                unordered_map<int, int> mods;
                dfs(c[0], p, c[1] % signalSpeed, signalSpeed, gp, mods);
                ans[p] += mods[0] * totMods[0];
                totMods[0] += mods[0];
            }
        }
        
        return ans;
    }
};
