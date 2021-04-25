
#define ull unsigned long long
int maxFrequency(vector<int> &a, int k)
{
    int n = a.size();
    sort(a.begin(), a.end());
    int ans = 0;
    ull csum = 0;
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        csum += a[i];
        while ((ull)a[i] * (i - j + 1) - csum > k)
            csum -= a[j++];
        ans = max(ans, (i - j + 1));
    }
    return ans;
}