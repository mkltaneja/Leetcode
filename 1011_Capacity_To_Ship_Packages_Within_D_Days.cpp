
int shipWithinDays(vector<int> &weights, int D)
{
    int lo = INT_MIN, hi = 0;
    for (int x : weights)
    {
        hi += x;
        lo = max(lo, x);
    }
    int ans = hi;
    while (lo <= hi)
    {
        int mid = (lo + hi) >> 1;
        int reqd = 1, sumw = 0;
        for (int i = 0; i < weights.size(); i++)
        {
            if (sumw + weights[i] > mid)
            {
                reqd++;
                sumw = 0;
            }
            sumw += weights[i];
        }
        if (reqd > D)
            lo = mid + 1;
        else
        {
            hi = mid - 1;
            ans = mid;
        }
    }
    return ans;
}