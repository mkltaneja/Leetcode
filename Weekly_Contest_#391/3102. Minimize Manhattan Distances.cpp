
// APPROACH 1 (Using Multiset to consider extreme points)

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


// APPROACH 2 (Without Multiset - Taking 4 variables to consider extreme points)

// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    
    int findMaximumDistance(vector<vector<int>> &points, int ignoreIdx, int &extreme1, int &extreme2)
    {
        int idx1 = -1, idx2 = -1, idx3 = -1, idx4 = -1;
        for(int idx = 0; idx < points.size(); idx++)
        {
            if(idx == ignoreIdx) continue;
            
            if(idx1 == -1 || points[idx][0] + points[idx][1] < points[idx1][0] + points[idx1][1])
                idx1 = idx;
            if(idx2 == -1 || points[idx][0] + points[idx][1] > points[idx2][0] + points[idx2][1])
                idx2 = idx;
            if(idx3 == -1 || points[idx][0] - points[idx][1] < points[idx3][0] - points[idx3][1])
                idx3 = idx;
            if(idx4 == -1 || points[idx][0] - points[idx][1] > points[idx4][0] - points[idx4][1])
                idx4 = idx;
        }
        int dist1 = (points[idx2][0] + points[idx2][1]) - (points[idx1][0] + points[idx1][1]);
        int dist2 = (points[idx4][0] - points[idx4][1]) - (points[idx3][0] - points[idx3][1]);
        if(dist1 > dist2)
        {
            extreme1 = idx1;
            extreme2 = idx2;
            return dist1;
        }
        extreme1 = idx3;
        extreme2 = idx4;
        return dist2;
    }
    
    int minimumDistance(vector<vector<int>>& points)
    {
        int extreme1 = -1, extreme2 = -1, tmp1 = -1, tmp2 = -1;
        findMaximumDistance(points, -1, extreme1, extreme2);
        
        return min(findMaximumDistance(points, extreme1, tmp1, tmp2), findMaximumDistance(points, extreme2, tmp1, tmp2));
    }
};
