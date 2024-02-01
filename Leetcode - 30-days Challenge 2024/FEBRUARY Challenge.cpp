
// DAY 1 (2966. Divide Array Into Arrays With Max Difference)===========================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<vector<int>> divideArray(vector<int> &nums, int k)
{
    int size = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    for(int idx = 0; idx+2 < size; idx+=3)
    {
        if(nums[idx+2] - nums[idx] > k)
            return {};
        ans.push_back({nums[idx], nums[idx+1], nums[idx+2]});
    }
    return ans;
}
