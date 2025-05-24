
// DAY 2 (838. Push Dominoes)==============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void fillDominoes(char op, int st, int end, string &dominoes) {
    for(int idx = st; idx <= end; idx++) {
        dominoes[idx] = op;
    }
}

string pushDominoes(string dominoes) {
    int size = dominoes.size();
    char prevOp = '#';
    for(int idx = 0; idx < size; idx++) {
        if(dominoes[idx] == '.') {
            int tempItr = idx;
            while(tempItr < size && dominoes[tempItr] == '.') {
                tempItr++;
            }
            char currOp = tempItr == size? '#' : dominoes[tempItr];
            if((prevOp == 'R' && currOp != 'L') || (prevOp != 'R' && currOp == 'L')) {
                char op = prevOp == 'R'? prevOp : currOp;
                fillDominoes(op, idx, tempItr-1, dominoes);
            }
            else if(prevOp == 'R' && currOp == 'L') {
                int intervalSize = tempItr-idx;
                int halfInterval = intervalSize/2;
                int st1 = idx, st2 = idx + halfInterval + (intervalSize & 1);
                int end1 = st1 + halfInterval - 1, end2 = st2 + halfInterval - 1;
                fillDominoes('R', st1, end1, dominoes);
                fillDominoes('L', st2, end2, dominoes);
            }
            idx = tempItr;
            prevOp = currOp;
        } else {
            prevOp = dominoes[idx];
        }
    }
    return dominoes;
}

// DAY 4 (1128. Number of Equivalent Domino Pairs)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    vector<vector<int>> dominoPair(10, vector<int>(10, 0));
    int pairCount = 0;
    for(vector<int> &domino : dominoes) {
        int minVal = min(domino[0], domino[1]);
        int maxVal = max(domino[0], domino[1]);
        if(dominoPair[minVal][maxVal]) {
            pairCount += dominoPair[minVal][maxVal];
        }
        dominoPair[minVal][maxVal]++;
    }
    return pairCount;
}

// DAY 6 (1920. Build Array from Permutation)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> buildArray(vector<int>& nums) {
    int size = nums.size();
    vector<int> ans(size);
    for(int idx = 0; idx < size; idx++) {
        ans[idx] = nums[nums[idx]];
    }
    return ans;
}

// DAY 7 (3341. Find Minimum Time to Reach Last Room I)===========================================================================

// Time Complexity = O(n^2 * logn)
// Space Complexity = O(n^2)

int minTimeToReach(vector<vector<int>>& moveTime) {
    int rows = moveTime.size(), cols = moveTime[0].size();
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> minPq;
    minPq.push({0, {0, 0}});
    moveTime[0][0] = -1;

    while(!minPq.empty()) {
        int ctime = minPq.top().first;
        int crow = minPq.top().second.first;
        int ccol = minPq.top().second.second;
        minPq.pop();

        for(int d = 0; d < 4; d++) {
            int nrow = crow + dir[d][0];
            int ncol = ccol + dir[d][1];
            if(nrow == -1 || ncol == -1 || nrow == rows || ncol == cols || moveTime[nrow][ncol] == -1) {
                continue;
            }
            int ntime = max(ctime + 1, moveTime[nrow][ncol] + 1);
            if(nrow == rows - 1 && ncol == cols - 1) {
                return ntime;
            }
            minPq.push({ntime, {nrow, ncol}});
            moveTime[nrow][ncol] = -1;
        }
    }
    return -1;
}

// DAY 8 (3342. Find Minimum Time to Reach Last Room II)================================================================================

// Time Complexity = O(n*m * log(n*m))
// Space Complexity = O(n*m)

int minTimeToReach(vector<vector<int>>& moveTime) {
    int rows = moveTime.size(), cols = moveTime[0].size();
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minPq;
    minPq.push({0, 0, 0, 0});
    moveTime[0][0] = -1;
    while(!minPq.empty()) {
        int ctime = minPq.top()[0];
        int crow = minPq.top()[1];
        int ccol = minPq.top()[2];
        int cmove = minPq.top()[3];
        minPq.pop();

        for(int d = 0; d < 4; d++) {
            int nrow = crow + dir[d][0];
            int ncol = ccol + dir[d][1];
            int nmove = cmove ^ 1;
            if(nrow == -1 || ncol == -1 || nrow == rows || ncol == cols || moveTime[nrow][ncol] == -1) {
                continue;
            }
            int stepTime = (cmove & 1) + 1;
            int ntime = max(moveTime[nrow][ncol] + stepTime, ctime + stepTime);
            if(nrow == rows - 1 && ncol == cols - 1) {
                return ntime;
            }
            minPq.push({ntime, nrow, ncol, nmove});
            moveTime[nrow][ncol] = -1;
        }
    }
    return -1;
}

