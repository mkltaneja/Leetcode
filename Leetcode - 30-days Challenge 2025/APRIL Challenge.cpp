
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
