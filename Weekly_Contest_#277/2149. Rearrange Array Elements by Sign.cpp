
vector<int> rearrangeArray(vector<int> &nums)
{
    vector<int> pos, neg;
    for (int x : nums)
    {
        if (x >= 0)
            pos.push_back(x);
        else
            neg.push_back(x);
    }
    int x = 0, j = 0, k = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (i & 1)
            nums[i] = neg[j++];
        else
            nums[i] = pos[k++];
    }
    return nums;
}