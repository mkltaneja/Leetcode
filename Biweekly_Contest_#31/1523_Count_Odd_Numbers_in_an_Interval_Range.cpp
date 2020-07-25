// O(1)
int countOdds(int low, int high)
{
    if (low & 1)
        low--;
    if (high & 1)
        high++;
    return (high - low) / 2;
}