
vector<int> platesBetweenCandles(string s, vector<vector<int>> &queries)
{
    int n = s.size();
    vector<int> li(n, -1), tot1(n), tot2(n);
    int p = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '|')
            p = i, li[i] = -2;
        else if (p != -1)
            li[i] = p;
    }

    int cnt = 0;
    p = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '|')
        {
            if (p != -1)
                tot1[p + 1] = cnt;
            tot2[i] = cnt;
            p = i;
            cnt = 0;
        }
        else if (p != -1)
            cnt++;
    }

    for (int i = 0; i < n; i++)
    {
        tot1[i] += i ? tot1[i - 1] : 0;
        tot2[i] += i ? tot2[i - 1] : 0;
    }

    vector<int> res(queries.size());
    for (int i = 0; i < queries.size(); i++)
    {
        if (li[queries[i][0]] == li[queries[i][1]] && li[queries[i][0]] != -2)
            res[i] = 0;
        else
            res[i] = tot2[queries[i][1]] - tot1[queries[i][0]];
    }

    return res;
}