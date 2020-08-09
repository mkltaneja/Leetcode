
int maxNonOverlapping(vector<int>& nums, int target)
{
    int ps = 0, ans = 0;
    set<int> s;
    s.insert(0);
    for (int i : nums)
    {
        ps += i;
        if (s.find(ps - target) != s.end())
        {
            ans++;
            s.clear();
        }
        s.insert(ps);
    }
    return ans;
}