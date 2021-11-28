
int minimumDeletions(vector<int> &nums)
{
    int n = nums.size();
    int i1 = 0, i2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] < nums[i1])
            i1 = i;
        if (nums[i] > nums[i2])
            i2 = i;
    }
    int ans = n;
    if (i1 < i2)
        ans = min({ans, i2 + 1, n - i1, i1 + 1 + n - i2});
    else
        ans = min({ans, i1 + 1, n - i2, i2 + 1 + n - i1});

    return ans;
}