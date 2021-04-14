
int firstMissingPositive(vector<int> &nums)
{
    int n = nums.size();
    int ans = n + 1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == i + 1)
            continue;
        if (nums[i] < 1 || nums[i] > n)
            continue;
        if (nums[i] == nums[nums[i] - 1])
            continue;
        swap(nums[i], nums[nums[i] - 1]);
        i--;
    }
    for (int i = 0; i < n; i++)
        if (nums[i] != i + 1)
            return i + 1;
    return n + 1;
}