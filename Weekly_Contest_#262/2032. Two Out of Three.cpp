
vector<int> twoOutOfThree(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3)
{
    unordered_set<int> s1, s2;
    unordered_map<int, int> m;
    for (int i = 0; i < nums1.size(); i++)
    {
        s1.insert(nums1[i]);
        m[nums1[i]] = 1;
    }
    for (int i = 0; i < nums2.size(); i++)
    {
        m[nums2[i]] = s1.count(nums2[i]) + 1;
        s2.insert(nums2[i]);
    }
    for (int i = 0; i < nums3.size(); i++)
        m[nums3[i]] = s1.count(nums3[i]) + s2.count(nums3[i]) + 1;

    vector<int> ans;
    for (auto p : m)
        if (p.second >= 2)
            ans.push_back(p.first);
    return ans;
}