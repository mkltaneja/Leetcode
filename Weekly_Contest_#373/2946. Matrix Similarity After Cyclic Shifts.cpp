class Solution {
public:
    bool areSimilar(vector<vector<int>>& mat, int k) 
    {
        int n = mat.size(), m = mat[0].size();
        k %= m;
        for(int i = 0; i < n; i++)
        {
            vector<int> a(mat[i].begin(), mat[i].begin() + m - k);
            vector<int> b(mat[i].begin() + m - k, mat[i].end());
            vector<int> c(b.begin(), b.end());
            c.insert(c.end(), a.begin(), a.end());
            
            if(c != mat[i])
                return false;
        }
        return true;
    }
};
