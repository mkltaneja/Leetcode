// DAY 1 (Arranging coins)=======================================

// Brute force
// O(sqrt(n))
int arrangeCoins(int n)
{
    int i = 1, count = 0;
    while ((n - i) >= 0)
    {
        count++;
        n -= i;
        i++;
    }
    return count;
}

// O(logn)
int arrangeCoins(int n)
{
    int si = 0, ei = n;
    while (si <= ei)
    {
        long int mid = si + (ei - si) / 2;
        if ((mid * (mid + 1)) / 2 == n)
            return mid;
        else if ((mid * (mid + 1)) / 2 < n)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return ei;
}

///////////////////OR////////////////////\

// O(1)
int arrangeCoins(int n)
{
    return (int)(-0.5 + sqrt(0.25 + (long int)2 * n));
}