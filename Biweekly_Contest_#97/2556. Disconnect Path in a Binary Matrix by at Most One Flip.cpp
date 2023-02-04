class Solution {
public:
    
    vector<vector<int>> down, up, arr;
    int n = 0, m = 0;
    
    void dfs1(int i, int j)
    {
        if(i == n || j == m) return;
        if(!arr[i][j] || down[i][j]) return;
        
        down[i][j] = 1;
        
        dfs1(i+1, j);
        dfs1(i, j+1);
    }
    
    void dfs2(int i, int j)
    {
        if(i == -1 || j == -1) return;
        if(!arr[i][j] || up[i][j]) return;
        
        up[i][j] = 1;
        
        dfs2(i-1, j);
        dfs2(i, j-1);
    }
    
    bool isPossibleToCutPath(vector<vector<int>>& grid) 
    {
        n = grid.size(), m = grid[0].size();
        arr = grid;
        down.assign(n, vector<int>(m, 0));
        up.assign(n, vector<int>(m, 0));
        
        dfs1(0, 0);
        dfs2(n-1, m-1);
        
        if(!down[n-1][m-1] || !up[0][0]) return true;
        
        vector<int> diag(n+m-1, 0);
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                if((i == 0 && j == 0) || (i == n-1 && j == m-1))
                    continue;
                diag[i+j] += down[i][j] & up[i][j];
            }
        }
        
        for(int d = 0; d < n+m-1; d++)
            if(diag[d] == 1)
                return true;
        
        return false;
    }
};
