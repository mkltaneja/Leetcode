
vector<vector<char>> rotateTheBox(vector<vector<char>> &box)
{
    int n = box.size(), m = box[0].size();
    for (int i = 0; i < n; i++)
    {
        int stoni = 0;
        for (int j = 0; j < m; j++)
        {
            if (box[i][j] == '.')
                swap(box[i][stoni++], box[i][j]);
            else if (box[i][j] == '*')
                stoni = j + 1;
        }
    }
    vector<vector<char>> ans(m, vector<char>(n));
    int k = 0;
    for (int j = 0; j < m; j++)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            ans[k / n][k % n] = box[i][j];
            k++;
        }
    }
    return ans;
}