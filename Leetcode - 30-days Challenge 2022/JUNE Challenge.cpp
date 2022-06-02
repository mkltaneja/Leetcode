// DAY 1 (1480. Running Sum of 1d Array)=========================================================================================================================

vector<int> runningSum(vector<int>& nums) 
{
    for(int i = 0; i < nums.size(); i++)
        nums[i] += i? nums[i-1] : 0;
    return nums;
}

// DAY 2 (867. Transpose Matrix)=========================================================================================================================

vector<vector<int>> transpose(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> ans(m, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            ans[j][i] = matrix[i][j];
    return ans;
}
