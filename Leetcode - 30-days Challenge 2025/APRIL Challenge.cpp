
// DAY 1 (2140. Solving Questions With Brainpower)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

#define ll long long
long long mostPoints(vector<vector<int>>& questions) {
    int size = questions.size();
    vector<ll> maxScore(size, 0);
    maxScore[size-1] = questions[size-1][0];
    for(int idx = size-2; idx >= 0; idx--) {
        ll excScore = maxScore[idx + 1];
        ll incScore = questions[idx][0] + ((idx + questions[idx][1] + 1 < size)? maxScore[idx + questions[idx][1] + 1] : 0);
        maxScore[idx] = max(incScore, excScore);
    }
    return maxScore[0];
}

// DAY 2 (2873. Maximum Value of an Ordered Triplet I)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long maximumTripletValue(vector<int>& nums) {
    long long currMax = nums[0], maxDiff = nums[0] - nums[1], maxProd = 0;
    for(int idx = 2; idx < nums.size(); idx++) {
        maxProd = max(maxProd, maxDiff * nums[idx]);
        currMax = max(currMax, 1ll * nums[idx - 1]);
        maxDiff = max(maxDiff, currMax - nums[idx]);
    }
    return maxProd;
}

// DAY 3 (2874. Maximum Value of an Ordered Triplet II)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long maximumTripletValue(vector<int>& nums) {
    long long maxNum = nums[0], maxDiff = nums[0] - nums[1], maxProd = 0;
    for(int idx = 2; idx < nums.size(); idx++) {
        maxProd = max(maxProd, maxDiff * nums[idx]);
        maxNum = max(maxNum, 1ll * nums[idx - 1]);
        maxDiff = max(maxDiff, maxNum - nums[idx]);
    }
    return maxProd;
}

// DAY 4 (1123. Lowest Common Ancestor of Deepest Leaves)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

TreeNode* ans = nullptr;
int maxDepth = -1;

int lcaDeepestLeaves_postOrder(TreeNode* node, int depth) {
    if(!node) {
        maxDepth = max(maxDepth, depth);
        return depth;
    }

    int leftMaxDepth = lcaDeepestLeaves_postOrder(node->left, depth + 1);
    int rightMaxDepth = lcaDeepestLeaves_postOrder(node->right, depth + 1);
    if(leftMaxDepth == rightMaxDepth && leftMaxDepth == maxDepth) {
        ans = node;
    }
    return max(leftMaxDepth, rightMaxDepth);
}

TreeNode* lcaDeepestLeaves(TreeNode* root) {
    lcaDeepestLeaves_postOrder(root, 0);
    return ans;
}

// DAY 5 (1863. Sum of All Subset XOR Totals)=========================================================================================

// Time Complexity = O(2^n * n)
// Space Complexity = O(1)

int subsetXORSum(vector<int>& nums) {
    int size = nums.size();
    int totalSum = 0;
    for(int mask = 0; mask < (1 << size); mask++) {
        int currXor = 0;
        for(int idx = 0; idx < size; idx++) {
            if(mask & (1 << idx)) {
                currXor ^= nums[idx];
            }
        }
        totalSum += currXor;
    }
    return totalSum;
}

// DAY 6 (368. Largest Divisible Subset)==================================================================

// Time Complexity = O(n*logn + n^2)
// Space Complexity = O(n)

vector<int> largestDivisibleSubset(vector<int>& nums) {
    int size = nums.size();
    int maxLen = -1, startIdx = -1;
    vector<int> maxCount(size, 0), nextIdx(size, -1);
    vector<int> ans;

    sort(nums.begin(), nums.end());

    for(int idx1 = size-1; idx1 >= 0; idx1--) {
        for(int idx2 = idx1 + 1; idx2 < size; idx2++) {
            if((nums[idx2] % nums[idx1]) == 0 && maxCount[idx2] + 1 > maxCount[idx1]) {
                maxCount[idx1] = maxCount[idx2] + 1;
                nextIdx[idx1] = idx2;
            }
        }
        if(maxCount[idx1] > maxLen) {
            maxLen = maxCount[idx1];
            startIdx = idx1;
        }
    }

    while(startIdx != -1) {
        ans.push_back(nums[startIdx]);
        startIdx = nextIdx[startIdx];
    }

    return ans;
}

// DAY 7 (416. Partition Equal Subset Sum)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool canPartition(vector<int>& nums) {
    int totSum = accumulate(nums.begin(), nums.end(), 0);
    if(totSum & 1) {
        return false;
    }
    
    totSum >>= 1;
    bitset<20001> sumDp = 1;
    for(int num : nums) {
        sumDp |= (sumDp << num);
        if(sumDp.test(totSum)) {
            return true;
        }
    }

    return false;
}

