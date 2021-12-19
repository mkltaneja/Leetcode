
int kIncreasing(vector<int> &arr, int k)
{
    int n = arr.size();
    int ans = 0;
    for (int i = 0; i < k; i++)
    {
        vector<int> lis;
        int sz = 0;
        for (int j = i; j < n; j += k)
        {
            sz++;
            int x = upper_bound(lis.begin(), lis.end(), arr[j]) - lis.begin();
            if (x == lis.size())
                lis.push_back(arr[j]);
            else
                lis[x] = arr[j];
        }
        ans += sz - lis.size();
    }

    return ans;
}