
vector<int> productExceptSelf(vector<int> &nums)
{
    int n = nums.size();
    vector<int> prefprod(n);
    vector<int> suffprod(n);
    prefprod[0] = nums[0];
    suffprod[n - 1] = nums[n - 1];
    for (int i = 1; i < n; i++)
        prefprod[i] = prefprod[i - 1] * nums[i];
    for (int i = n - 2; i >= 0; i--)
        suffprod[i] = suffprod[i + 1] * nums[i];

    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
        int pref = (i == 0) ? 1 : prefprod[i - 1];
        int suff = (i == n - 1) ? 1 : suffprod[i + 1];
        ans[i] = pref * suff;
    }
    return ans;
}