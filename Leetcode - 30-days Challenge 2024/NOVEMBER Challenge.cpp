
// DAY 1 (1957. Delete Characters to Make Fancy String)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

string makeFancyString(string s) {
    int size = s.size();
    if(size < 3)
        return s;
    int prevItr = 2;
    for(int itr = 2; itr < size; itr++)
        if(s[itr] != s[prevItr-1] || s[itr] != s[prevItr-2])
            s[prevItr++] = s[itr];
    s.resize(prevItr);
    return s;
}

// DAY 2 (2490. Circular Sentence)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isCircularSentence(string sentence) {
    for(int idx = 0; idx < sentence.size(); idx++)
        if(sentence[idx] == ' ' && sentence[idx-1] != sentence[idx+1])
            return false;
    return sentence[0] == sentence.back();
}

// DAY 3 (796. Rotate String)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> getLpsArray(string &s) {
    vector<int> lps(s.size(), 0);
    int len = 0;
    for(int idx = 1; idx < s.size(); ) {
        if(s[idx] == s[len])
            lps[idx++] = ++len;
        else {
            if(len)
                len = len? lps[len-1] : 0;
            else idx++;
        }
    }
    return lps;
}

bool rotateString(string s, string goal) {
    if(s.size() != goal.size())
        return false;
    string kmpStr = goal + "#" + s + s;
    vector<int> lps = getLpsArray(kmpStr);
    for(int idx = 0; idx < lps.size(); idx++) {
        if(lps[idx] == goal.size())
            return true;
    }
    return false;
}

// DAY 4 (3163. String Compression III)===============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string compressedString(string word) {
    int size = word.size();
    string ans = "";
    for(int idx = 0; idx < size; ) {
        int idx2 = idx;
        while(idx2 < size && idx2 - idx + 1 <= 9 && word[idx2] == word[idx])
            idx2++;
        ans += to_string(idx2 - idx) + word[idx];
        idx = idx2;
    }
    return ans;
}

// DAY 5 (2914. Minimum Number of Changes to Make Binary String Beautiful)============================================================

// APPROACH 1 (Checking through odd-even segments)

// Time Complexity = O(n)
// Space Complexity = O(1)

int minChanges(string s) {
    int size = s.size();
    int prevEvens = 0, prevOdds = 0;
    int moves = 0;
    for(int idx = 0; idx < size; ) {
        int nextIdx = idx;
        while(nextIdx < size && s[nextIdx] == s[idx])
            nextIdx++;
        if((nextIdx - idx) & 1) {
            if(prevOdds) {
                moves += prevEvens + 1;
                prevOdds = 0;
            }
            else prevOdds++;
            prevEvens = 0;
        }
        else prevEvens++;

        idx = nextIdx;
    }
    return moves;
}

// APPROACH 2 (Checking in bubbles)

// Time Complexity = O(n)
// Space Complexity = O(1)

int minChanges(string s) {
    int moves = 0;
    for(int idx = 0; idx < s.size(); idx += 2)
        moves += s[idx] != s[idx+1];
    return moves;
}

// DAY 6 (3011. Find if Array Can Be Sorted)======================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

bool isSortedArray(int size, vector<int> &nums) {
    for(int idx = 1; idx < size; idx++)
        if(nums[idx] < nums[idx-1])
            return false;
    return true;
}

bool canSortArray(vector<int>& nums) {
    int size = nums.size();
    for(int idx = 0; idx < size; idx++) {
        int pidx = idx;
        int bits = __builtin_popcount(nums[idx]);
        while(idx + 1 < size && __builtin_popcount(nums[idx+1]) == bits)
            idx++;
        sort(nums.begin() + pidx, nums.begin() + idx + 1);
    }

    return isSortedArray(size, nums);
}

// DAY 7 (2275. Largest Combination With Bitwise AND Greater Than Zero)================================================

// Time Complexity = O(n*32)
// Space Complexity = O(32)

