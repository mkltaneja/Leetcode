
int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations)
{
    priority_queue<int> pq;
    int ans = 0;
    for (int i = 0; i < stations.size(); i++)
    {
        while (startFuel < stations[i][0] && !pq.empty())
        {
            startFuel += pq.top();
            pq.pop();
            ans++;
        }
        if (startFuel < stations[i][0])
            return -1;
        pq.push(stations[i][1]);
    }

    while (startFuel < target && !pq.empty())
    {
        startFuel += pq.top();
        pq.pop();
        ans++;
    }

    return (startFuel < target) ? -1 : ans;
}