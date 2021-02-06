
// METHOD 1 (Kedanes and Reverse Kedanes)

int kedanes(vector<int> &nums)
{
    int sum = 0, maxsum = INT_MIN;
    for (int x : nums)
    {
        if (sum >= 0)
            sum += x;
        else
            sum = x;
        maxsum = max(maxsum, sum);
    }
    return maxsum;
}
int reverse_kedanes(vector<int> &nums)
{
    int sum = 0, minsum = INT_MAX;
    for (int x : nums)
    {
        if (sum < 0)
            sum += x;
        else
            sum = x;
        minsum = min(minsum, sum);
    }
    return minsum;
}

int maxAbsoluteSum(vector<int> &nums)
{
    return max(kedanes(nums), abs(reverse_kedanes(nums)));
}