
vector<int> numberOfPairs(vector<int> &nums)
{
    int e = 0, o = 0;
    unordered_map<int, int> mp;
    for (int x : nums)
        mp[x]++;
    for (auto p : mp)
    {
        e += p.second / 2;
        o += p.second & 1;
    }

    return {e, o};
}