class Solution {
public:
    int maximumCostSubstring(string s, string chars, vector<int>& vals) 
    {
        int n = s.size();
        vector<int> cost(26, INT_MIN);
        
        for(int i = 0; i < chars.size(); i++)
            cost[chars[i]-'a'] = vals[i];
        for(int i = 0; i < 26; i++)
            cost[i] = (cost[i] == INT_MIN)? i+1 : cost[i];
                
        int x = 0, ans = 0;
        for(int i = 0; i < n; i++)
        {
            x += cost[s[i]-'a'];
            if(x < 0) x = 0;
            ans = max(ans, x);
        }
        
        return ans;
    }
};
