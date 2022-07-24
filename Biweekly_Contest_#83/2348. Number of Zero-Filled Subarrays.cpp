
long long zeroFilledSubarray(vector<int> &nums)
{
    int i = 0, li = -1;
    long long ans = 0;
    while (i < nums.size())
    {
        if (nums[i] == 0)
            ans += i++ - li;
        else
            li = i++;
    }
    return ans;
}