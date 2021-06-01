int maxChunksToSorted(vector<int> &arr)
{
    int n = arr.size();
    vector<int> mini(n);
    int mn = INT_MAX;
    for (int i = n - 1; i >= 0; i--)
    {
        mn = min(mn, arr[i]);
        mini[i] = mn;
    }
    int ans = 0;
    int i = 0;
    while (i < n)
    {
        int mx = arr[i++];
        while (i < n && mx > mini[i])
            mx = max(mx, arr[i++]);
        ans++;
    }
    return ans;
}