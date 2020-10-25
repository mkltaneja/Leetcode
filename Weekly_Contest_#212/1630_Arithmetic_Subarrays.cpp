
bool checkarith(vector<int> &a)
{
    int n = a.size();
    for (int i = 2; i < n; i++)
        if (a[i] - a[i - 1] != a[1] - a[0])
            return false;
    return true;
}

vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l, vector<int> &r)
{
    int n = l.size();
    vector<bool> ans(n);
    for (int i = 0; i < n; i++)
    {
        vector<int> temp(nums.begin() + l[i], nums.begin() + r[i] + 1);
        sort(temp.begin(), temp.end());
        bool ansi = checkarith(temp);
        ans[i] = ansi;
    }
    return ans;
}