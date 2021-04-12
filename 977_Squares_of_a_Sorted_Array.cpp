vector<int> sortedSquares(vector<int> &nums)
{
    vector<int> ans(nums.size());
    int i = 0, j = nums.size() - 1, k = j;
    while (i <= j)
    {
        if (abs(nums[i]) > abs(nums[j]))
            ans[k--] = nums[i] * nums[i++];
        else
            ans[k--] = nums[j] * nums[j--];
    }
    return ans;
}