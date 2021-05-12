
// APPROACH 1 (Acquire - Release) --> O(n*m*log(n*m))
// AC

#define f first
#define s second
vector<int> smallestRange(vector<vector<int>> &nums)
{
    int k = nums.size();
    vector<pair<int, int>> mix;
    for (int i = 0; i < nums.size(); i++)
        for (int j = 0; j < nums[i].size(); j++)
            mix.push_back({nums[i][j], i});
    sort(mix.begin(), mix.end());

    unordered_map<int, int> m;
    int j = 0;
    vector<int> ans = {-1, INT_MAX - 1};
    for (int i = 0; i < mix.size(); i++)
    {
        m[mix[i].s]++;
        // cout<<mix[i].s<<" --> "<<m.size()<<endl;
        while (m.size() == k)
        {
            if ((mix[i].f - mix[j].f) < (ans[1] - ans[0]))
                ans[0] = mix[j].f, ans[1] = mix[i].f;
            if (--m[mix[j].s] == 0)
                m.erase(mix[j].s);
            j++;
        }
    }
    return ans;
}

// APPROACH 2 (Adding single element from every k list in the min priority_queue then comparing "max - min" every time) --> O(n*m*log(k))

#define f first
#define s second
vector<int> smallestRange(vector<vector<int>> &nums)
{
    int k = nums.size();
    priority_queue<pair<int, pair<int, int>>,
                   vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>>
        pq;
    int mx = INT_MIN;
    for (int i = 0; i < k; i++)
    {
        pq.push({nums[i][0], {i, 0}});
        mx = max(mx, nums[i][0]);
    }

    vector<int> ans = {-1, INT_MAX - 1};
    while (!pq.empty())
    {
        auto top = pq.top();
        pq.pop();

        if ((mx - top.f) < (ans[1] - ans[0]))
            ans[0] = top.f, ans[1] = mx;

        if (top.s.s + 1 < nums[top.s.f].size())
        {
            pq.push({nums[top.s.f][top.s.s + 1], {top.s.f, top.s.s + 1}});
            mx = max(mx, nums[top.s.f][top.s.s + 1]);
        }
        else
            break;
    }
    return ans;
}