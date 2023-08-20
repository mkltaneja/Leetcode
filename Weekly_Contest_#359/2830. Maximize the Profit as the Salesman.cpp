class Solution {
public:
    int maximizeTheProfit(int n, vector<vector<int>>& offers) 
    {
        vector<vector<pair<int,int>>> startGold(n);
        vector<int> dp(n+1, 0);
        for(vector<int> &offer : offers)
            startGold[offer[1]].push_back({offer[0], offer[2]});
        
        for(int end = 0; end < n; end++)
        {
            dp[end] = end? dp[end - 1] : 0;
            for(pair<int,int> &sg : startGold[end])
                dp[end] = max(dp[end], sg.second + (sg.first? dp[sg.first - 1] : 0));
        }
        
        return dp[n-1];
    }
};
