
// APPROACH 1 (Brute Force) -> O(number of digits)

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

// APPROACH 2 (check for 0 at unit place for a non zero value) -> O(1)

bool isSameAfterReversals(int num)
{
    return !num || num % 10;
}