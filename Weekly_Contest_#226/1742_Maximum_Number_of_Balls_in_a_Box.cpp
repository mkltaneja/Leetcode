
int countBalls(int lowLimit, int highLimit)
{
    vector<int> box(50, 0);
    int maxballs = 0;
    for (int i = lowLimit; i <= highLimit; i++)
    {
        int x = i, sum = 0;
        while (x)
        {
            sum += x % 10;
            x /= 10;
        }
        maxballs = max(maxballs, ++box[sum]);
    }
    return maxballs;
}