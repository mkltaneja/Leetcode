class Solution {
public:
    vector<vector<int>> differenceOfDistinctValues(vector<vector<int>>& grid) 
    {
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> ans(n, vector<int> (m,0));
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int r = max(0, i - j);
                int c = max(0, j - i);
                unordered_set<int> st;
                while(r < i && c < j)
                    st.insert(grid[r++][c++]);
                r++, c++;
                int x = st.size();
                
                st.clear();
                while(r < n && c < m)
                    st.insert(grid[r++][c++]);
                int y = st.size();
                
                ans[i][j] = abs(x - y);
            }
        }
        
        return ans;
    }
};
