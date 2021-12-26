
vector<int> executeInstructions(int n, vector<int> &startPos, string s)
{
    int m = s.size();
    vector<int> ans(m);
    for (int i = 0; i < m; i++)
    {
        int tot = 0;
        int x = startPos[0], y = startPos[1];
        for (int j = i; j < m; j++)
        {
            if (s[j] == 'L')
                y--;
            else if (s[j] == 'R')
                y++;
            else if (s[j] == 'D')
                x++;
            else if (s[j] == 'U')
                x--;
            if (x < 0 || y < 0 || x == n || y == n)
                break;
            tot++;
        }
        ans[i] = tot;
    }
    return ans;
}