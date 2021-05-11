
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> pmax(n), smax(n);
    pmax[0] = nums[0], smax[n - 1] = nums[n - 1];
    for (int i = 1, j = n - 2; i < n; i++, j--)
    {
        if (i % k == 0)
            pmax[i] = nums[i];
        else
            pmax[i] = max(pmax[i - 1], nums[i]);

        if (j % k == k - 1)
            smax[j] = nums[j];
        else
            smax[j] = max(smax[j + 1], nums[j]);
    }

    vector<int> ans(n - k + 1);
    for (int i = 0; i < n - k + 1; i++)
        ans[i] = max(smax[i], pmax[i + k - 1]);

    return ans;
}