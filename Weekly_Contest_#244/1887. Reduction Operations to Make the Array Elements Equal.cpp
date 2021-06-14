
int reductionOperations(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int x = nums[0];
    unsigned long long ans = 0, p = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == x)
            ans += p;
        else
        {
            x = nums[i];
            ans += ++p;
        }
    }
    return ans;
}