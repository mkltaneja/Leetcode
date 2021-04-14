
void wiggleSort(vector<int> &nums)
{
    int n = nums.size();
    for (int i = 0; i < n - 1; i++)
    {
        if ((i & 1) && (nums[i] < nums[i + 1]))
            swap(nums[i], nums[i + 1]);
        else if (!(i & 1) && nums[i] > nums[i + 1])
            swap(nums[i], nums[i + 1]);
    }
    // write your code here
}