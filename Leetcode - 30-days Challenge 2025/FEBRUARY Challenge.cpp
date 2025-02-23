
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

// DAY 5 (1790. Check if One String Swap Can Make Strings Equal)==================================================================

// time Complexity = O(n)
// Space Complexity = O(1)

bool areAlmostEqual(string s1, string s2) {
    int invalidIdx1 = -1, invalidIdx2 = -1;
    for(int idx = 0; idx < s1.size(); idx++) {
        if(s1[idx] != s2[idx]) {
            if(invalidIdx1 == -1) {
                invalidIdx1 = idx;
            }
            else if(invalidIdx2 == -1) {
                invalidIdx2 = idx;
            }
            else {
                return false;
            }
        }
    }
    if(invalidIdx1 != -1) {
        if(invalidIdx2 == -1) {
            return false;
        }
        swap(s1[invalidIdx1], s1[invalidIdx2]);
    }

    return s1 == s2;
}

// DAY 6 (1726. Tuple with Same Product)==============================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int tupleSameProduct(vector<int>& nums) {
    int tuples = 0;
    int size = nums.size();
    unordered_map<int,int> prodCount;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1+1; idx2 < size; idx2++) {
            int prod = nums[idx1] * nums[idx2];
            prodCount[prod]++;
        }
    }
    for(auto pc : prodCount) {
        int pairs = pc.second;
        tuples += pairs * (pairs - 1) / 2; // nC2
    }
    return 8 * tuples;
}

// DAY 7 (3160. Find the Number of Distinct Colors Among the Balls)==========================================================

// Time Complexity = O(q)
// Space Complexity = O(q)

vector<int> queryResults(int limit, vector<vector<int>>& queries) {
    unordered_map<int,int> color;
    vector<int> ans;
    unordered_map<int,int> colorCnt;
    for(vector<int> &query : queries) {
        int currentColor = color[query[0]];
        int newColor = query[1];
        if(currentColor && --colorCnt[currentColor] == 0) {
            colorCnt.erase(currentColor);
        }
        colorCnt[newColor]++;
        color[query[0]] = newColor;
        ans.push_back(colorCnt.size());
    }
    return ans;
}

// DAY 8 (2349. Design a Number Container System)=============================================================

// APPROACH 1 (Using Map of Set)

// Time Complexity = O(q*logq)
// Space Complexity = O(q)

class NumberContainers {
public:

    unordered_map<int,int> idxNum;
    unordered_map<int,set<int>> numIdx;
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        numIdx[idxNum[index]].erase(index);
        numIdx[number].insert(index);
        idxNum[index] = number;
    }
    
    int find(int number) {
        return numIdx[number].empty()? -1 : *numIdx[number].begin();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

// APPROACH 2 (Using Map of Min Heap)

// Time Complexity = O(q*logq)
// Space Complexity = O(q)

class NumberContainers {
public:

    unordered_map<int,int> idxNum;
    unordered_map<int,priority_queue<int, vector<int>, greater<int>>> numIdx;
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        numIdx[number].push(index);
        idxNum[index] = number;
    }
    
    int find(int number) {
        priority_queue<int, vector<int>, greater<int>> &minPq = numIdx[number];
        while(!minPq.empty() && idxNum[minPq.top()] != number) {
            minPq.pop();
        }
        return minPq.empty()? -1 : minPq.top();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

// DAY 9 (2364. Count Number of Bad Pairs)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

long long countBadPairs(vector<int>& nums) {
    int size = nums.size();
    long long totalPairs = 0;
    unordered_map<int,int> diffCnt, pairCnt;
    for(int idx = size-1; idx >= 0; idx--) {
        int diff = idx - nums[idx];
        pairCnt[diff] += (size - idx - 1) - diffCnt[diff]++;
    }
    for(auto &pair : pairCnt) {
        totalPairs += pair.second;
    }

    return totalPairs;
}

// DAY 10 (3174. Clear Digits)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string clearDigits(string s) {
    string ans = "";
    for(char c : s) {
        if(isdigit(c)) {
            if(!ans.empty()) {
                ans.pop_back();
            }
        }
        else {
            ans += c;
        }
    }
    return ans;
}

// DAY 11 (1910. Remove All Occurrences of a Substring)===================================================

// METHOD 1 (Naive)

// Time Complexity = O(n*m)
// Space Complexity = O(n)

void removeSuffix(int size, string &ans) {
    while(size--) {
        ans.pop_back();
    }
}

string removeOccurrences(string s, string part) {
    int psize = part.size();
    string ans = "";
    for(char c : s) {
        ans += c;
        if(ans.size() >= psize && ans.substr(ans.size() - psize, psize) == part) {
            removeSuffix(psize, ans);
        }
    }
    return ans;
}

// METHOD 2 (More concise)

// Time Complexity = O(n*m)
// Space Complexity = O(n)

string removeOccurrences(string s, string part) {
    while(s.size() >= part.size() && s.find(part) != string::npos) {
        s.erase(s.find(part), part.size());
    }
    return s;
}

// DAY 12 (2342. Max Sum of a Pair With Equal Sum of Digits)=====================================================================

// Time Complexity = O(n * log10(x))
// Space Complexity = O(1)

const int MAX_DIG_SUM = 82;

int getDigitsSum(int num) {
    int sum = 0;
    while(num) {
        sum += num % 10;
        num /= 10;
    }
    return sum;
}

int maximumSum(vector<int>& nums) {
    vector<vector<int>> digSum(MAX_DIG_SUM, {0, 0});
    int maxSum = -1;
    for(int num : nums) {
        int sum = getDigitsSum(num);
        if(digSum[sum][0] < num) {
            digSum[sum][1] = digSum[sum][0];
            digSum[sum][0] = num;
        }
        else digSum[sum][1] = max(digSum[sum][1], num);
    }
    for(int sum = 1; sum < MAX_DIG_SUM; sum++) {
        if(digSum[sum][0] && digSum[sum][1]) {
            maxSum = max(maxSum, digSum[sum][0] + digSum[sum][1]);
        }
    }
    return maxSum;
}

// DAY 13 (3066. Minimum Operations to Exceed Threshold Value II)====================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int minOperations(vector<int>& nums, int k) {
    priority_queue<long, vector<long>, greater<long>> minPq;
    int operations = 0;
    for(int num : nums) {
        minPq.push(num);
    }

    while(minPq.size() >= 2 && minPq.top() < k) {
        long smallestNum = minPq.top();
        minPq.pop();
        long secondSmallestNum = minPq.top();
        minPq.pop();

        long newNum = smallestNum * 2 + secondSmallestNum;
        minPq.push(newNum);
        operations++;
    }

    return operations;
}

