
vector<vector<int>> merge(vector<vector<int>> &intervals)
{
    sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    int st = intervals[0][0], end = intervals[0][1];
    for (int i = 1; i < intervals.size(); i++)
    {
        if (intervals[i][0] > end)
        {
            ans.push_back({st, end});
            st = intervals[i][0];
        }
        end = max(end, intervals[i][1]);
    }
    ans.push_back({st, end});

    return ans;
}