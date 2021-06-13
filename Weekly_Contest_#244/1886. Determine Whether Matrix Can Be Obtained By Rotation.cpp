
void rotate(vector<vector<int>> &mat)
{
    int n = mat.size(), m = mat[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            swap(mat[i][j], mat[j][i]);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m / 2; j++)
            swap(mat[i][j], mat[i][m - j - 1]);
}

bool findRotation(vector<vector<int>> &mat, vector<vector<int>> &target)
{
    if (mat == target)
        return true;
    rotate(mat);
    if (mat == target)
        return true;
    rotate(mat);
    if (mat == target)
        return true;
    rotate(mat);
    if (mat == target)
        return true;
    return false;
}