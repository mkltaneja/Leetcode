
int maxChunksToSorted(vector<int> &arr)
{
    int ans = 0;
    int i = 0;
    while (i < arr.size())
    {
        int mx = arr[i];
        while (i < arr.size() && i <= mx)
            mx = max(mx, arr[i++]);
        ans++;
    }
    return ans;
}