int largestCombination(vector<int>& candidates) {
    vector<int> bitCandidates(32);
    int largestCombination = 0;
    for(int candidate : candidates)
        for(int bit = 0; bit < 32; bit++)
            if(candidate & (1 << bit))
                bitCandidates[bit]++;

    for(int bit = 0; bit < 32; bit++)
        largestCombination = max(largestCombination, bitCandidates[bit]);
    return largestCombination;
}

// DAY 8 (1829. Maximum XOR for Each Query)================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getTotalXor(vector<int> &nums) {
    int res = 0;
    for(int num : nums)
        res ^= num;
    return res;
}

vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
    int size = nums.size();
    int totalXor = getTotalXor(nums);
    vector<int> ans(size);
    for(int idx = size-1; idx >= 0; idx--) {
        int k = ~totalXor & ((1 << maximumBit) - 1);
        ans[size - idx - 1] = k;
        totalXor ^= nums[idx];
    }
    return ans;
}

// DAY 9 (3133. Minimum Array End)===================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

#define ll long long
long long minEnd(int n, int x) {
    ll ans = x;
    n--;

    for(int xbit = 0, nbit = 0; xbit < 64; xbit++) {
        if(x & (1ll << xbit))
            continue;
        if(n & (1ll << (nbit++)))
            ans |= 1ll << xbit;
    }

    return ans;
}

// DAY 10 (3097. Shortest Subarray With OR at Least K II)===================================================

// Time Complexity = O(n*32)
// Space Complexity = O(32)

int minimumSubarrayLength(vector<int>& nums, int k) {
    int minLen = INT_MAX, currOr = 0;
    vector<int> bitCnt(32);
    for(int idx = 0, pidx = 0; idx < nums.size(); idx++) {
        currOr |= nums[idx];
        for(int bit = 0; bit < 32; bit++)
            bitCnt[bit] += (nums[idx] >> bit) & 1;
        while(pidx <= idx && currOr >= k) {
            minLen = min(minLen, idx - pidx + 1);
            for(int bit = 0; bit < 32; bit++) {
                bitCnt[bit] -= (nums[pidx] >> bit) & 1;
                if(bitCnt[bit] == 0)
                    currOr &= ~(1 << bit);
            }
            pidx++;
        }
    }
    return minLen == INT_MAX? -1 : minLen;
}

// DAY 12 (2070. Most Beautiful Item for Each Query)================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int getLowerBound(vector<vector<int>>& items, int maxPrice) {
    int lo = 0, hi = items.size() - 1;
    int ans = items.size();
    while(lo <= hi) {
        int mid = ((lo + hi) >> 1);
        if(items[mid][0] <= maxPrice) {
            ans = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    return ans;
}

vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
    vector<int> ans;
    sort(items.begin(), items.end());
    for(int idx = 1; idx < items.size(); idx++) {
        items[idx][1] = max(items[idx][1], items[idx-1][1]);
    }
    for(int q : queries) {
        int lb = getLowerBound(items, q);
        if(lb == items.size())
            ans.push_back(0);
        else ans.push_back(items[lb][1]);
    }
    return ans;
}

// DAY 13 (2563. Count the Number of Fair Pairs)====================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

long long countFairPairs(vector<int>& nums, int lower, int upper) {
    int size = nums.size();
    sort(nums.begin(), nums.end());
    long long ans = 0;
    for(int idx = 1; idx < size; idx++) {
        int lowerNum = lower - nums[idx];
        int upperNum = upper - nums[idx];
        int lb = lower_bound(nums.begin(), nums.begin() + idx, lowerNum) - nums.begin();
        int ub = upper_bound(nums.begin(), nums.begin() + idx, upperNum) - nums.begin();
        ans += 1ll * ub - lb;
    }
    return ans;
}

