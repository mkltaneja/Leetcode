
// DAY 1 (2022. Convert 1D Array Into 2D Array)====================================================================

// Time Complexity - O(n*m)
// Space Complexity - O(n*m)

vector<vector<int>> construct2DArray(vector<int>& original, int m, int n)
{
    int size = original.size();
    if(size != n*m)
        return {};
    
    vector<vector<int>> ans(m, vector<int>(n));
    for(int i = 0; i < size; i++)
    {
        int row = i / n;
        int col = i % n;
        ans[row][col] = original[i];
    }

    return ans;
}