// DAY 8 (3396. Minimum Number of Operations to Make Elements in Array Distinct)======================================

// APPROACH 1 (Using count map)

// Time Complexity = O(n)
// Space Complexity = O(n)

int minimumOperations(vector<int>& nums) {
    unordered_map<int,int> cntMap;
    int size = nums.size(), idx = 0, operations = 0;
    for(int num : nums) {
        cntMap[num]++;
    }
    while(cntMap.size() != (size - idx)) {
        int removals = 0;
        while(idx < size && removals < 3) {
            if(--cntMap[nums[idx]] == 0) {
                cntMap.erase(nums[idx]);
            }
            removals++;
            idx++;
        }
        operations++;
    }
    return operations;
}

// APPROACH 2 (Traversing backwardes and finding the answer optimally) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(1)

const int MAX_NUM = 101;
int minimumOperations(vector<int>& nums) {
    vector<bool> vis(MAX_NUM, false);
    for(int idx = nums.size() - 1; idx >= 0; idx--) {
        if(vis[nums[idx]]) {
            return ceil(1.0 * (idx + 1) / 3);
        }
        vis[nums[idx]] = true;
    }
    return 0;
}

// DAY 9 (3375. Minimum Operations to Make Array Values Equal to K)===================================================

// Time Complexxity = O(n)
// Space Complexxity = O(1)

int minOperations(vector<int>& nums, int k) {
    int minEle = *min_element(nums.begin(), nums.end());
    if(k > minEle) {
        return -1;
    }
    bool vis[101] = {false};
    int uniqueCount = 0;
    for(int num : nums) {
        uniqueCount += !vis[num];
        vis[num] = true;
    }
    return uniqueCount - vis[k];
}

// DAY 11 (2843. Count Symmetric Integers)========================================================================

// Time Complexity = O((high - low + 1) * log10(high))
// Space Complexity = O(log10(high))

bool isSymmetricNum(int num) {
    string numStr = to_string(num);
    int st = 0, end = numStr.size()-1;
    int sum1 = 0, sum2 = 0;
    while(st < end) {
        sum1 += numStr[st++];
        sum2 += numStr[end--];
    }
    return st > end && sum1 == sum2;
}

int countSymmetricIntegers(int low, int high) {
    int ans = 0;
    for(int num = low; num <= high; num++) {
        if(isSymmetricNum(num)) {
            ans++;
        }
    }
    return ans;
}

// DAY 12 (3272. Find the Count of Good Integers)=======================================================================

// Time Complexity = O(10^(m) * m*logm) [m = (n + 1 / 2)]
// Space Complexity = O(10^m)

#define ll long long
ll fact[11] = {1};
unordered_set<ll> vis;

void precomputeFactorials() {
    for(int dig = 1; dig <= 10; dig++) {
        fact[dig] = dig * fact[dig - 1];
    }
}

bool isKPalindrome(string &num, int k) {
    return stoll(num) % k == 0;
}

ll countPermutations(string &num, int size) {
    string tempNum = num;
    sort(tempNum.begin(), tempNum.end());
    if(vis.count(stoll(tempNum))) {
        return 0;
    }
    vis.insert(stoll(tempNum));
    int freq[10] = {0};
    ll numerator = fact[size], denomenator = 1;
    for(char dig : tempNum) {
        freq[dig - '0']++;
    }
    for(int dig = 0; dig <= 9; dig++) {
        denomenator *= fact[freq[dig]];
    }
    ll count = numerator / denomenator;
    if(freq[0]) {
        denomenator = (denomenator / fact[freq[0]]) * (fact[freq[0] - 1]);
        count -= fact[size - 1] / denomenator;
    }
    return count;
}

ll countGoodIntegersDfs(int idx, string &num, int size, int k) {
    if(idx == (size + 1) / 2) {
        if(isKPalindrome(num, k)) {
            return countPermutations(num, size);
        }
        return 0;
    }

    ll count = 0;
    for(char dig = char('0' + (idx == 0)); dig <= '9'; dig++) {
        num[idx] = dig;
        num[size - idx - 1] = dig;
        count += countGoodIntegersDfs(idx + 1, num, size, k);
    }
    num[idx] = '#';
    num[size - idx - 1] = '#';

    return count;
}

