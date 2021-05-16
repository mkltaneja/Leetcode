
// APPROACH 1 (Brute Force -- all subsequences) --> O(2^n)

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

// APPROACH 2 (Making the bits of every number on, so it will occur exactly n/2 times in all the subsequences) --> O(n)

int subsetXORSum(vector<int> &nums)
{
    int on = 0, n = nums.size();
    for (int i = 0; i < n; i++)
        on |= nums[i];
    return on * pow(2, n - 1);
}