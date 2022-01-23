
int maximumGood(vector<vector<int>> &statements)
{
    int n = statements.size();
    int ans = 0;
    for (int x = 0; x < (1 << n); x++)
    {
        bool valid = true;
        int goods = 0;
        for (int i = 0; i < n && valid; i++)
        {
            if (x >> i & 1 ^ 1)
                continue;
            goods++;
            for (int j = 0; j < n && valid; j++)
            {
                if (statements[i][j] == 2)
                    continue;
                if (statements[i][j] ^ (x >> j & 1))
                    valid = false;
            }
        }
        if (valid)
            ans = max(ans, goods);
    }

    return ans;
}