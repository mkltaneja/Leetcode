
int maximumProduct(vector<int> &nums)
{
    int mn1 = INT_MAX, mn2 = INT_MAX;
    int mx1 = INT_MIN, mx2 = INT_MIN, mx3 = INT_MIN;
    for (int n : nums)
    {
        if (n < mn1)
        {
            mn2 = mn1;
            mn1 = n;
        }
        else if (n < mn2)
            mn2 = n;
        if (n > mx1)
        {
            mx3 = mx2;
            mx2 = mx1;
            mx1 = n;
        }

        else if (n > mx2)
        {
            mx3 = mx2;
            mx2 = n;
        }
        else if (n > mx3)
            mx3 = n;
    }
    return max(mn1 * mn2 * mx1, mx1 * mx2 * mx3);
}