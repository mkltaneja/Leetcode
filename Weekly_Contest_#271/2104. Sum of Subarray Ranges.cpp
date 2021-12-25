
// APPROACH 1 (Brute Force) --> O(n^2)

long long subArrayRanges(vector<int> &nums)
{
    int n = nums.size();
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
        int mx = nums[i], mn = nums[i];
        for (int j = i + 1; j < n; j++)
        {
            mx = max(mx, nums[j]);
            mn = min(mn, nums[j]);

            ans += (mx - mn);
        }
    }

    return ans;
}