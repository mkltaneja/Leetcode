
int ans = 0;
void subs(int x, int i, int m, vector<int> &bits, int cols)
{
    if(cols == 0)
    {
        int cnt = 0;
        for(int y : bits)
            if((y & ~x) == 0)
                cnt++;
        ans = max(ans, cnt);
        return;
    }
    if(i == m) return;

    subs(x | (1 << i), i+1, m, bits, cols-1);
    subs(x, i+1, m, bits, cols);
}

int maximumRows(vector<vector<int>>& mat, int cols) 
{
    int n = mat.size(), m = mat[0].size();
    vector<int> bits(n);
    for(int i = 0; i < n; i++)
    {
        int x = 0;
        for(int j = 0; j < m; j++)
        {
            x <<= 1;
            if(mat[i][j])
                x |= 1;
        }
        bits[i] = x;
    }

    subs(0, 0, m, bits, cols);
    return ans;
}
