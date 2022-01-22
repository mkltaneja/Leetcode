
int numberOfArrays(vector<int> &diff, int lower, int upper)
{
    int n = diff.size();
    long l = lower, mn = INT_MAX, mx = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        l += diff[i];
        mn = min(mn, l);
        mx = max(mx, l);
    }

    int st = mn < lower ? (lower + (lower - mn)) : lower;
    int end = mx + (st - lower);
    // cout<<l<<";  "<<mn<<", "<<mx<<" -> "<<st<<", "<<end<<endl;
    return max(end, st) <= upper ? upper - max(end, st) + 1 : 0;
}