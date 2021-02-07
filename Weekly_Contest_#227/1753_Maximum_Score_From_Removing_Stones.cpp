
int maximumScore(int a, int b, int c)
{
    int d[3] = {a, b, c};
    sort(d, d + 3);
    int cnt = 0;
    while (d[1])
    {
        cnt++;
        if (d[0])
            d[0]--;
        else
            d[1]--;
        d[2]--;
        sort(d, d + 3);
    }
    return cnt;
}