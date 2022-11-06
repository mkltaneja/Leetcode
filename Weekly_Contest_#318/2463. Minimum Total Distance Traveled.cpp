class Solution {
public:
    
    #define ll long long
    
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) 
    {
        vector<int> allFactory;
        for(auto &v : factory)
            while(v[1]--)
                allFactory.push_back(v[0]);
        sort(allFactory.begin(), allFactory.end());
        sort(robot.begin(), robot.end());
        
        int n = robot.size(), m = allFactory.size();
        ll inf = LONG_LONG_MAX;
        
        vector<vector<ll>> dp(m, vector<ll>(n+1, inf));
        for(int i = 0; i < m; i++)
            dp[i][0] = 0;
        dp[0][1] = abs(allFactory[0] - robot[0]);
        
        for(int i = 1; i < m; i++)
            for(int j = 1; j <= n; j++)
                dp[i][j] = min(dp[i-1][j], dp[i-1][j-1] == inf? inf : dp[i-1][j-1] + abs(allFactory[i] - robot[j-1]));
        
        return dp[m-1][n];
    }
};
