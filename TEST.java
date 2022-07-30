class Solution {
    public int orangesRotting(int[][] grid) {
        // variables row, col, num, queue
        int row = grid.length;
        int col = grid[0].length; 
        int oSum = 0, sum = 0;
        int min = 0;
        int[] dr = new int[]{0, 0, 1, -1};
        int[] dc = new int[]{1, -1, 0, 0};
        Queue<int[]> q = new LinkedList<>();
        
        // check how many oranges
        for(int i = 0; i < row; i++){
            for(int j = 0; j < col; j++){
                if(grid[i][j] != 0)
                    oSum++;
                if(grid[i][j] == 2){
                    q.offer(new int[]{i, j});
                    sum++;
                }
            }
        }
        // special cases
        if(oSum == 0)
            return 0;
        
        // BFS to check neighbours
        while(!q.isEmpty()){
            int size = q.size();
            for(int x = 0; x < size; x++){
                int[] temp = q.poll();
                int r = temp[0];
                int c = temp[1];
                for(int i = 0; i < 4; i++){
                    int rNew = r + dr[i];
                    int cNew = c + dc[i];
                    if(rNew >= 0 && rNew < row && cNew >= 0 && cNew < col){
                        if(grid[rNew][cNew] == 1){
                            grid[rNew][cNew] = 2;
                            q.offer(new int[]{rNew, cNew});
                            sum++;
                        }
                    }
                }
            }
            min++;
        }   
        // return
        if(oSum != sum)
            return -1;
        return min-1;
    }
}

// Time complexity: O(mn + mn*4(worst cases)) = O(mn)
// Space Complecity: O(mn)