int lengthOfLIS(vector<int> &arr)
{
    if (arr.size() == 0)
        return 0;
    vector<int> dp(arr.size(), 1);
    int omax = 1;
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (arr[j] < arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        omax = max(omax, dp[i]);
    }
    return omax;
}

///////////////////OR///////////////////////

int lengthOfLIS(vector<int> &arr)
{
    if (arr.size() == 0)
        return 0;
    vector<int> dp(arr.size(), 1);
    int omax = 1;
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] > arr[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        omax = max(omax, dp[i]);
    }
    return omax;
}