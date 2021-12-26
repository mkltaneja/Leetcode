
// APPROACH 1 (Brute Force)

int reverse(int x)
{
    int ans = 0;
    while (x)
    {
        ans = ans * 10 + x % 10;
        x /= 10;
    }
    return ans;
}

bool isSameAfterReversals(int num)
{
    int r1 = reverse(num);
    int r2 = reverse(r1);

    return r2 == num;
}