
int minswaps(int n, int x, int cnt, vector<int> &arr)
{
    if (cnt == 0 || cnt == n)
        return 0;
    int y = 0;
    int ans = n;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
            y++;
        if (i + 1 > cnt)
            y -= (arr[i - cnt] == x);
        if (i + 1 >= cnt)
            ans = min(ans, cnt - y);
    }
    return ans;
}

int minSwaps(vector<int> &nums)
{
    int n = nums.size();
    int o = 0;
    for (int i = 0; i < n; i++)
        o += nums[i];

    return min(minswaps(n, 0, n - o, nums), minswaps(n, 1, o, nums));
}