// DAY 10 (2918. Minimum Equal Sum of Two Arrays After Replacing Zeros)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long minSum(vector<int>& nums1, vector<int>& nums2) {
    long long sum1 = 0, sum2 = 0;
    int canInc1 = 0, canInc2 = 0;
    for(int num : nums1) {
        sum1 += num? num : 1;
        canInc1 |= num == 0;
    }
    for(int num : nums2) {
        sum2 += num? num : 1;
        canInc2 |= num == 0;
    }
    if(sum2 < sum1) {
        swap(sum1, sum2);
        swap(canInc1, canInc2);
    }
    else if(sum1 == sum2) {
        return sum1;
    }
    if(!canInc1) {
        return -1;
    }
    return sum2;
}

// DAY 11 (1550. Three Consecutive Odds)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool threeConsecutiveOdds(vector<int>& arr) {
    for(int idx = 0; idx < (int)arr.size()-2; idx++) {
        if((arr[idx] & 1) && (arr[idx + 1] & 1) && (arr[idx + 2] & 1)) {
            return true;
        }
    }
    return false;
}

// DAY 12 (2094. Finding 3-Digit Even Numbers)========================================================================================

// Time Complexity = O(n^3 * logn)
// Space Complexity = O(n^3)

vector<int> findEvenNumbers(vector<int>& digits) {
    int size = digits.size();
    set<int> ansSet;
    vector<int> ans;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = 0; idx2 < size; idx2++) {
            for(int idx3 = 0; idx3 < size; idx3++) {
                if(!digits[idx1] || (digits[idx3] & 1) || (idx1 == idx2 || idx1 == idx3 || idx2 == idx3)) {
                    continue;
                }
                int num = digits[idx1] * 100 + digits[idx2] * 10 + digits[idx3];
                ansSet.insert(num);
            }
        }
    }
    ans.insert(ans.begin(), ansSet.begin(), ansSet.end());
    return ans;
}

// DAY 13 (3335. Total Characters in String After Transformations I)===========================================================================

// Time Complexity = O(t * 26)
// Space Complexity = O(1)

const int MOD = 1e9 + 7;
int lengthAfterTransformations(string s, int t) {
    vector<int> cntMap(26, 0);
    for(char c : s) {
        cntMap[c - 'a']++;
    }
    int totalLen = 0;

    for(int trans = 1; trans <= t; trans++) {
        vector<int> nxtCntMap(26);
        nxtCntMap[0] = cntMap[25];
        nxtCntMap[1] = (cntMap[25] % MOD + cntMap[0] % MOD) % MOD;
        for(int c = 2; c < 26; c++) {
            nxtCntMap[c] = cntMap[c - 1];
        }
        cntMap = nxtCntMap;
    }
    for(int c = 0; c < 26; c++) {
        totalLen = (totalLen % MOD + cntMap[c] % MOD) % MOD;
    }

    return totalLen;
}

// DAY 15 (2900. Longest Unequal Adjacent Groups Subsequence I)===========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<string> getLongestSubsequence(vector<string>& words, vector<int>& groups) {
    vector<string> ans;
    int lastGroup = -1;
    for(int idx = 0; idx < words.size(); idx++) {
        if(lastGroup != groups[idx]) {
            ans.push_back(words[idx]);
            lastGroup = groups[idx];
        }
    }
    return ans;
}

// DAY 16 (2901. Longest Unequal Adjacent Groups Subsequence II)========================================================================

// Time Complexity = O(n^2 * m)
// Space Complexity = O(n)

int getHammingDistance(string &word1, string &word2) {
    if(word1.size() != word2.size()) {
        return -1;
    }
    int hammingDist = 0;
    for(int idx = 0; idx < word1.size(); idx++) {
        hammingDist += word1[idx] != word2[idx];
    }
    return hammingDist;
}