// DAY 15 (1574. Shortest Subarray to be Removed to Make Array Sorted)===========================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int findLengthOfShortestSubarray(vector<int>& arr) {
    int size = arr.size();
    int sortedPrefixLen = 1, sortedSuffixLen = 1;
    for(int idx = 1; idx < size && arr[idx] >= arr[idx-1]; idx++) {
        sortedPrefixLen++;
    }
    for(int idx = size-2; idx >= 0 && arr[idx] <= arr[idx+1]; idx--) {
        sortedSuffixLen++;
    }
    if(sortedPrefixLen == size)
        return 0;
    int minLen = min(size - sortedPrefixLen, size - sortedSuffixLen);
    for(int idx1 = sortedPrefixLen-1, idx2 = size-1; idx1 >= 0 && idx2 >= size-sortedSuffixLen; ) {
        if(arr[idx1] <= arr[idx2]) {
            minLen = min(minLen, idx2 - idx1 - 1);
            idx2--;
        }
        else idx1--;
    }
    return minLen;
}

// DAY 16 (3254. Find the Power of K-Size Subarrays I)======================================================================

// Time Complexity = O(n)
// Space Complexity = O(n - k)

vector<int> resultsArray(vector<int>& nums, int k) {
    int n = nums.size();
    vector<int> ans(n - k + 1);
    vector<int> incLen(n, 1);
    for(int idx = 1; idx < n; idx++)
        incLen[idx] = nums[idx] == nums[idx-1] + 1? incLen[idx-1] + 1 : 1;
    for(int idx = k-1; idx < n; idx++) {
        ans[idx-k+1] = incLen[idx] >= k? nums[idx] : -1;
    }
    return ans;
}

// DAY 19 (2461. Maximum Sum of Distinct Subarrays With Length K)===================================================

// Time Complexity = O(n)
// Space Complexity = O(k)

#define ll long long
long long maximumSubarraySum(vector<int>& nums, int k) {
    unordered_map<int, int> numCnt;
    ll maxSum = 0, currSum = 0;
    for(int curr = 0, prev = 0; curr < nums.size(); curr++) {
        numCnt[nums[curr]]++;
        currSum += nums[curr];
        while(numCnt[nums[curr]] == 2 || numCnt.size() > k) {
            if(--numCnt[nums[prev]] == 0)
                numCnt.erase(nums[prev]);
            currSum -= nums[prev++];
        }
        if(numCnt.size() == k)
            maxSum = max(maxSum, currSum);
    }
    return maxSum;
}

// DAY 20 (2516. Take K of Each Character From Left and Right)============================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int takeCharacters(string s, int k) {
    int acnt = 0, bcnt = 0, ccnt = 0, n = s.size();
    int i = 0, j = n-1;
    while(i < n && (acnt < k || bcnt < k || ccnt < k)) {
        acnt += s[i] == 'a';
        bcnt += s[i] == 'b';
        ccnt += s[i] == 'c';
        i++;
    }
    if(acnt < k || bcnt < k || ccnt < k)
        return -1;
    int minMin = i--;
    if(i == j) {
        acnt -= s[i] == 'a';
        bcnt -= s[i] == 'b';
        ccnt -= s[i] == 'c';
        i--;
    }
    while(j >= 0 && i >= 0) {
        acnt += s[j] == 'a';
        bcnt += s[j] == 'b';
        ccnt += s[j] == 'c';

        while(i >= -1 && (acnt >= k && bcnt >= k && ccnt >= k)) {
            minMin = min(minMin, (i + 1) + (n - j));
            if(i == -1) break;
            acnt -= s[i] == 'a';
            bcnt -= s[i] == 'b';
            ccnt -= s[i] == 'c';
            i--;
        }
        j--;
    }

    return minMin;
}


// DAY 21 (2257. Count Unguarded Cells in the Grid)================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

