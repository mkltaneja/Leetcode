
// APPROACH 1 (Taking max and min vals)

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

// APPROACH 2 (Range Difference)

int numberOfArrays(vector<int> &diff, int lower, int upper)
{
    int n = diff.size();
    long l = 0, r = 0;
    long curr = 0;
    for (int x : diff)
    {
        curr += x;
        if (curr < l)
            l = curr;
        else if (curr > r)
            r = curr;
    }
    long myRange = r - l, xRange = upper - lower;
    return myRange <= xRange ? xRange - myRange + 1 : 0;
}