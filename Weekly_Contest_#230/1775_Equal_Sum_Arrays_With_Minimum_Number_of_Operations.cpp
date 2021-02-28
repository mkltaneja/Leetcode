
int minOperations(vector<int> &a, vector<int> &b)
{
    vector<int> sum(2, 0);
    vector<vector<int>> cnt(2, vector<int>(6, 0));
    for (int x : a)
    {
        sum[0] += x;
        cnt[0][x - 1]++;
    }
    for (int x : b)
    {
        sum[1] += x;
        cnt[1][x - 1]++;
    }

    int j = (sum[1] > sum[0]);
    int ans = 0;
    while (sum[j] > sum[j ^ 1])
    {
        int i = 5;
        while (i && cnt[j][i] == 0 && cnt[j ^ 1][5 - i] == 0)
            i--;
        if (!i)
            return -1;
        sum[j] -= i;
        if (cnt[j][i])
            cnt[j][i]--;
        else
            cnt[j ^ 1][5 - i]--;
        ans++;
    }
    return ans;
}