vector<string> getWordsInLongestSubsequence(vector<string>& words, vector<int>& groups) {
    int size = words.size();
    vector<string> ans;
    int overallMaxCount = 0, startIdx = -1;
    vector<int> maxCount(size, 1), nextIdx(size, -1);
    for(int idx1 = size - 1; idx1 >= 0; idx1--) {
        for(int idx2 = idx1 + 1; idx2 < size; idx2++) {
            if(getHammingDistance(words[idx1], words[idx2]) == 1 && groups[idx1] != groups[idx2]) {
                if(maxCount[idx2] + 1 > maxCount[idx1]) {
                    maxCount[idx1] = maxCount[idx2] + 1;
                    nextIdx[idx1] = idx2;
                }
            }
        }
        if(overallMaxCount < maxCount[idx1]) {
            overallMaxCount = maxCount[idx1];
            startIdx = idx1;
        }
    }

    while(startIdx != -1) {
        ans.push_back(words[startIdx]);
        startIdx = nextIdx[startIdx];
    }

    return ans;
}

// DAY 17 (75. Sort Colors)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void sortColors(vector<int>& nums) {
    int st = 0, end = nums.size() - 1, curr = 0;
    while(curr <= end) {
        if(nums[curr] == 0) {
            swap(nums[st++], nums[curr++]);
        } else if(nums[curr] == 2) {
            swap(nums[end--], nums[curr]);
        } else {
            curr++;
        }
    }
}

// DAY 18 (1931. Painting a Grid With Three Different Colors)=============================================================

// Time Complexity = O(n * m * 4^m)
// Space Complexity = O(n*m + n*(4^m))

const int MOD = 1e9 + 7;
int stateCache[1001][1025];
int colorTheGridDFS(int r, int c, int m, int n, int prevState, int currState) {
    if(c == n) {
        return 1;
    }
    if(r == m) {
        return colorTheGridDFS(0, c + 1, m, n, currState, 0);
    }
    if(r == 0 && stateCache[c][prevState] != -1) {
        return stateCache[c][prevState];
    }
    int upColor = currState & 3;
    int leftColor = (prevState >> ((m - r - 1) * 2)) & 3;
    int totalWays = 0;
    for(int currColor = 1; currColor <= 3; currColor++) {
        if(currColor != upColor && currColor != leftColor) {
            totalWays = (totalWays % MOD + (colorTheGridDFS(r + 1, c, m, n, prevState, (currState << 2) | currColor)) % MOD) % MOD;
        }
    }
    if(r == 0) {
        stateCache[c][prevState] = totalWays;
    }
    return totalWays;
}

int colorTheGrid(int m, int n) {
    memset(stateCache, -1, sizeof(stateCache));
    return colorTheGridDFS(0, 0, m, n, 0, 0) % MOD;
}

// DAY 19 (3024. Type of Triangle)==========================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

string triangleType(vector<int>& nums) {
    bool isTriangle = (nums[0] < nums[1] + nums[2]) && (nums[1] < nums[0] + nums[2]) && (nums[2] < nums[0] + nums[1]);
    if(!isTriangle) {
        return "none";
    }
    bool isEquilateral = nums[0] == nums[1] && nums[0] == nums[2];
    bool isIsosceles = nums[0] == nums[1] || nums[0] == nums[2] || nums[1] == nums[2];
    if(isEquilateral) {
        return "equilateral";
    }
    if(isIsosceles) {
        return "isosceles";
    }
    return "scalene";
}

// DAY 20 (3355. Zero Array Transformation I)==============================================================================

// Time Complexity = O(n + q)
// Space Complexity = O(n)

bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    int size = nums.size();
    vector<int> netSum(size + 1, 0);
    for(vector<int> &query : queries) {
        int l = query[0];
        int r = query[1];
        netSum[l] += -1;
        netSum[r + 1] += 1;
    }
    for(int idx = 1; idx < size; idx++) {
        netSum[idx] += netSum[idx - 1];
    }
    for(int idx = 0; idx < size; idx++) {
        if(nums[idx] + netSum[idx] > 0) {
            return false;
        }
    }
    return true;
}

// DAY 21 (73. Set Matrix Zeroes)==============================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

void setZeroes(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    vector<bool> isZeroRow(rows, false), isZeroCol(cols, false);
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(matrix[row][col] == 0) {
                isZeroRow[row] = true;
                isZeroCol[col] = true;
            }
        }
    }
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(isZeroRow[row] || isZeroCol[col]) {
                matrix[row][col] = 0;
            }
        }
    }
}

// DAY 24 (2942. Find Words Containing Character)==========================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n)

vector<int> findWordsContaining(vector<string>& words, char x) {
    vector<int> ans;
    for(int idx = 0; idx < words.size(); idx++) {
        for(char c : words[idx]) {
            if(c == x) {
                ans.push_back(idx);
                break;
            }
        }
    }
    return ans;
}
