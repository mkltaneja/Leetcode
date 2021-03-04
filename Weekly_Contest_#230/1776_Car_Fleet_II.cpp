
// APPROACH 1 (Using Priority queue) --> >O(n*logn)
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

// APPROACH 2 (OPTIMIZED Brute Force) --> <<O(n^2) ~= O(n)

vector<double> getCollisionTimes(vector<vector<int>> &cars)
{
    int n = cars.size();
    vector<double> ans(n, -1);

    for (int i = n - 1; i >= 0; i--)
    {
        int p1 = cars[i][0];
        int s1 = cars[i][1];
        // cout<<i<<": ";
        for (int j = i - 1; j >= 0; j--)
        {
            int p2 = cars[j][0];
            int s2 = cars[j][1];
            if (s2 <= s1)
                break;
            double t = 1.0 * (p1 - p2) / (s2 - s1);
            if (ans[j] == -1 || t < ans[j])
                ans[j] = t;
            else
                break;
            // cout<<j<<"   "<<t<<endl;
        }
    }
    return ans;
}