// DAY 14 (1352. Product of the Last K Numbers)=======================================================================

// Time Complexity = O(q)
// Space Complexity = O(q)

class ProductOfNumbers {
public:

    vector<int> prefProd;
    int size;
    ProductOfNumbers() {
        this->size = 0;
        prefProd = {1};
    }
    
    void add(int num) {
        if(num == 0) {
            prefProd = {1};
            size = 0;
        }
        else {
            prefProd.push_back(prefProd.back() * num);
            size++;
        }
    }
    
    int getProduct(int k) {
        if(k > size) {
            return 0;
        }
        return prefProd[size] / prefProd[size-k];
    }
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

// DAY 15 (2698. Find the Punishment Number of an Integer)================================================================

// Time Complexity = O(n * 2^log10(n))
// Space Complexity = O(log10(n))

bool isValidNum(int num, string &numSq, int idx, int currSum) {
    if(idx == numSq.size()) {
        return currSum == num;
    }

    int currNum = 0;
    for(int itr = idx; itr < numSq.size(); itr++) {
        currNum = currNum * 10 + (numSq[itr]-'0');
        if(isValidNum(num, numSq, itr + 1, currSum + currNum)) {
            return true;
        }
    }

    return false;
}

bool isValidNum(int num) {
    string numSq = to_string(num*num);
    return isValidNum(num, numSq, 0, 0);
}

int punishmentNumber(int n) {
    int ans = 0;
    for(int x = 1; x <= n; x++) {
        if(isValidNum(x)) {
            ans += x*x;
        }
    }
    return ans;
}

// DAY 16 (1718. Construct the Lexicographically Largest Valid Sequence)===================================================================

// Time Complexity = O(n! ~= 2^n)
// Space Complexity = O(n! ~= 2^n)

bool constructDistancedSequenceDFS(int idx, int numVisMask, int n, vector<int> &currSeq) {
    if(idx == currSeq.size()) {
        return true;
    }
    if(currSeq[idx]) {
        return constructDistancedSequenceDFS(idx + 1, numVisMask, n, currSeq);
    }
    for(int x = n; x >= 1; x--) {
        if(numVisMask & (1 << x)) {
            continue;
        }
        currSeq[idx] = x;
        numVisMask ^= (1 << x);
        if(x == 1) {
            if(constructDistancedSequenceDFS(idx + 1, numVisMask, n, currSeq)) {
                return true;
            }
        }
        else if(idx + x < currSeq.size() && currSeq[x + idx] == 0) {
            currSeq[idx + x] = x;
            if(constructDistancedSequenceDFS(idx + 1, numVisMask, n, currSeq)) {
                return true;
            }
            currSeq[idx + x] = 0;
        }
        currSeq[idx] = 0;
        numVisMask ^= (1 << x);
    }
    return false;
}

vector<int> constructDistancedSequence(int n) {
    vector<int> currSeq(2*n - 1, 0);
    int numVisMask = 0;
    constructDistancedSequenceDFS(0, numVisMask, n, currSeq);
    return currSeq;
}

// DAY 17 (1079. Letter Tile Possibilities)==============================================================

// Time Complexity = O(n!)
// Space Complexity = O(n*n!)

int numTilePossibilities(string tiles) {
    int size = tiles.size();
    if(size == 0) {
        return 0;
    }
    int charMask = 0;
    int totalCount = 0;
    for(int idx = 0; idx < size; idx++) {
        int mask = 1 << (tiles[idx]-'A');
        if(charMask & mask) {
            continue;
        }
        charMask ^= mask;
        string leftString = tiles.substr(0, idx);
        string rightString = tiles.substr(idx + 1);
        totalCount += numTilePossibilities(leftString + rightString) + 1;
    }
    return totalCount;
}

// DAY 19 (1415. The k-th Lexicographical String of All Happy Strings of Length n)==========================================================

// Time Complexity = O(k * n)
// Space Complexity = O(n)

const char LAST_CHAR = 'c';

bool isValidString(string &str) {
    for(int idx = 0; idx < str.size()-1; idx++) {
        if(str[idx] == str[idx+1]) {
            return false;
        }
    }
    return true;
}

bool incrementString(string &str) {
    int size = str.size();
    int idx = size - 1;
    for(; idx >= 0 && str[idx] == LAST_CHAR; idx--);
    if(idx == -1) {
        return false;
    }
    str[idx++]++;
    for(; idx < size; idx++) {
        str[idx] = 'a';
    }
    return true;
}

string getHappyString(int n, int k) {
    string res = string(n, 'a');
    k = k - (n == 1);
    for(int itr = 0; itr < k; itr++) {
        do {
            if(!incrementString(res)) {
                return "";
            }
        }
        while(!isValidString(res));
    }
    return res;
}

// DAY 20 (1980. Find Unique Binary String)=====================================================================

// APPROACH 1 (Finding 1st absent element through mask)

// Time Complexity = O(n^2)
// Space Complexity = O(n)

int binaryToNum(int n, string &str) {
    int num = 0;
    for(int idx = n-1; idx >= 0; idx--) {
        num += ((str[idx]-'0') << (n-idx-1));
    }
    return num;
}

string numToBinary(int n, int num) {
    string bin = "";
    for(int idx = 0; idx < n; idx++) {
        bin += (num & (1 << idx))? "1" : "0";
    }
    reverse(bin.begin(), bin.end());
    return bin;
}

string findDifferentBinaryString(vector<string>& nums) {
    int n = nums.size();
    int numMask = 0;
    for(int idx = 0; idx < n; idx++) {
        int num = binaryToNum(n, nums[idx]);
        if(num <= n) {
            numMask |= (1 << num);
        }
    }
    numMask = ~numMask;
    numMask = numMask & -numMask;
    int minAbsentNum = log2(numMask);
    return numToBinary(n, minAbsentNum);
}

// APPROACH 2 (Finding answer by taking inverse of specific set of bits) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(n)

string findDifferentBinaryString(vector<string>& nums) {
    string ans = "";
    for(int idx = 0; idx < nums.size(); idx++) {
        ans += char(((nums[idx][idx] - '0') ^ 1) + '0');
    }
    return ans;
}

// DAY 21 (1261. Find Elements in a Contaminated Binary Tree)===================================================================

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
public:

    void createTree(TreeNode* &node, int val) {
        if(!node) {
            return;
        }
        node->val = val;
        treeNodes.insert(val);
        createTree(node->left, 2*val + 1);
        createTree(node->right, 2*val + 2);
    }

    unordered_set<int> treeNodes;
    FindElements(TreeNode* root) {
        createTree(root, 0);
    }
    
    bool find(int target) {
        return treeNodes.count(target);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */

// DAY 23 (889. Construct Binary Tree from Preorder and Postorder Traversal)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

TreeNode* constructTree(int &preIdx, int &postIdx, vector<int>& preorder, vector<int>& postorder) {
    TreeNode* node = new TreeNode(preorder[preIdx++]);
    if(postorder[postIdx] != node->val) {
        node->left = constructTree(preIdx, postIdx, preorder, postorder);
    }
    if(postorder[postIdx] != node->val) {
        node->right = constructTree(preIdx, postIdx, preorder, postorder);
    }
    postIdx++;
    return node;
}

TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
    int preIdx = 0, postIdx = 0;
    return constructTree(preIdx, postIdx, preorder, postorder);
}
