
// APPROACH 1 (Making pairs of all y for a particular x and then find area by traversing in each x)

// Time Complexity = O(n*logn + n^2)
// Space Complexity = O(n + n^2)

int minAreaRect(vector<vector<int>>& points) 
{
    int size = points.size();
    map<int,vector<int>> xMap;
    map<pair<int, int>, int> pairs;
    int minArea = INT_MAX;
    for(int idx = 0; idx < size; idx++)
    {
        int x = points[idx][0], y = points[idx][1];
        xMap[x].push_back(y);
    }
    for(auto p : xMap)
    {
        for(int i = 0; i < p.second.size(); i++)
        {
            for(int j = i+1; j < p.second.size(); j++)
            {
                int minY = min(p.second[i], p.second[j]);
                int maxY = max(p.second[i], p.second[j]);
                if(pairs.count({minY, maxY}))
                    minArea = min(minArea, (maxY - minY) * (p.first - pairs[{minY, maxY}]));
                pairs[{minY, maxY}] = p.first;
            }
        }
    }
    return minArea == INT_MAX? 0 : minArea;
}
