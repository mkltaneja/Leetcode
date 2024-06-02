
// APPROACH 1 (Making pairs of all y for a particular x and then find area by traversing in each x)====================================================

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


// APPROACH 2 (Traversing through the corners)===============================================================================================

// [OPTIMIZED]

// Time Complexity = O(n + n^2)
// Space Complexity = O(n)

int minAreaRect(vector<vector<int>>& points) 
{
    int size = points.size();
    unordered_map<int, unordered_set<int>> xMap;
    int minArea = INT_MAX;
    for(int idx = 0; idx < size; idx++)
    {
        int x = points[idx][0], y = points[idx][1];
        xMap[x].insert(y);
    }
    for(int idx1 = 0; idx1 < size; idx1++)
    {
        for(int idx2 = idx1+1; idx2 < size; idx2++)
        {
            int x1 = points[idx1][0], y1 = points[idx1][1];
            int x2 = points[idx2][0], y2 = points[idx2][1];
            if(x1 == x2 || y1 == y2)
                continue;
            if(xMap[x1].count(y2) && xMap[x2].count(y1))
                minArea = min(minArea, abs(x1 - x2) * abs(y1 - y2));
        }
    }
    return minArea == INT_MAX? 0 : minArea;
}
