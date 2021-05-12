
int mod = 1000000007;
int sumSubseqWidths(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());
    int ans = 0;
    long minsum = 0, maxsum = 0;
    long p = 1;
    for (int i = 0; i < n; i++)
    {
        ans = (ans + ((nums[i] * p) % mod - (nums[n - i - 1] * p) % mod) + mod) % mod;
        p = (p * 2) % mod;
    }
    return ans;
}