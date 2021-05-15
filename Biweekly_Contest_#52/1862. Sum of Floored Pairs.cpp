
#define mod 1000000007
int sumOfFlooredPairs(vector<int> &nums)
{
    int n = nums.size();
    vector<int> cnt(2e5 + 1, 0), psum(2e5 + 1, 0);
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++)
        cnt[nums[i]]++;
    for (int i = 1; i <= 2e5; i++)
        psum[i] = psum[i - 1] + cnt[i];

    long ans = 0;
    for (int i = 1; i <= 1e5; i++)
    {
        if (cnt[i])
        {
            for (int j = i; j <= 1e5; j += i)
            {
                ans += ((psum[i + j - 1] - psum[j - 1]) % mod * (j / i) % mod * cnt[i] % mod) % mod;
                ans %= mod;
            }
        }
    }
    return ans % mod;
}