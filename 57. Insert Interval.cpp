
vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
{
    int n = intervals.size();
    int st = newInterval[0], end = newInterval[1];
    vector<vector<int>> ans;
    int i = 0;
    while (i < n && intervals[i][1] < st)
        ans.push_back({intervals[i][0], intervals[i++][1]});

    while (i < n && intervals[i][0] <= end)
    {
        st = min(st, intervals[i][0]);
        end = max(end, intervals[i++][1]);
    }
    ans.push_back({st, end});

    while (i < n)
        ans.push_back({intervals[i][0], intervals[i++][1]});

    return ans;
}