
// DAY 1 (3151. Special Array I)==========================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isArraySpecial(vector<int>& nums) {
    for(int idx = 0; idx < nums.size()-1; idx++) {
        if((nums[idx] + nums[idx+1]) & 1 ^ 1) {
            return false;
        }
    }
    return true;
}

// DAY 2 (1752. Check if Array Is Sorted and Rotated)======================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool check(vector<int>& nums) {
    int size = nums.size();
    int partitionCount = 0;
    for(int idx = 0; idx < size; idx++) {
        if(nums[idx] > nums[(idx+1) % size]) {
            partitionCount++;
        }
    }
    return partitionCount < 2;
}

// DAY 3 (3105. Longest Strictly Increasing or Strictly Decreasing Subarray)==============================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int largestIncreasingOrDecreasingSubarray(vector<int> &nums, int size, bool checkForIncreasing) {
    int largestSubarray = 0;
    for(int curr = 0; curr < size; ) {
        int forw = curr + 1;
        while(forw < size && (checkForIncreasing? nums[forw] > nums[forw-1] : nums[forw] < nums[forw-1])) {
            forw++;
        }
        largestSubarray = max(largestSubarray, forw - curr);
        curr = forw;
    }
    return largestSubarray;
}

int longestMonotonicSubarray(vector<int>& nums) {
    int size = nums.size();
    int largestIncreasingSubarray = largestIncreasingOrDecreasingSubarray(nums, size, true);
    int largestDecreasingSubarray = largestIncreasingOrDecreasingSubarray(nums, size, false);
    return max(largestIncreasingSubarray, largestDecreasingSubarray);
}

// DAY 4 (1800. Maximum Ascending Subarray Sum)========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxAscendingSum(vector<int>& nums) {
    int size = nums.size();
    int maxSum = 0;
    for(int curr = 0; curr < size; ) {
        int forw = curr + 1;
        int currSum = nums[curr];
        while(forw < size && nums[forw] > nums[forw-1]) {
            currSum += nums[forw++];
        }
        maxSum = max(maxSum, currSum);
        curr = forw;
    }
    return maxSum;
}
