
vector<int> maxScoreIndices(vector<int> &nums)
{
    int n = nums.size();

    int o = 0, z = 0;
    for (int i = 0; i < n; i++)
        o += nums[i];

    vector<int> ans;
    int mx = -1;

    for (int i = 0; i <= n; i++)
    {
        int x = o + z;
        if (x >= mx)
        {
            if (x > mx)
                ans.clear();
            ans.push_back(i);
            mx = x;
        }
        if (i == n)
            break;
        z += !nums[i];
        o -= nums[i];
    }

    return ans;
}