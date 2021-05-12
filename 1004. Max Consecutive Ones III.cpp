
int longestOnes(vector<int> &nums, int k)
{
    int z = 0;
    int ans = 0;
    int i = 0, j = 0;
    while (i < nums.size())
    {
        if (nums[i] == 0)
        {
            if (k == 0)
            {
                i++, j = i;
                continue;
            }
            z++;
        }
        while (j < i && z == k + 1)
        {
            if (nums[j] == 0)
                z--;
            j++;
        }
        ans = max(ans, i - j + 1);
        i++;
    }
    return ans;
}