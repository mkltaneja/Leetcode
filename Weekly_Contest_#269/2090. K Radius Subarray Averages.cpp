
vector<int> getAverages(vector<int> &nums, int k)
{
    long sum = 0;
    int n = nums.size();
    vector<long> lsum(n), rsum(n);
    for (int i = 0; i < n; i++)
    {
        if (i > k)
            sum -= nums[i - k - 1];
        if (i >= k)
            lsum[i] = sum;
        else
            lsum[i] = -1;
        sum += nums[i];
    }
    sum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (n - 1 - i > k)
            sum -= nums[i + k + 1];
        if (n - 1 - i >= k)
            rsum[i] = sum;
        else
            rsum[i] = -1;
        sum += nums[i];
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        if (lsum[i] == -1 || rsum[i] == -1)
            ans[i] = -1;
        else
            ans[i] = (lsum[i] + nums[i] + rsum[i]) / (2 * k + 1);
    }

    return ans;
}