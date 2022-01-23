
int countElements(vector<int> &nums)
{
    int mn = INT_MAX, mx = INT_MIN;
    for (int x : nums)
    {
        mn = min(mn, x);
        mx = max(mx, x);
    }
    int ans = 0;
    for (int x : nums)
        ans += (x != mn && x != mx);
    return ans;
}