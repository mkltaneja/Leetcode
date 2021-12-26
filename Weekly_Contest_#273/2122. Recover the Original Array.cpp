
// APPROACH 1 (Using Multiset) --> O(n^2 * log(n))

vector<int> recoverArray(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();

    for (int i = 1; i < n; i++)
    {
        int k = nums[i] - nums[0];
        if (k == 0 || (k & 1))
            continue;
        multiset<int> ms(nums.begin(), nums.end());
        vector<int> ans;
        while (!ms.empty())
        {
            int x = *ms.begin();
            ms.erase(ms.begin());

            auto y = ms.find(x + k);
            if (y == ms.end())
                break;

            ans.push_back(x + k / 2);
            ms.erase(y);
        }
        if (ms.empty())
            return ans;
    }
    return {};
}

// APPROACH 2 (Brute Force -- [Using visited array]) --> O(n^2)

vector<int> recoverArray(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int n = nums.size();

    vector<int> ans;
    for (int i = 1; i < n; i++)
    {
        int k = nums[i] - nums[0];
        if (k == 0 || (k & 1))
            continue;

        vector<int> vis(n);
        for (int i = 0; i < n; i++)
        {
            if (vis[i])
                continue;
            for (int j = i + 1; j < n; j++)
            {
                if (!vis[j] && nums[j] == nums[i] + k)
                {
                    vis[i] = 1;
                    vis[j] = 1;
                    break;
                }
            }
            if (!vis[i])
                break;
            ans.push_back(nums[i] + k / 2);
        }
        if (ans.size() == n / 2)
            return ans;
        ans.clear();
    }
    return {};
}