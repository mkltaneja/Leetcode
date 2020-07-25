
// O(n)
int minNumberOperations(vector<int> &target)
{
    int n = target.size();
    int total = target[0];
    int separator = target[0];
    for (int i = 1; i < n; i++)
    {
        if (target[i] < separator)
            separator = target[i];
        else
        {
            total += target[i] - separator;
            separator = target[i];
        }
    }
    return total;
}