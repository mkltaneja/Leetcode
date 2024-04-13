
// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

class Solution {
public:
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w) 
    {
        int ans = 0;
        int n = points.size();
        sort(points.begin(), points.end());
        for(int i = 0; i < n; )
        {
            int j = i;
            while(j < n && points[j][0] <= points[i][0] + w)
                j++;
            ans++;
            i = j;
        }
        return ans;
    }
};
