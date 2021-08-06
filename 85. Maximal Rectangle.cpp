
int largestArea(int n, vector<int> &hts)
{
    int maxarea = 0;
    stack<int> st;
    for (int i = 0; i <= n; i++)
    {
        int x = (i == n) ? 0 : hts[i];
        while (!st.empty() && x < hts[st.top()])
        {
            int ht = hts[st.top()];
            st.pop();
            maxarea = max(maxarea, ht * (st.empty() ? i : i - st.top() - 1));
        }
        st.push(i);
    }
    return maxarea;
}

int maximalRectangle(vector<vector<char>> &matrix)
{
    int n = matrix.size();
    if (n == 0)
        return 0;
    int m = matrix[0].size();
    vector<vector<int>> hts(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] - '0')
                hts[i][j] = i ? (hts[i - 1][j] + 1) : matrix[i][j] - '0';

    int maxarea = 0;
    for (int i = 0; i < n; i++)
        maxarea = max(maxarea, largestArea(m, hts[i]));

    return maxarea;
}