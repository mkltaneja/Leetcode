class Solution {
public:
    int findChampion(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        vector<int> inDeg(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(i != j && grid[i][j])
                    inDeg[j]++;
        for(int i = 0; i < n; i++)
            if(inDeg[i] == 0)
                return i;
        return -1;
    }
};
