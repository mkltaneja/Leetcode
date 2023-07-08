class Solution {
public:
    vector<long long> countBlackBlocks(int m, int n, vector<vector<int>>& coordinates) 
    {
        set<pair<int,int>> st;
        int dir[4][2] = {{1,1}, {1,-1}, {-1,-1}, {-1, 1}};
        
        vector<long long> ans(5,0);
        ans[0] = 1l * (n-1) * (m-1);
        for(vector<int> &c : coordinates)
        {
            int x = c[0];
            int y = c[1];
            
            for(int d = 0; d < 4; d++)
            {
                int nx = x + dir[d][0];
                int ny = y + dir[d][1];
                if(nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                
                int blacks = st.count({x, ny}) + st.count({nx, y}) + st.count({nx, ny});
                ans[blacks]--;
                ans[blacks+1]++;
            }
            st.insert({x, y});
        }
        
        return ans;
    }
};
