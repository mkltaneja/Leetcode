
long long minimumReplacement(vector<int> &nums)
{
    int n = nums.size();
    long long ans = 1;
    long long prev = nums[n - 1];

    for (int i = n - 2; i >= 0; i--)
    {
        long long x = (nums[i] + prev - 1) / prev;
        ans += x;
        prev = nums[i] / x;
    }

    return ans - n;
}