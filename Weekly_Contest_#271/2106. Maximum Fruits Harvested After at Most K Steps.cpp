
int maxFruits(int x, int k, int n, vector<vector<int>> &fruits, int start)
{
    if (fruits[x][0] != start)
        k -= abs(fruits[x][0] - start);

    vector<int> psum(n);
    for (int i = 0; i < n; i++)
        psum[i] += fruits[i][1] + (i ? psum[i - 1] : 0);

    int maxfruits = 0;

    for (int i = x; i >= 0; i--) // left to right
    {
        int avail = k - 2 * (fruits[x][0] - fruits[i][0]);
        if (avail < 0)
            break;
        int lfruits = psum[x] - (i ? psum[i - 1] : 0);
        int si = x, ei = n - 1;
        int r = x;
        while (si <= ei)
        {
            int m = si + (ei - si) / 2;
            if (fruits[m][0] - fruits[x][0] <= avail)
                r = m, si = m + 1;
            else
                ei = m - 1;
        }
        int rfruits = psum[r] - psum[x];

        maxfruits = max(maxfruits, lfruits + rfruits);
    }

    for (int i = x; i < n; i++) // right to left
    {
        int avail = k - 2 * (fruits[i][0] - fruits[x][0]);
        if (avail < 0)
            break;
        int rfruits = psum[i] - (x ? psum[x - 1] : 0);
        int si = 0, ei = x - 1;
        int l = x;
        while (si <= ei)
        {
            int m = si + (ei - si) / 2;
            if (fruits[x][0] - fruits[m][0] <= avail)
                l = m, ei = m - 1;
            else
                si = m + 1;
        }
        int lfruits = (x ? psum[x - 1] : 0) - (l ? psum[l - 1] : 0);
        maxfruits = max(maxfruits, lfruits + rfruits);
    }

    return maxfruits;
}

int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k)
{
    int n = fruits.size();
    int si = 0, ei = n - 1;
    int x = 0;
    while (si <= ei)
    {
        int m = si + (ei - si) / 2;
        if (fruits[m][0] <= startPos)
            x = m, si = m + 1;
        else
            ei = m - 1;
    }

    if (startPos == fruits[x][0])
        return maxFruits(x, k, n, fruits, startPos);
    else
        return max(maxFruits(x, k, n, fruits, startPos), (x + 1 < n ? maxFruits(x + 1, k, n, fruits, startPos) : 0));
}