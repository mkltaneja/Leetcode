
int majorityElement(vector<int> &nums)
{
    int n = nums.size();
    int x = nums[0], cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == x)
            cnt++;
        else
            cnt--;
        if (cnt == 0)
            x = nums[i], cnt = 1;
    }
    return x;
}