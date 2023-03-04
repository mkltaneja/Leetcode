class Solution {
public:
    
    int mod = 1e9 + 7;
    int countWays(vector<vector<int>>& ranges) 
    {
        sort(ranges.begin(), ranges.end());
        int end = ranges[0][1], clusters = 1, ans = 2;
        for(int i = 1; i < ranges.size(); i++)
        {
            if(end < ranges[i][0])
            {
                clusters++;
                ans = ((ans % mod) * (2l % mod)) % mod;
            }
            end = max(end, ranges[i][1]);
        }

        return ans;
    }
};
