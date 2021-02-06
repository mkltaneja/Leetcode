
int sumOfUnique(vector<int> &nums)
{
    vector<int> un(101, -1);
    int sum = 0;
    for (int x : nums)
    {
        if (un[x] == -1)
        {
            un[x] = x;
            sum += x;
        }
        else
        {
            if (un[x] == 0)
                continue;
            un[x] = 0;
            sum -= x;
        }
    }
    return sum;
}