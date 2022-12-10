class Solution {
public:
    
    int maxStarSum(vector<int>& vals, vector<vector<int>>& edges, int k) 
    {
        int n = vals.size();
        vector<vector<int>> gp(n);
        for(vector<int> &e : edges)
        {
            gp[e[0]].push_back(e[1]);
            gp[e[1]].push_back(e[0]);
        }
        
        int mx = INT_MIN;
        for(int i = 0; i < n; i++)
        {
            sort(gp[i].begin(), gp[i].end(), [&](const int a, const int b)
            {
                return vals[a] > vals[b];
            });
            int tmp = k;
            int sum = 0;
            for(int v : gp[i])
            {
                if(vals[v] <= 0 || tmp-- == 0) break;
                sum += vals[v];
            }
            mx = max(mx, vals[i] + sum);
        }
        
        return mx;
    }
};
