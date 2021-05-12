
int findMaxConsecutiveOnes(vector<int> &nums)
{
    int i = 0, j = 0;
    int z = 0;
    int ans = 0;
    while (i < nums.size())
    {
        if (nums[i] == 0)
            z++;
        while (z == 2)
        {
            if (j < i && nums[j] == 0)
                z--;
            j++;
        }
        ans = max(ans, i - j + 1);
        i++;
    }
    return ans;
}