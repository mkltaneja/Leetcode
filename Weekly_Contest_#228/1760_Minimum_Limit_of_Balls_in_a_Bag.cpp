
int minimumSize(vector<int> &nums, int maxOperations)
{
    int st = 0, end = 1e9 + 7;
    while (st + 1 < end)
    {
        int mid = (st + end) >> 1;
        int i = 0, m = 0;
        for (; i < nums.size() && m <= maxOperations; i++)
            m += (nums[i] - 1) / mid;
        if (m <= maxOperations)
            end = mid;
        else
            st = mid;
    }
    return end;
}