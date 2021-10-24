// APPROACH 1

void perms(string &s, int i, vector<vector<int>> &arr2)
{
    arr2[i].push_back(stoi(s));
    while (next_permutation(s.begin(), s.end()))
        arr2[i].push_back(stoi(s));
}

int nextBeautifulNumber(int n)
{
    if (n == 0)
        return 1;

    vector<vector<string>> arr = {{"1"}, {"22"}, {"122", "333"}, {"1333", "4444"}, {"14444", "22333", "55555"}, {"122333", "224444", "155555", "666666"}, {"1224444", "1666666", "2255555", "3334444", "7777777"}, {"88888888"}};
    vector<vector<int>> arr2(8);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
            perms(arr[i][j], i, arr2);

        sort(arr2[i].begin(), arr2[i].end());
    }

    int nn = n, cnt = 0;
    while (nn)
    {
        nn /= 10;
        cnt++;
    }
    auto u1 = upper_bound(arr2[cnt - 1].begin(), arr2[cnt - 1].end(), n);
    auto u2 = upper_bound(arr2[cnt].begin(), arr2[cnt].end(), n);

    int x = u1 - arr2[cnt - 1].begin();
    int y = u2 - arr2[cnt].begin();
    if (x == arr2[cnt - 1].size())
        return arr2[cnt][y];
    return min(arr2[cnt - 1][x], arr2[cnt][y]);
}