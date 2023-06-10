class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<int> row((1 << m), -1);
        for(int i = 0; i < n; i++)
        {
            int x = 0;
            for(int j = 0; j < m; j++)
                x |= (grid[i][j] << j);
            row[x] = i;
        }
        
        for(int i = 1; i < (1 << m); i++)
        {
            for(int j = i+1; j < (1 << m); j++)
            {
                if(!(i & j) && row[i] != -1 && row[j] != -1)
                    return {min(row[i], row[j]), max(row[i], row[j])};
            }
        }
        
        if(row[0] != -1)
            return {row[0]};
        return {};
    }
};
