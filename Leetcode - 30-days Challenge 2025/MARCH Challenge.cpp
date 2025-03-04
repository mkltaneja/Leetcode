
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

// DAY 3 (2161. Partition Array According to Given Pivot)=========================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> pivotArray(vector<int>& nums, int pivot) {
    vector<int> smaller, greater;
    for(int num : nums) {
        if(num < pivot) {
            smaller.push_back(num);
        }
        else if(num > pivot) {
            greater.push_back(num);
        }
    }
    int equals = nums.size() - (smaller.size() + greater.size());
    int idx = 0;
    for(int num : smaller) {
        nums[idx++] = num;
    }
    while(equals--) {
        nums[idx++] = pivot;
    }
    for(int num : greater) {
        nums[idx++] = num;
    }
    
    return nums;
}

// DAY 4 (1780. Check if Number is a Sum of Powers of Three)=========================================================

// APPROACH 1 (Recursive)

// Time Complexity = O(2^log3(n)) = O(n)
// Space Complexity = O(log3(n))

bool checkPowersOfThreeDFS(int n, int prod) {
    if(n == 0) {
        return true;
    }
    if(prod > n) {
        return false;
    }
    
    bool includeProd = checkPowersOfThreeDFS(n - prod, prod * 3);
    bool excludeProd = checkPowersOfThreeDFS(n, prod * 3);

    return includeProd || excludeProd;
}

bool checkPowersOfThree(int n) {
    return checkPowersOfThreeDFS(n, 1);
}

// APPROACH 2 (Iterative)

// Time Complexity = O(log3(n))
// Space Complexity = O(1)

bool checkPowersOfThree(int n) {
    int prod = 1;
    while(prod * 3 <= n) {
        prod *= 3;
    }
    while(prod) {
        if(n / prod) {
            n -= prod;
        }
        if(n / prod) {
            return false;
        }
        prod /= 3;
    }
    return true;
}

// APPROACH 3 (Iterative - Ternary Representation) --> [OPTIMIZED]

// Time Complexity = O(log3(n))
// Space Complexity = O(1)

bool checkPowersOfThree(int n) {
    while(n) {
        if(n % 3 == 2) {
            return false;
        }
        n /= 3;
    }
    return true;
}
