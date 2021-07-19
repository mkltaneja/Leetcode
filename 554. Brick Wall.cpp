
int leastBricks(vector<vector<int>> &wall)
{
    int n = wall.size();
    unordered_map<int, int> m;
    for (int i = 0; i < n; i++)
    {
        int gap = 0;
        for (int j = 0; j < wall[i].size() - 1; j++)
        {
            gap += wall[i][j];
            m[gap]++;
        }
    }
    int mx = 0;
    for (auto p : m)
        mx = max(mx, p.second);
    return (n - mx);
}