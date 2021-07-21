
int subarraySum(vector<int> &nums, int k)
{
    int n = nums.size();
    vector<int> ps(n);
    for (int i = 0; i < n; i++)
        ps[i] = nums[i] + (i ? ps[i - 1] : 0);

    unordered_map<int, int> m;
    m[0] = 1;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        ans += m[ps[i] - k];
        m[ps[i]]++;
    }

    return ans;
}