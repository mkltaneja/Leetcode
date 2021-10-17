
int countMaxOrSubsets(vector<int> &nums)
{
    vector<int> v;
    int n = nums.size();
    int mx = 0, cnt = 0;
    for (int i = 0; i < (1 << n); i++)
    {
        int x = i, y = 0;
        int m = 0;
        while (x)
        {
            if (x & 1)
                m |= nums[y];
            x >>= 1;
            y++;
        }
        v.push_back(m);
        if (m > mx)
        {
            mx = m;
            cnt = 1;
        }
        else if (mx == m)
            cnt++;
    }
    return cnt;
}