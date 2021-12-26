
void solve(vector<long long> &ans, vector<int> arr)
{
    long long p = 0, s = 0;
    for (int x : arr)
        s += x;

    long long m = 0, ps = 0;
    for (int x : arr)
    {
        ans[x] = s - ((arr.size() - m) * x);
        ans[x] += (m++) * x - ps;
        ps += x;
        s -= x;
    }
}

vector<long long> getDistances(vector<int> &arr)
{
    int n = arr.size();
    vector<long long> ans(n);

    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];

    unordered_map<int, vector<int>> m;
    for (int i = 0; i < n; i++)
        m[arr[i]].push_back(i);

    for (auto &p : m)
    {
        sort(p.s.begin(), p.s.end());
        solve(ans, p.s);
    }

    return ans;
}