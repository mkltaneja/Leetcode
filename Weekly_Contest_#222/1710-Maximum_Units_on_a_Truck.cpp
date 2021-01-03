
int maximumUnits(vector<vector<int>> &boxTypes, int truckSize)
{
    sort(boxTypes.begin(), boxTypes.end(), [](const vector<int> &a, const vector<int> &b) {
        return (a[1] == b[1]) ? (a[0] < b[0]) : (a[1] > b[1]);
    });
    int ans = 0, i = 0;
    while (i < boxTypes.size() && truckSize > 0)
    {
        ans += (min(boxTypes[i][0], truckSize) * boxTypes[i][1]);
        truckSize -= boxTypes[i++][0];
    }
    return ans;
}