long long countGoodIntegers(int n, int k) {
    string num = string(n, '#');
    precomputeFactorials();
    return countGoodIntegersDfs(0, num, n, k);
}

// DAY 13 (1922. Count Good Numbers)=========================================================================

// Time Complexity = O(logn)
// Space Complexity = O(1)

#define ll long long
const ll MOD = 1e9 + 7;

int modularMultiplication(int num1, int num2) {
    return (num1 % MOD * num2 % MOD) % MOD;
}

int modularPower_BinaryExponentiation(ll base, ll pow) {
    int res = 1;
    while(pow) {
        if(pow & 1) {
            res = modularMultiplication(res, base);
        }
        base = modularMultiplication(base, base);
        pow >>= 1;
    }
    return res % MOD;
}

int countGoodNumbers(long long n) {
    ll odds = n / 2;
    ll evens = (n + 1) / 2;
    return modularMultiplication(modularPower_BinaryExponentiation(4ll, odds), modularPower_BinaryExponentiation(5ll, evens));
}

// DAY 14 (1534. Count Good Triplets)==================================================================

// Time Complexity = O(n^3)
// Space Complexity = O(1)

int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
    int size = arr.size(), tripletsCount = 0;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1 + 1; idx2 < size; idx2++) {
            for(int idx3 = idx2 + 1; idx3 < size; idx3++) {
                if(abs(arr[idx1] - arr[idx2]) <= a && abs(arr[idx2] - arr[idx3]) <= b && abs(arr[idx1] - arr[idx3]) <= c) {
                    tripletsCount++;
                }
            }
        }
    }
    return tripletsCount;
}

// DAY 16 (2537. Count the Number of Good Subarray)===================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

long long countGood(vector<int>& nums, int k) {
    int size = nums.size();
    long long subarraysCount = 0, currPairs = 0;
    unordered_map<int, long long> freqMap;
    for(int left = 0, right = 0; right < size; ) {
        currPairs += freqMap[nums[right++]]++;
        while(left < right && currPairs >= k) {
            currPairs -= --freqMap[nums[left++]];
            subarraysCount += size - right + 1;
        }
    }
    return subarraysCount;
}

// DAY 17 (2176. Count Equal and Divisible Pairs in an Array)=======================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(1)

int countPairs(vector<int>& nums, int k) {
    int size = nums.size();
    int pairsCount = 0;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1 + 1; idx2 < size; idx2++) {
            if((idx1 * idx2) % k == 0 && nums[idx1] == nums[idx2]) {
                pairsCount++;
            }
        }
    }
    return pairsCount;
}

// DAY 18 (38. Count and Say)=======================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

string countAndSay(int n) {
    string ans = "1";
    while(--n) {
        string curr = ans;
        string next = "";
        for(int idx = 0; idx < curr.size(); ) {
            int itr = idx;
            while(itr < curr.size() && curr[idx] == curr[itr]) {
                itr++;
            }
            int count = itr - idx;
            next += to_string(count) + curr[idx];
            idx = itr;
        }
        ans = next;
    }
    return ans;
}

// DAY 20 (781. Rabbits in Forest)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

const int MAX_RABBITS = 1001;
int numRabbits(vector<int>& answers) {
    vector<int> countMap(MAX_RABBITS, 0);
    int minRabbits = 0;
    for(int count : answers) {
        countMap[count]++;
    }
    for(int rabbits = 0; rabbits < MAX_RABBITS; rabbits++) {
        int count = countMap[rabbits];
        minRabbits += ceil(1.0 * count / (rabbits + 1)) * (rabbits + 1);
    }
    return minRabbits;
}

// DAY 21 (2145. Count the Hidden Sequences)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfArrays(vector<int>& differences, int lower, int upper) {
    long long currNum = 0, minNum = 0, maxNum = 0;
    for(int diff : differences) {
        currNum += diff;
        minNum = min(minNum, currNum);
        maxNum = max(maxNum, currNum);
    }
    int gap = (upper - lower) - (maxNum - minNum);
    return gap < 0? 0 : gap + 1;
}

// DAY 23 (1399. Count Largest Group)===========================================================================

// Time Complexity = O(n * log10(n))
// Space Complexity = O(1)

