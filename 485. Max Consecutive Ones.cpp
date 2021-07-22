
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int ans = 0;
    int i = 0, n = nums.size();
    while (i < n)
    {
        int j = i;
        while (j < n && nums[j] == 1)
            j++;
        ans = max(ans, j - i);
        while (j < n && nums[j] == 0)
            j++;
        i = j;
    }
    return ans;
}