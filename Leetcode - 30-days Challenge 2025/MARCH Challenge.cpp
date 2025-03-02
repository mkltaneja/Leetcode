
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

// DAY 2 (2570. Merge Two 2D Arrays by Summing Values)===============================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
    vector<vector<int>> ans;
    int size1 = nums1.size(), size2 = nums2.size();
    for(int idx1 = 0, idx2 = 0; idx1 < size1 || idx2 < size2; ) {
        if(idx1 == size1 || idx2 == size2) {
            if(idx1 == size1) {
                ans.push_back(nums2[idx2++]);
            }
            else {
                ans.push_back(nums1[idx1++]);
            }
        }
        else if(nums1[idx1][0] < nums2[idx2][0]) {
            ans.push_back(nums1[idx1++]);
        }
        else if(nums1[idx1][0] > nums2[idx2][0]) {
            ans.push_back(nums2[idx2++]);
        }
        else {
            ans.push_back({nums1[idx1][0], nums1[idx1++][1] + nums2[idx2++][1]});
        }
    }
    return ans;
}
