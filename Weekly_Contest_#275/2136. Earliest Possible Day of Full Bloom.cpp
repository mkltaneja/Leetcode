
int earliestFullBloom(vector<int> &plantTime, vector<int> &growTime)
{
    int n = plantTime.size();
    vector<vector<int>> pg(n, vector<int>(2));
    for (int i = 0; i < n; i++)
        pg[i] = {plantTime[i], growTime[i]};
    sort(pg.begin(), pg.end(), [](auto const &a, auto const &b)
         { return b[1] < a[1]; });

    int ans = 0;
    int x = 0, l = 0;
    for (int i = 0; i < n; i++)
    {
        l += pg[i][0];
        ans = max(ans, l + pg[i][1]);
    }
    return ans;
}