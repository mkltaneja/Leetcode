
// APPROACH 1 (Brute Force) --> time = O(n^3)

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

// APPROACH 2 (DP) --> time = O(n^2)

class Solution {
public:
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>>& queries) 
    {
        vector<vector<int>> mat(n+1, vector<int>(n+1, 0));
        vector<vector<int>> ans(n, vector<int>(n, 0));
        for(vector<int> &q : queries)
        {
            mat[q[0]][q[1]]++;
            mat[q[0]][q[3]+1]--;
            mat[q[2]+1][q[1]]--;
            mat[q[2]+1][q[3]+1]++;
        }
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i) mat[i][j] += mat[i-1][j];
                if(j) mat[i][j] += mat[i][j-1];
                if(i && j) mat[i][j] -= mat[i-1][j-1];
                
                ans[i][j] = mat[i][j];
            }
        }
        
        return ans;
    }
};
