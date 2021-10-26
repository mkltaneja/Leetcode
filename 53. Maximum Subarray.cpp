
int maxSubArray(vector<int> &nums)
{
    int sum = 0, maxsum = INT_MIN;
    for (int x : nums)
    {
        sum = max(sum + x, x);
        maxsum = max(maxsum, sum);
    }
    return maxsum;
}