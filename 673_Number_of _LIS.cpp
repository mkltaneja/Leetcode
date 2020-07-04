int findNumberOfLIS(vector<int> &nums)
{
    int n = nums.size();
    vector<int> len(n, 1);
    vector<int> count(n, 1);

    int omax = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (nums[j] < nums[i])
            {
                if (len[j] + 1 > len[i])
                {
                    len[i] = len[j] + 1;
                    count[i] = count[j];
                }
                else if (len[j] + 1 == len[i])
                    count[i] += count[j];
            }
        }
    }

    int maxlen = 0;
    int maxcount = 0;
    for (int i = 0; i < n; i++)
    {
        if (len[i] > maxlen)
        {
            maxlen = len[i];
            maxcount = count[i];
        }
        else if (len[i] == maxlen)
            maxcount += count[i];
    }

    return maxcount;
}