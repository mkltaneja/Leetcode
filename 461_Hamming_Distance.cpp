int hammingDistance(int x, int y)
{
    int n = x ^ y;
    // cout<<n;
    int count = 0;
    while (n)
    {
        // cout<<(n|1)<<" ";
        if (n & 1)
            count++;
        n >>= 1;
    }
    return count;
}