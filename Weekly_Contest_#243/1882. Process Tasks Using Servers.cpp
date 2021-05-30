
#define f first
#define s second

vector<int> assignTasks(vector<int> &servers, vector<int> &tasks)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> avail;
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> unavail;

    for (int i = 0; i < servers.size(); i++)
        avail.push({servers[i], i});

    vector<int> ans;
    int t = 0;
    for (int i = 0; i < tasks.size(); i++)
    {
        if (avail.empty())
            t = unavail.top().f;
        t = max(t, i + 1);
        while (!unavail.empty() && unavail.top().f == t)
        {
            avail.push({unavail.top().s});
            unavail.pop();
        }
        ans.push_back(avail.top().s);
        unavail.push({t + tasks[i], avail.top()});
        avail.pop();
    }
    return ans;
}