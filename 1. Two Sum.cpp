
#define f first
#define s second
vector<int> twoSum(vector<int> &nums, int target)
{
    int n = nums.size();
    vector<pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
        arr[i] = {nums[i], i};

    sort(arr.begin(), arr.end());
    int i = 0, j = n - 1;

    while (i < j)
    {
        int sum = arr[i].f + arr[j].f;

        if (sum == target)
            return {arr[i].s, arr[j].s};

        if (sum < target)
            i++;
        else
            j--;
    }
    return {-1, -1};
}