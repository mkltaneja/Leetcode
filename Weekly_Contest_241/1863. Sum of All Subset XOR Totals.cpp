
void subseq(int i, vector<int> &nums, int &ans, int x)
{
    if (i == nums.size())
    {
        ans += x;
        return;
    }
    subseq(i + 1, nums, ans, x ^ nums[i]);
    subseq(i + 1, nums, ans, x);
}

int subsetXORSum(vector<int> &nums)
{
    int ans = 0;
    subseq(0, nums, ans, 0);
    return ans;
}