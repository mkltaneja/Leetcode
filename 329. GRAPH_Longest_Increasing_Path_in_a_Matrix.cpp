int longestIncreasingPath(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    if (n == 0)
        return 0;
    int m = matrix[0].size();
    if (m == 0)
        return 0;

    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    vector<vector<int>> inDegree(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];
                if (x < n && x >= 0 && y < m && y >= 0 && matrix[x][y] > matrix[i][j])
                    inDegree[x][y]++;
            }
        }
    }
    queue<int> que;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (inDegree[i][j] == 0)
                que.push(i * m + j);

    int length = 0;
    while (!que.empty())
    {
        int size = que.size();
        while (size--)
        {
            int rvtx = que.front();
            que.pop();

            int i = rvtx / m;
            int j = rvtx % m;
            for (int d = 0; d < 4; d++)
            {
                int x = i + dir[d][0];
                int y = j + dir[d][1];
                while (x < n && x >= 0 && y < m && y >= 0 && matrix[x][y] > matrix[i][j] && --inDegree[x][y] == 0)
                    que.push(x * m + y);
            }
        }
        length++;
    }
    return length;
}