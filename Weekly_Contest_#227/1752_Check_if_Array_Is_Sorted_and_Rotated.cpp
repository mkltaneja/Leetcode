
bool check(vector<int> &nums)
{
    int n = nums.size();
    int idx = -1;
    bool dec = false;
    for (int i = 1; i < n; i++)
    {
        if (nums[i - 1] > nums[i])
        {
            dec = true;
            idx = i;
            break;
        }
    }
    if (dec == false)
        return true;
    int cnt = 0;
    vector<int> sor(n);
    for (int i = idx; cnt < n; i = (i + 1) % n)
    {
        sor[cnt++] = nums[i];
    }
    sort(nums.begin(), nums.end());
    return nums == sor;
}

// OR

bool check(vector<int> &nums)
{
    int n = nums.size();
    int cnt = 0;
    for (int i = 1; i < n; i++)
        if (nums[i - 1] > nums[i])
            cnt++;
    if (nums[n - 1] > nums[0])
        cnt++;
    return cnt <= 1;
}