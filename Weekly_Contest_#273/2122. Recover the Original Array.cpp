
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