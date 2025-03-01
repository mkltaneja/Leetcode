
// DAY 1 (2460. Apply Operations to an Array)======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> applyOperations(vector<int>& nums) {
    int size = nums.size();
    for(int idx = 0, first0 = -1; idx < size; idx++) {
        if(nums[idx] == 0 && first0 == -1) {
            first0 = idx;
        }
        if(size-1-idx && nums[idx] && nums[idx] == nums[idx + 1]) {
            nums[idx] *= 2;
            nums[idx + 1] = 0;
        }
        if(nums[idx] && first0 != -1) {
            swap(nums[first0++], nums[idx]);
        }
    }
    return nums;
}
