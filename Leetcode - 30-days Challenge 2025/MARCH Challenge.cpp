
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

// DAY 5 (2579. Count Total Number of Colored Cells)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long coloredCells(int n) {
    long long totalCells = 1;
    while(--n) {
        totalCells += 4ll * n;
    }
    return totalCells;
}

// DAY 6 (2965. Find Missing and Repeated Values)=================================================================================

// Time Complexity = O(n*n)
// Space Complexity = O(1)

vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    int n = grid[0].size();
    long long total = n*n;
    long long sum = 0, sumSq = 0;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            sum += grid[row][col];
            sumSq += grid[row][col] * grid[row][col];
        }
    }
    long long sumDiff = sum - (total * (total + 1) / 2);
    long long sumSqDiff = sumSq - (total * (total + 1) * (2 * total + 1) / 6);
    int repeatedNum = ((sumSqDiff / sumDiff) + sumDiff) / 2;
    int missingNum = ((sumSqDiff / sumDiff) - sumDiff) / 2;
    return {repeatedNum, missingNum};
}

// DAY 7 (2523. Closest Prime Numbers in Range)==============================================================================

// Time Complexity = O(n * log(logn))
// Time Complexity = O(n)

vector<int> closestPrimes(int left, int right) {
    vector<bool> isPrime(right + 1, true);
    isPrime[0] = isPrime[1] = false;
    int tempNum1 = -1, tempNum2 = -1, num1 = -1, num2 = -1, minDiff = INT_MAX;
    for(int num = 2; num <= right; num++) {
        if(!isPrime[num]) {
            continue;
        }
        for(long long nextNum = 1ll * num * num; nextNum <= right; nextNum += num) {
            isPrime[nextNum] = false;
        }
    }

    for(int num = left; num <= right; num++) {
        if(!isPrime[num]) {
            continue;
        }
        if(tempNum1 == -1) {
            tempNum1 = num;
        }
        else if(tempNum2 == -1) {
            tempNum2 = num;
        }
        else {
            tempNum1 = tempNum2;
            tempNum2 = num;
        }
        if(tempNum1 != -1 && tempNum2 != -1) {
            if(tempNum2 - tempNum1 < minDiff) {
                num1 = tempNum1;
                num2 = tempNum2;
                minDiff = tempNum2 - tempNum1;
            }
        }
    }
    return {num1, num2};
}

// DAY 8 (2379. Minimum Recolors to Get K Consecutive Black Blocks)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumRecolors(string blocks, int k) {
    int currWhiteCount = 0, minOperations = k;
    for(int idx = 0; idx < blocks.size(); idx++) {
        currWhiteCount += blocks[idx] == 'W';
        if(idx >= k - 1) {
            if(idx >= k) {
                currWhiteCount -= blocks[idx - k] == 'W';
            }
            minOperations = min(minOperations, currWhiteCount);
        }
    }
    return minOperations;
}

// DAY 9 (3208. Alternating Groups II)================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfAlternatingGroups(vector<int>& colors, int k) {
    int size = colors.size(), groups = 0;
    for(int left = 0, right = 0; right < size + k - 1; right++) {
        if(right && colors[right % size] == colors[(right - 1) % size]) {
            left = right;
        }
        if(right - left + 1 >= k) {
            groups++;
        }
    }
    return groups;
}

// DAY 10 (1358. Number of Substrings Containing All Three Characters)====================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfSubstrings(string s) {
    int size = s.size();
    int totalSubstrs = 0;
    vector<int> charCount(3, 0);
    for(int left = 0, right = 0; right < size; right++) {
        charCount[s[right]-'a']++;
        while(charCount[0] && charCount[1] && charCount[2]) {
            totalSubstrs += size - right;
            charCount[s[left++]-'a']--;
        }
    }
    return totalSubstrs;
}
