
vector<vector<int>> intervalIntersection(vector<vector<int>> &firstList, vector<vector<int>> &secondList)
{
    vector<vector<int>> ans;
    int i = 0, j = 0, n = firstList.size(), m = secondList.size();
    while (i < n && j < m)
    {
        int stmax = max(firstList[i][0], secondList[j][0]);
        int endmin = min(firstList[i][1], secondList[j][1]);

        if (stmax <= endmin)
            ans.push_back({stmax, endmin});
        if (firstList[i][1] < secondList[j][1])
            i++;
        else
            j++;
    }
    return ans;
}