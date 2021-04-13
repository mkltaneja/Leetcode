
int nextGreaterElement(int n)
{
    string s = to_string(n);
    int i = s.size() - 1;
    while (i > 0)
    {
        if (s[i - 1] < s[i])
        {
            int j = i, idx = j;
            int g = s[j];
            while (j < s.size())
            {
                if (s[j] > s[i - 1] && s[j] <= g)
                {
                    g = s[j];
                    idx = j;
                }
                j++;
            }
            swap(s[i - 1], s[idx]);
            reverse(s.begin() + i, s.end());
            break;
        }
        i--;
    }
    long ans = stol(s);
    // cout<<ans<<endl;
    return (ans == n || ans > INT_MAX) ? -1 : ans;
}