
vector<int> gridIllumination(int n, vector<vector<int>> &lamps, vector<vector<int>> &queries)
{
    unordered_map<long, long> row, col, ld, rd;
    unordered_map<long, bool> cell;
    for (vector<int> v : lamps)
    {
        long i = v[0], j = v[1];
        if (cell[long(i * n + j)])
            continue;
        cell[i * n + j] = true;
        row[i]++;
        col[j]++;
        rd[i + j]++;
        ld[(i - j) + (n - 1)]++;
    }
    vector<int> ans(queries.size());
    int k = 0;
    int dir[9][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, -1}, {-1, 1}, {1, 1}, {-1, -1}};
    for (vector<int> v : queries)
    {
        long i = v[0], j = v[1];
        if (cell[long(i * n + j)] || row[i] > 0 || col[j] > 0 || rd[i + j] > 0 || ld[(i - j) + (n - 1)] > 0)
            ans[k++] = 1;
        else
            ans[k++] = 0;

        for (int d = 0; d < 9; d++)
        {
            long r = i + dir[d][0], c = j + dir[d][1];
            if (r < 0 || c < 0 || r >= n || c >= n)
                continue;
            if (cell[long(r * n + c)])
            {
                cell[long(r * n + c)] = false;
                row[r]--;
                col[c]--;
                rd[r + c]--;
                ld[(r - c) + (n - 1)]--;
            }
        }
    }
    return ans;
}