
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