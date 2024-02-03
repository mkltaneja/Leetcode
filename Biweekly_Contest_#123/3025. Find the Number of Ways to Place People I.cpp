
// Time = O(n*logn + n^3)
// Space = O(1)

class Solution {
public:
        
    int numberOfPairs(vector<vector<int>>& points) 
    {
        sort(points.begin(), points.end(), [](auto const &a, auto const &b){
            return a[0] == b[0]? a[1] > b[1] : a[0] < b[0];
        });
        
        int ans = 0;
        int n = points.size();
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                int cnt = 0;
                for(int k = i+1; k < j; k++)
                    if(points[k][1] >= points[j][1] && points[k][1] <= points[i][1])
                        cnt++;
                if(!cnt && points[j][1] <= points[i][1])
                    ans++;
            }
        }

        return ans;
    }
};
