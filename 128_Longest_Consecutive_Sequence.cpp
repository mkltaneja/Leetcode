
int longestConsecutive(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    unordered_map<int, int> m;
    int ans = 1;
    for (int x : nums)
    {
        if (m.count(x))
            continue;
        if (m.count(x - 1) && m.count(x + 1))
        {
            int len = m[x - m[x - 1]] + m[x + m[x + 1]] + 1;
            m[x - m[x - 1]] = len;
            m[x + m[x + 1]] = len;
            m[x] = len;
            ans = max(ans, len);
        }
        else if (m.count(x - 1))
        {
            m[x] = m[x - 1] + 1;
            m[x - m[x - 1]]++;
            ans = max(ans, m[x]);
        }
        else if (m.count(x + 1))
        {
            m[x] = m[x + 1] + 1;
            m[x + m[x + 1]]++;
            ans = max(ans, m[x]);
        }
        else
            m[x] = 1;
    }
    return ans;
}