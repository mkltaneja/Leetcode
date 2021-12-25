
int countPoints(string rings)
{
    unordered_map<char, int> m;
    m['R'] = 0;
    m['G'] = 1;
    m['B'] = 2;
    vector<vector<int>> ring(10, vector<int>(3, 0));

    for (int i = 0; i < rings.size(); i += 2)
        ring[rings[i + 1] - '0'][m[rings[i]]] = 1;

    int ans = 0;
    for (int i = 0; i < 10; i++)
        ans += (ring[i][0] && ring[i][1] && ring[i][2]);

    return ans;
}