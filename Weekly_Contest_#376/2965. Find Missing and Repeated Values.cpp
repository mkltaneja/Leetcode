class Solution {
public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) 
    {
        int n = grid.size();
        unordered_map<int,int> mp;
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                mp[grid[i][j]]++;
        vector<int> ans(2);
        for(int i = 1; i <= n*n; i++)
            if(mp[i] == 2)
                ans[0] = i;
            else if(mp[i] == 0)
                ans[1] = i;
        return ans;
    }
};
