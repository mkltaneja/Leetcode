class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) 
    {
        int n = mat.size(), m = mat[0].size();
        int mx = 0, mxi = 0;
        for(int i = 0; i < n; i++)
        {
            int x = 0;
            for(int y : mat[i])
                x += y;
            if(x > mx) mx = x, mxi = i;
        }
        
        return {mxi, mx};
    }
};
