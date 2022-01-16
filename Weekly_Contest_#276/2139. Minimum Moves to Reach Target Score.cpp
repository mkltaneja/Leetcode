
int minMoves(int target, int maxDoubles)
{
    int ans = 0;
    while (target > 1)
    {
        if (maxDoubles == 0)
            return ans + (target - 1);

        ans += target & 1;
        target >>= 1;
        maxDoubles--;
        ans++;
    }
    return ans;
}