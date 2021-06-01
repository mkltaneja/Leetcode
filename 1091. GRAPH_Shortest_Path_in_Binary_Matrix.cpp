int shortestPathBinaryMatrix(vector<vector<int>>& grid) 
{
    int n = grid.size();
    if(n == 0)
        return -1;
    int m = grid[0].size();
    
    if(grid[0][0] == 1 || grid[n-1][m-1] == 1)
        return -1;
    
    int dir[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
    
    int level = 1;
    queue<int> que;
    que.push(0);
    grid[0][0] = 1;
    
    while(!que.empty())
    {
        int size = que.size();
        while(size-- > 0)
        {
            int rvtx = que.front();
            que.pop();
            
            int r = rvtx / m;
            int c = rvtx % m;
            
            if(r == n-1 && c == m-1)
                return level;
            
            for(int d=0;d<8;d++)
            {
                int x = r + dir[d][0];
                int y = c + dir[d][1];
                
                if(x >= 0 && x < n && y >= 0 && y < m && grid[x][y] == 0)
                {
                    que.push((x*m + y));
                    grid[x][y] = 1;
                }
            }
        }
        level++;
    }
    return -1;
}