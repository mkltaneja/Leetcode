
long long subseq(int i, vector<vector<int>> &arr, vector<long long> &dp)
{
    if (i >= arr.size())
        return 0;
    if (dp[i] != -1)
        return dp[i];
    return dp[i] = max(subseq(i + arr[i][1] + 1, arr, dp) + (long long)arr[i][0], subseq(i + 1, arr, dp));
}

long long mostPoints(vector<vector<int>> &questions)
{
    vector<long long> dp(questions.size() + 1, -1);
    return subseq(0, questions, dp);
}