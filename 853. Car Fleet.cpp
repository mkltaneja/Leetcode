
int carFleet(int target, vector<int> &position, vector<int> &speed)
{
    int n = position.size();
    vector<pair<int, int>> posspeed(n);
    for (int i = 0; i < n; i++)
        posspeed[i] = {position[i], speed[i]};
    sort(posspeed.begin(), posspeed.end());
    vector<double> time(n);
    for (int i = 0; i < n; i++)
    {
        if (posspeed[i].second == 0)
            time[i] = DBL_MAX;
        else
            time[i] = (1.0 * (target - posspeed[i].first) / posspeed[i].second);
    }

    int fleets = 0;
    double ltime = 0;
    for (int i = n - 1; i >= 0; i--)
        if (time[i] > ltime)
            ltime = time[i], fleets++;
    return fleets;
}