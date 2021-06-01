
int dominantIndex(vector<int> &nums)
{
    int n = nums.size();
    if (n == 1)
        return 0;
    int mx = -1, mx1 = -1, ans = -1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] > mx)
        {
            mx1 = mx;
            mx = nums[i];
            ans = i;
        }
        else if (nums[i] > mx1)
            mx1 = nums[i];
    }
    return (mx >= 2 * mx1) ? ans : -1;
}