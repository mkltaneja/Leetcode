
int minimumBuckets(string street)
{
    int n = street.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (street[i] == 'H')
        {
            if (!i && n == 1)
                return -1;
            if (!i && street[i + 1] == 'H')
                return -1;
            if (i == n - 1 && street[i - 1] == 'H')
                return -1;
            if (i && i != n - 1 && street[i - 1] == 'H' && street[i + 1] == 'H')
                return -1;
            if (i && street[i - 1] == 'b' || i < n - 1 && street[i + 1] == 'b')
                continue;
            if (i == n - 1 && street[i - 1] == '.')
                street[i - 1] = 'b';
            else if (street[i + 1] == '.')
                street[i + 1] = 'b';
            ans++;
        }
    }
    return ans;
}