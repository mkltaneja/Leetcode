
#define f first
#define s second
vector<double> getCollisionTimes(vector<vector<int>> &cars)
{
    int n = cars.size();
    vector<double> ans(n, -1);
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq;
    set<int> a;
    for (int i = 0; i < n - 1; i++)
    {
        a.insert(i);
        if (cars[i][1] > cars[i + 1][1])
            pq.push({(cars[i + 1][0] - cars[i][0]) * 1.0 / (cars[i][1] - cars[i + 1][1]), {i, i + 1}});
    }
    a.insert(n - 1);

    while (!pq.empty())
    {
        auto tp = pq.top();
        pq.pop();
        double t = tp.f;
        int i = tp.s.f, j = tp.s.s;
        // cout<<i<<" "<<j<<" --> "<<t<<endl;

        if (a.find(i) == a.end() || a.find(j) == a.end())
            continue;
        ans[i] = t;
        auto it = a.find(i);
        if (it == a.begin())
            a.erase(i);
        else
        {
            it--;
            a.erase(i);
            auto it2 = next(it);
            if (cars[*it][1] > cars[*it2][1])
                pq.push({(cars[*it2][0] - cars[*it][0]) * 1.0 / (cars[*it][1] - cars[*it2][1]), {*it, *it2}});
        }
    }
    cout << endl;
    return ans;
}