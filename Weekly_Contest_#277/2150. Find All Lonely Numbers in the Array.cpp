
vector<int> findLonely(vector<int> &nums)
{
    unordered_map<int, int> m;
    for (int x : nums)
        m[x]++;
    vector<int> ans;
    for (auto p : m)
        if (p.second == 1 && !m.count(p.first - 1) && !m.count(p.first + 1))
            ans.push_back(p.first);
    return ans;
}