
// DAY 2 (Two Sum)=========================================================================

vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> m;
    for (int i = 0; i < nums.size(); i++)
    {
        if (m.count(target - nums[i]))
            return {m[target - nums[i]], i};
        m[nums[i]] = i;
    }
    return {};
}

// DAY 3 (Subsets 2)===============================================================================================

void subsets(int i, vector<int> &nums, set<vector<int>> &st, vector<vector<int>> &ans, vector<int> ss)
{
    if (i == nums.size())
    {
        if (!st.count(ss))
        {
            ans.push_back(ss);
            st.insert(ss);
        }
        return;
    }
    subsets(i + 1, nums, st, ans, ss);
    ss.push_back(nums[i]);
    subsets(i + 1, nums, st, ans, ss);
    ss.pop_back();
}

vector<vector<int>> subsetsWithDup(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    set<vector<int>> st;
    vector<vector<int>> ans;
    subsets(0, nums, st, ans, {});
    return ans;
}