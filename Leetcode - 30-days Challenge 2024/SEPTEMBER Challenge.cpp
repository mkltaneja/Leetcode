
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

// DAY 2 (1894. Find the Student that Will Replace the Chalk)=========================================================

// Time Complexity = O(n + logn)
// Time Complexity = O(n)

int chalkReplacer(vector<int>& chalk, int k)
{
    int size = chalk.size();
    vector<long> prefChalkSum(size, 0);
    for(int idx = 0; idx < size; idx++)
        prefChalkSum[idx] = (idx? prefChalkSum[idx-1] : 0) + chalk[idx];
    
    long kulChalks = prefChalkSum[size-1];
    int bacheChalks = k % kulChalks;

    int bakchodBacha = upper_bound(prefChalkSum.begin(), prefChalkSum.end(), bacheChalks) - prefChalkSum.begin();

    return bakchodBacha;
}
