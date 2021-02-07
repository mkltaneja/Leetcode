
// METHOD 1 (Coin Change - Subsequence of finite coins)
// TLE

int mindiff = 2e9;
void coinchange(int i, int n, vector<int> &arr, int tar)
{
    mindiff = min(mindiff, abs(tar));
    if (i == n)
        return;
    coinchange(i + 1, n, arr, tar - arr[i]);
    coinchange(i + 1, n, arr, tar);
}

int minAbsDifference(vector<int> &nums, int goal)
{
    coinchange(0, nums.size(), nums, goal);
    return mindiff;
}

// METHOD 2 (Creating sum of all subsequences in an array, then using Lower Bound)
// AC

vector<int> allsums(int n, vector<int> &arr)
{
    vector<int> ans;
    for (int x = 0; x < (1 << n); x++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
            if ((x >> j) & 1)
                sum += arr[j];
        ans.push_back(sum);
    }
    sort(ans.begin(), ans.end());
    return ans;
}

int minAbsDifference(vector<int> &nums, int goal)
{
    int n = nums.size(), m = n / 2;
    vector<int> temp1 = vector<int>(nums.begin(), nums.begin() + m);
    vector<int> temp2 = vector<int>(nums.begin() + m, nums.begin() + n);
    vector<int> a = allsums(m, temp1);
    vector<int> b = allsums(n - m, temp2);

    int mindiff = 2e9;
    for (int x : a)
    {
        int i = upper_bound(b.begin(), b.end(), goal - x) - b.begin();
        if (i != b.size())
            mindiff = min(mindiff, abs(x + b[i] - goal));
        if (i != 0)
            mindiff = min(mindiff, abs(x + b[i - 1] - goal));
        if (mindiff == 0)
            break;
    }
    return mindiff;
}