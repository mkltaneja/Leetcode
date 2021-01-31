
#define f first
#define s second
vector<int> restoreArray(vector<vector<int>> &adjacentPairs)
{
    unordered_map<int, vector<int>> lr;
    for (auto p : adjacentPairs)
    {
        lr[p[0]].push_back(p[1]);
        lr[p[1]].push_back(p[0]);
    }
    vector<int> ans(adjacentPairs.size() + 1);
    int k = 0;
    for (auto p : lr)
    {
        if (p.second.size() == 1)
        {
            ans[k++] = p.first;
            ans[k++] = p.second[0];
            break;
        }
    }
    // if(k == ans.size())
    //     return ans;
    int num = ans[k - 1];
    while (k < ans.size())
    {
        auto itr = lr.find(num);
        if (itr->s.size() == 1)
        {
            ans[k++] = itr->s[0];
            return ans;
        }
        if (ans[k - 2] != itr->s[0])
            ans[k++] = itr->s[0];
        else
            ans[k++] = itr->s[1];
        num = ans[k - 1];
    }
    return ans;
}