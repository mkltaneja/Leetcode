
#define ull unsigned long long
vector<bool> canEat(vector<int> &arr, vector<vector<int>> &q)
{
    int m = arr.size(), n = q.size();

    vector<ull> psum(m + 1, 0);
    for (int i = 1; i <= m; i++)
        psum[i] = psum[i - 1] + arr[i - 1];
    for (int x : psum)
        cout << x << " ";
    cout << endl;

    vector<bool> ans(n);
    for (int i = 0; i < n; i++)
    {
        ull t = q[i][0], d = q[i][1], c = q[i][2];

        ull days = d + 1;
        ull max_caneat = (d + 1) * c;
        ull max_days = psum[t + 1];
        ull min_toeat = psum[t] + 1;

        if (min_toeat > max_caneat || max_days < days)
            ans[i] = false;
        else
            ans[i] = true;
    }
    return ans;
}