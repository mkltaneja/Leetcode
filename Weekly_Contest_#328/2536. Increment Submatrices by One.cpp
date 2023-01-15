class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) 
    {
        vector<vector<int>> mat(n+2, vector<int>(n+2, 0));
        vector<vector<int>> ans(n, vector<int>(n, 0));
        for(vector<int> &q : queries)
        {
            while(q[0] <= q[2])
            {
                mat[q[0]+1][q[1]+1]++;
                mat[q[0]+1][q[3]+2]--;
                q[0]++;
            }
        }
        
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                ans[i-1][j-1] = (j > 1? ans[i-1][j-2] : 0) + mat[i][j];
        
        return ans;
    }
};
