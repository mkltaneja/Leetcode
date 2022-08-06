
long long countBadPairs(vector<int> &nums)
{
    long long ans = 0;
    unordered_map<int, int> mp;
    unsigned long long tot = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        ans += i - mp[nums[i] - i]++;
    }
    return ans;
}