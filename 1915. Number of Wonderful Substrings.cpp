
long long wonderfulSubstrings(string word)
{
    long long ans = 0;
    unordered_map<int, int> mconf;
    int xr = 0; // all even
    mconf[0] = 1;

    for (char c : word)
    {
        xr ^= (1 << (c - 'a'));
        ans += mconf[xr];
        for (int i = 0; i < 10; i++)
            ans += mconf[xr ^ (1 << i)];
        mconf[xr]++;
    }

    return ans;
}