int getDigitsSum(int num) {
    int sum = 0;
    while(num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int countLargestGroup(int n) {
    int digSum[40] = {0};
    int maxSize = 0, totalGroups = 0;
    for(int x = 1; x <= n; x++) {
        int sum = getDigitsSum(x);
        if(++digSum[sum] > maxSize) {
            maxSize = digSum[sum];
            totalGroups = 1;
        } else if(digSum[sum] == maxSize) {
            totalGroups++;
        }
    }
    return totalGroups;
}

// DAY 24 (2799. Count Complete Subarrays in an Array)================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getDistinctNums(vector<int> &nums) {
    unordered_set<int> vis;
    for(int num : nums) {
        vis.insert(num);
    }
    return vis.size();
}

int countSubarraysWithAtmostKDistincts(int k, int size, vector<int> &nums) {
    int left = 0, right = 0, subarrays = 0;
    unordered_map<int,int> numCnt;
    while(right < size) {
        numCnt[nums[right]]++;
        while(numCnt.size() > k) {
            if(--numCnt[nums[left]] == 0) {
                numCnt.erase(nums[left]);
            }
            left++;
        }
        subarrays += right - left + 1;
        right++;
    }
    return subarrays;
}

int countCompleteSubarrays(vector<int>& nums) {
    int size = nums.size();
    int distinctNums = getDistinctNums(nums);
    return countSubarraysWithAtmostKDistincts(distinctNums, size, nums) - countSubarraysWithAtmostKDistincts(distinctNums - 1, size, nums);
}

// DAY 25 (2845. Count of Interesting Subarrays)=============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
    int size = nums.size(), cnt = 0;
    long long ans = 0;
    unordered_map<int,int> cntMap;
    cntMap[0] = 1;

    for(int idx = 0; idx < size; idx++) {
        cnt += ((nums[idx] % modulo) == k);
        ans += cntMap[(cnt - k + modulo) % modulo];
        cntMap[cnt % modulo]++;
    }
    return ans;
}

// DAY 26 (2444. Count Subarrays With Fixed Bounds)===============================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long countSubarrays(vector<int>& nums, int minK, int maxK) {
    long long subarrayCount = 0;
    for(int minKPtr = -1, maxKPtr = -1, startItr = -1, itr = 0; itr < nums.size(); itr++) {
        if(nums[itr] == minK) {
            minKPtr = itr;
        }
        if(nums[itr] == maxK) {
            maxKPtr = itr;
        }
        if(nums[itr] < minK || nums[itr] > maxK) {
            minKPtr = maxKPtr = startItr = itr;
        }
        subarrayCount += min(minKPtr, maxKPtr) - startItr;
    }
    return subarrayCount;
}

// DAY 27 (3392. Count Subarrays of Length Three With a Condition)=====================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

const int MAX_NUM = 101;
int countSubarrays(vector<int>& nums) {
    int subarrayCount = 0;
    for(int idx = 1; idx < nums.size()-1; idx++) {
        if(nums[idx] & 1 ^ 1) {
            subarrayCount += (nums[idx] / 2) == (nums[idx - 1] + nums[idx + 1]);
        }
    }
    return subarrayCount;
}

// DAY 28 (2302. Count Subarrays With Score Less Than K)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

#define ll long long
long long countSubarrays(vector<int>& nums, long long k) {
    int prev = 0;
    ll currScore = 0, totalSubarrays = 0, currSum = 0;
    for(int curr = 0; curr < nums.size(); curr++) {
        currSum += nums[curr];
        currScore = currSum * (curr - prev + 1);
        while(prev <= curr && currScore >= k) {
            currSum -= nums[prev++];
            currScore = currSum * (curr - prev + 1);
        }
        totalSubarrays += curr - prev + 1;
    }
    return totalSubarrays;
}

// DAY 29 (2962. Count Subarrays Where Max Element Appears at Least K Times)=======================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long countSubarrays(vector<int>& nums, int k) {
    int maxEle = *max_element(nums.begin(), nums.end());
    int maxCnt = 0;
    long long totalSubarrays = 0;
    for(int curr = 0, prev = 0; curr < nums.size(); curr++) {
        maxCnt += nums[curr] == maxEle;
        while(maxCnt - (nums[prev] == maxEle) >= k) {
            maxCnt -= nums[prev++] == maxEle;
        }
        totalSubarrays += maxCnt == k? (prev + 1) : 0;
    }
    return totalSubarrays;
}

// DAY 30 (1295. Find Numbers with Even Number of Digits)===============================================================

// Time Complexity = O(n * log10(x))
// Space Complexity = O(1)

int countDigits(int num) {
    int digits = 0;
    while(num) {
        num /= 10;
        digits++;
    }
    return digits;
}

int findNumbers(vector<int>& nums) {
    int ans = 0;
    for(int num : nums) {
        ans += countDigits(num) & 1 ^ 1;
    }
    return ans;
}
