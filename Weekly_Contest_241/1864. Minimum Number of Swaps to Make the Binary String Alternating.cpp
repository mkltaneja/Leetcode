

int swaps(int x, string &s)
{
    string a = "";
    int ans = 0;
    for (int i = 0; i < s.size(); i++)
    {
        ans += ((s[i] - '0') ^ x);
        x ^= 1;
    }
    return ans / 2;
}

int minSwaps(string s)
{
    int o = 0, z = 0;
    for (char c : s)
    {
        if (c == '0')
            z++;
        else
            o++;
    }
    if (min(o, z) != s.size() / 2)
        return -1;
    if (o == z)
        return min(swaps(0, s), swaps(1, s));
    return (o > z) ? swaps(1, s) : swaps(0, s);
}