
vector<int> smallestTrimmedNumbers(vector<string> &nums, vector<vector<int>> &queries)
{
    vector<int> ans(queries.size());
    for (int j = 0; j < queries.size(); j++)
    {
        vector<int> q = queries[j];
        vector<pair<string, int>> tmp(nums.size());
        for (int i = 0; i < nums.size(); i++)
        {
            tmp[i] = {nums[i].substr(nums[i].size() - q[1]), i};
        }
        sort(tmp.begin(), tmp.end());
        ans[j] = tmp[q[0] - 1].second;
    }

    return ans;
}