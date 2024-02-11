
// APPROACH 1 (Finding max with space)

// Time Complexity = O(2 * n * m)
// Space Complexity = O(m)

class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) 
    {
        int n = matrix.size();
        int m = matrix[0].size();
        vector<int> mx(m, -1);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                mx[j] = max(mx[j], matrix[i][j]);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < m; j++)
                if(matrix[i][j] == -1)
                    matrix[i][j] = mx[j];
        return matrix;
    }
};

// APPROACH 2 (Finding max without extra space)

// Time Complexity = O(2 * n * m)
// Space Complexity = O(1)

class Solution {
public:
    vector<vector<int>> modifiedMatrix(vector<vector<int>>& matrix) 
    {
        int n = matrix.size();
        int m = matrix[0].size();
        for(int j = 0; j < m; j++)
        {
            int mx = -1;
            for(int i = 0; i < n; i++)
                mx = max(mx, matrix[i][j]);
            for(int i = 0; i < n; i++)
                if(matrix[i][j] == -1)
                    matrix[i][j] = mx;
        }
        return matrix;
    }
};
