
int kedanes(int i, int j, vector<int> &arr, int sign)
{
    int ans = INT_MIN, sum = 0;
    for (int ii = i; ii <= j; ii++)
    {
        sum = sign * arr[ii] + max(sum, 0);
        ans = max(ans, sum);
    }
    return ans;
}

int maxSubarraySumCircular(vector<int> &nums)
{
    int n = nums.size();
    int sum = 0;
    for (int x : nums)
        sum += x;
    if (n == 1)
        return sum;
    return max({kedanes(0, n - 1, nums, 1), sum + kedanes(0, n - 2, nums, -1), sum + kedanes(1, n - 1, nums, -1)});
}