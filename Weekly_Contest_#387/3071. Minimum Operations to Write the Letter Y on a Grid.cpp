
// Time Complexity = O(n^2)
// Space Complexity = O(1)

class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        int zero1 = 0, one1 = 0, two1 = 0;
        int zero2 = 0, one2 = 0, two2 = 0;
        for(int i = 0, j = 0; i < (n + 1)/2; i++, j++)
        {
            if(grid[i][j] == 0)
            {
                zero1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 1)
            {
                one1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 2)
            {
                two1++;
                grid[i][j] = -1;
            }
        }
        for(int i = 0, j = n-1; i < (n + 1)/2; i++, j--)
        {
            if(grid[i][j] == 0)
            {
                zero1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 1)
            {
                one1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 2)
            {
                two1++;
                grid[i][j] = -1;
            }
        }
        for(int i = (n+1)/2, j = n/2; i < n; i++)
        {
            if(grid[i][j] == 0)
            {
                zero1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 1)
            {
                one1++;
                grid[i][j] = -1;
            }
            else if(grid[i][j] == 2)
            {
                two1++;
                grid[i][j] = -1;
            }
        }
        
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(grid[i][j] == 0)
                    zero2++;
                else if(grid[i][j] == 1)
                    one2++;
                else if(grid[i][j] == 2)
                    two2++;
            }
        }
        
        int ans = INT_MAX;
        ans = min(ans, (one1 + two1) + (zero2 + two2)); // 0 1
        ans = min(ans, (two1 + zero1) + (one2 + two2)); // 1 0
        ans = min(ans, (one1 + two1) + (zero2 + one2)); // 0 2
        ans = min(ans, (one1 + zero1) + (one2 + two2)); // 2 0
        ans = min(ans, (two1 + zero1) + (zero2 + one2)); // 1 2
        ans = min(ans, (one1 + zero1) + (zero2 + two2)); // 2 1
        
        return ans;
    }
};