int countUnguarded(int m, int n, vector<vector<int>>& guards, vector<vector<int>>& walls) {
    vector<vector<int>> isGaurded(m, vector<int>(n, 0));
    int ungaurdedCnt = 0;
    for(vector<int> cell : guards)
        isGaurded[cell[0]][cell[1]] = 1;
    for(vector<int> cell : walls)
        isGaurded[cell[0]][cell[1]] = -1;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(isGaurded[i][j]) continue;
            bool isLeftGaurded = (j && (isGaurded[i][j-1] == 1 || isGaurded[i][j-1] == 2 || isGaurded[i][j-1] == 4));
            bool isUpGaurded = (i && (isGaurded[i-1][j] == 1 || isGaurded[i-1][j] == 3 || isGaurded[i-1][j] == 4));
            if(isLeftGaurded && isUpGaurded)
                isGaurded[i][j] = 4;
            else if(isLeftGaurded)
                isGaurded[i][j] = 2;
            else if(isUpGaurded)
                isGaurded[i][j] = 3;
        }
    }
    for(int i = m-1; i >= 0; i--) {
        for(int j = n-1; j >= 0; j--) {
            if(isGaurded[i][j] == -1 || isGaurded[i][j] == 1 || isGaurded[i][j] == 4) continue;
            bool isRightGaurded = (n-j-1 && (isGaurded[i][j+1] == 1 || isGaurded[i][j+1] == 2 || isGaurded[i][j+1] == 4));
            bool isDownGaurded = (m-i-1 && (isGaurded[i+1][j] == 1 || isGaurded[i+1][j] == 3 || isGaurded[i+1][j] == 4));
            if(isRightGaurded && isDownGaurded)
                isGaurded[i][j] = 4;
            else if(isRightGaurded)
                isGaurded[i][j] = 2;
            else if(isDownGaurded)
                isGaurded[i][j] = 3;
            
            if(isGaurded[i][j] == 0)
                ungaurdedCnt++;
        }
    }

    return ungaurdedCnt;
}

// DAY 22 (1072. Flip Columns For Maximum Number of Equal Rows)===========================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int maxEqualRowsAfterFlips(vector<vector<int>>& matrix) {
    unordered_map<string, int> maskCnt;
    for(vector<int> row : matrix) {
        string mask = "";
        for(int bit : row) {
            if(bit) mask += "0";
            else mask += "1";
        }
        maskCnt[mask]++;
    }

    int maxCnt = 0;
    for(auto pair : maskCnt)
        maxCnt = max(maxCnt, pair.second);
    return maxCnt;
}

// DAY 23 (1861. Rotating the Box)================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

void moveItemsInBox(vector<vector<char>> &rotatedBox) {
    int rows = rotatedBox.size(), cols = rotatedBox[0].size();
    for(int col = 0; col < cols; col++) {
        int lastStonePos = -1;
        for(int row = 0; row < rows; row++) {
            if(rotatedBox[row][col] == '.') {
                if(lastStonePos != -1) {
                    swap(rotatedBox[row][col], rotatedBox[lastStonePos++][col]);
                }
            }
            else if(rotatedBox[row][col] == '#') {
                if(lastStonePos == -1) {
                    lastStonePos = row;
                }
            }
            else {
                lastStonePos = row + 1;
            }
        }
    }
}

void rotateBox(int rows, int cols, vector<vector<char>> &box, vector<vector<char>> &rotatedBox) {
    int idx = 0;
    for(int col = 0; col < cols; col++) {
        for(int row = rows-1; row >= 0; row--) {
            int rotatedRow = idx / rows;
            int rotatedCol = idx % rows;
            idx++;
            rotatedBox[rotatedRow][rotatedCol] = box[row][col];
        }
    }
}

vector<vector<char>> rotateTheBox(vector<vector<char>>& box) {
    int rows = box.size(), cols = box[0].size();
    vector<vector<char>> rotatedBox(cols, vector<char>(rows));
    rotateBox(rows, cols, box, rotatedBox);
    moveItemsInBox(rotatedBox);
    return rotatedBox;
}
