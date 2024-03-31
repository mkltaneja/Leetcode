
// Time Complexity = O(n*logn)
// Space Complexity = O(n)

class Solution {
public:
    int minimumDistance(vector<vector<int>>& points) 
    {
        multiset<int> dist1, dist2;
        int minDist = INT_MAX;
        for(vector<int> &point : points)
        {
            int x = point[0], y = point[1];
            dist1.insert(x + y);
            dist2.insert(x - y);
        }

        for(vector<int> &point : points)
        {
            int x = point[0], y = point[1];
            dist1.erase(dist1.find(x + y));
            dist2.erase(dist2.find(x - y));
            minDist = min(minDist, max(*dist1.rbegin() - *dist1.begin(), *dist2.rbegin() - *dist2.begin()));
            dist1.insert(x + y);
            dist2.insert(x - y);
        }
        
        return minDist;
    }
};
