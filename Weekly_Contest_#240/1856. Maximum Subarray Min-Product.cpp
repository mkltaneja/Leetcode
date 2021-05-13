
#define mod 1000000007
#define ull long long
int maxSumMinProduct(vector<int> &nums)
{
    int n = nums.size();
    vector<ull> psum(n + 1, 0);
    vector<pair<int, int>> m(n);
    // set<pair<ull,int>> m;
    for (int i = 0; i < n; i++)
    {
        psum[i + 1] = psum[i] + nums[i];
        m[i] = {nums[i], i + 1};
        // m.insert({nums[i], i+1});
    }
    sort(m.begin(), m.end());

    set<int> vis;
    vis.insert(0);
    vis.insert(n + 1);
    ull ans = 0;
    for (auto p : m)
    {
        ull x = p.first;
        int i = p.second;
        // auto itr = lower_bound(vis.begin(), vis.end(), i);  --> Takes more time
        auto itr = vis.lower_bound(i); // --> Optimized
        int r = *itr;
        int l = *--itr;
        ans = max(ans, x * (psum[r - 1] - psum[l]));
        vis.insert(i);
    }
    return ans % mod;
}