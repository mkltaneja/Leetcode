class Solution {
public:
    
    #define f first
    #define s second
    int maxIncreasingCells(vector<vector<int>>& mat) 
    {
        int n = mat.size(), m = mat[0].size();
        map<int,vector<pair<int,int>>> mp;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                mp[mat[i][j]].push_back({i, j});
        
        int ans = 0;
        vector<int> maxr(n, 0), maxc(m, 0);
        for(auto itr : mp)
        {
            vector<int> maxrc;
            for(pair<int,int> p : itr.s)
                maxrc.push_back(max(maxr[p.f], maxc[p.s]) + 1);
            
            for(int i = 0; i < maxrc.size(); i++)
            {
                int x = itr.s[i].f, y = itr.s[i].s;
                maxr[x] = max(maxrc[i], maxr[x]);
                maxc[y] = max(maxrc[i], maxc[y]);
                ans = max(ans, maxrc[i]);
            }
        }
        
        return ans;
    }
};
