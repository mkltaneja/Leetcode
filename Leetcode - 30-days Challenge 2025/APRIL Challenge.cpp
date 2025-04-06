
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
