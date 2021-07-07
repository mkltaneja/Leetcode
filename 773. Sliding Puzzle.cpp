
#define f first
#define s second

int slidingPuzzle(vector<vector<int>> &board)
{
    vector<vector<int>> swaps = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};
    string solved = "123450";
    string curr = "";
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            curr += to_string(board[i][j]);

    set<string> vis;
    vis.insert(curr);

    queue<pair<string, int>> que;
    que.push({curr, 0});
    while (!que.empty())
    {
        auto tp = que.front();
        que.pop();
        if (tp.f == solved)
            return tp.s;
        int i = 0;
        while (tp.f[i] != '0')
            i++;
        for (int x : swaps[i])
        {
            swap(tp.f[i], tp.f[x]);
            if (!vis.count(tp.f))
            {
                vis.insert(tp.f);
                que.push({tp.f, tp.s + 1});
            }
            swap(tp.f[i], tp.f[x]);
        }
    }
    return -1;
}