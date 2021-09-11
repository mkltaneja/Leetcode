
int numWays(int n, int k)
{
    int same = 0, diff = k;
    for (int i = 2; i <= n; i++)
    {
        int temp = same;
        same = diff;
        diff = (diff + temp) * (k - 1);
    }
    return same + diff;
}