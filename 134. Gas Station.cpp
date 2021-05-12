
int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
{
    int n = gas.size();
    int deltasum = 0;
    int mn = INT_MAX, mni = 0;
    int gsum = 0, csum = 0;
    for (int i = 0; i < n; i++)
    {
        deltasum += gas[i] - cost[i];
        if (deltasum < mn)
        {
            mn = deltasum;
            mni = i;
        }
        gsum += gas[i];
        csum += cost[i];
    }
    return (gsum < csum) ? -1 : (mni + 1) % n;
}