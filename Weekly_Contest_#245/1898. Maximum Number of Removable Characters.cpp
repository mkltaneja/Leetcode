
int maximumRemovals(string s, string p, vector<int> &removable)
{
    int si = 0, ei = removable.size();
    vector<int> rem(s.size(), 0);
    while (si < ei)
    {
        int mid = (si + ei + 1) >> 1;

        for (int i = 0; i < mid; i++)
            rem[removable[i]] = 1;

        int j = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (rem[i])
                continue;
            if (j < p.size() && s[i] == p[j])
                j++;
        }

        for (int i = 0; i < mid; i++)
            rem[removable[i]] = 0;

        if (j == p.size())
            si = mid;
        else
            ei = mid - 1;
    }
    return si;
}