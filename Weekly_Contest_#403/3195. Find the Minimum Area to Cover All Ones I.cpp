
// Time Complexity = O(n + m)
// Time Complexity = O(1)

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid)
    {
        int n = grid.size(), m = grid[0].size();
        int l = 0, r = m-1, u = 0, d = n-1;
        int fl = 0;
        while(l < m && !fl)
        {
            for(int i = 0; i < n && !fl; i++)
                fl = grid[i][l];
            if(!fl) l++;
        }
        fl = 0;
        while(r >= 0 && !fl)
        {
            for(int i = 0; i < n && !fl; i++)
                fl = grid[i][r];
            if(!fl) r--;
        }
        fl = 0;
        while(u < n && !fl)
        {
            for(int i = 0; i < m && !fl; i++)
                fl = grid[u][i];
            if(!fl) u++;
        }
        fl = 0;
        while(d >= 0 && !fl)
        {
            for(int i = 0; i < m && !fl; i++)
                fl = grid[d][i];
            if(!fl) d--;
        }
        
        return (r-l+1) * (d-u+1);
    }
};
