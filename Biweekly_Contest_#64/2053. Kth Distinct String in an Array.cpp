
#define f first
#define s second
string kthDistinct(vector<string> &arr, int k)
{
    unordered_map<string, pair<int, int>> m;
    for (int i = 0; i < arr.size(); i++)
        m[arr[i]] = {m[arr[i]].f + 1, i};

    vector<pair<int, string>> ans;
    for (auto p : m)
    {
        // cout<<p.f<<" -> "<<p.s.f<<", "<<p.s.s<<endl;
        if (p.s.f == 1)
            ans.push_back({p.s.s, p.f});
    }
    sort(ans.begin(), ans.end());
    // cout<<endl;
    return ans.size() < k ? "" : ans[k - 1].s;
}