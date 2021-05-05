
int reachNumber(int target)
{
    if (target < 0)
        target = -target;
    int ans = 0;
    int n = 0, i = 1;
    while (n < target)
    {
        n += i++;
        ans++;
    }
    int diff = (target - n);
    if (diff % 2 == 0)
        return ans;
    else if (i & 1)
        return ans + 1;
    else
        return ans + 2;
}