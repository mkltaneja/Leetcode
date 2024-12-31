
// DAY 1 (1346. Check If N and Its Double Exist)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool checkIfExist(vector<int>& arr) {
    unordered_set<int> numSet;
    for(int num : arr) {
        if(numSet.count(num * 2) || ((num & 1 ^ 1) && (numSet.count(num >> 1))))
            return true;
        numSet.insert(num);
    }
    return false;
}

// DAY 2 (1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence)================================================

// Time Complexity = O(count(words) * searchWord.size())
// Space Complexity = O(sentence.size())

int isPrefixOfWord(string sentence, string searchWord) {
    stringstream ss(sentence);
    string word;
    int index = 1;
    while(getline(ss, word, ' ')) {
        if(word.size() >= searchWord.size() && word.substr(0, searchWord.size()) == searchWord) {
            return index;
        }
        index++;
    }
    return -1;
}

// DAY 3 (2109. Adding Spaces to a String)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string addSpaces(string s, vector<int>& spaces) {
    string ans = "";
    for(int sidx = 0, arrIdx = 0; sidx < s.size(); sidx++) {
        if(arrIdx < spaces.size() && sidx == spaces[arrIdx]) {
            ans += " ";
            arrIdx++;
        }
        ans += s[sidx];
    }
    return ans;
}

// DAY 4 (2825. Make String a Subsequence Using Cyclic Increments)===============================================

// Time Complexity = O(min(n, m))
// Space Complexity = O(1)

char getNext(char c) {
    return char((((c - 'a') + 1) % 26) + 'a');
}

bool canMakeSubsequence(string str1, string str2) {
    int size1 = str1.size(), size2 = str2.size();
    if(size2 > size1) {
        return false;
    }
    int idx1 = 0, idx2 = 0;
    while(idx1 < str1.size() && idx2 < str2.size()) {
        if(str2[idx2] == str1[idx1] || str2[idx2] == getNext(str1[idx1])) {
            idx2++;
        }
        idx1++;
    }
    return idx2 == str2.size();
}

// DAY 5 (2337. Move Pieces to Obtain a String)==================================================================================

// Time Complexity = O(min(n, m))
// Space Complexity = O(1)

bool canChange(string start, string target) {
    int sitr = 0, titr = 0;
    int size1 = start.size(), size2 = target.size();
    while(sitr < size1 || titr < size2) {
        while(sitr < size1 && start[sitr] == '_') {
            sitr++;
        }
        while(titr < size2 && target[titr] == '_') {
            titr++;
        }

        if(sitr == size1 || titr == size2) {
            break;
        }

        if(start[sitr] != target[titr]) {
            return false;
        }
        if((start[sitr] == 'L' && sitr < titr) || (start[sitr] == 'R' && sitr > titr)) {
            return false;
        }
        sitr++, titr++;
    }
    return sitr == size1 && titr == size2;
}

// DAY 6 (2554. Maximum Number of Integers to Choose From a Range I)=================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(m)

int maxCount(vector<int>& banned, int n, int maxSum) {
    unordered_set<int> bannedSet;
    int currSum = 0, totalNums = 0;
    for(int num : banned) {
        bannedSet.insert(num);
    }
    for(int num = 1; num <= n && currSum + num <= maxSum; num++) {
        if(!bannedSet.count(num)) {
            currSum += num;
            totalNums++;
        }
    }

    return totalNums;
}

// DAY 8 (2054. Two Best Non-Overlapping Events)================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

int upperBound(vector<vector<int>> &events, int lo, int hi, int val) {
    while(lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if(events[mid][0] <= val) {
            lo = mid + 1;
        }
        else {
            hi = mid;
        }
    }
    return lo;
}

int maxTwoEvents(vector<vector<int>>& events) {
    int maxSum = 0;
    sort(events.begin(), events.end());
    for(int idx = events.size()-1; idx >= 0; idx--) {
        int startTime = events[idx][0];
        int endTime = events[idx][1];
        int value = events[idx][2];

        int nextStartIdx = upperBound(events, idx + 1, events.size(), endTime);
        int nextMaxVal = nextStartIdx == events.size()? 0 : events[nextStartIdx][2];
        maxSum = max(maxSum, value + nextMaxVal);
        events[idx][2] = max(events[idx][2], (idx + 1 < events.size())? events[idx+1][2] : 0);
    }

    return maxSum;
}

// DAY 9 (3152. Special Array II)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) {
    vector<int> seqCnt(nums.size(), 0);
    vector<bool> ans(queries.size());
    seqCnt[0] = 1;
    for(int idx = 1; idx < nums.size(); idx++) {
        seqCnt[idx] = seqCnt[idx-1] + ((nums[idx] & 1) ^ (nums[idx-1] & 1));
    }

    for(int idx = 0; idx < queries.size(); idx++) {
        int left = queries[idx][0], right = queries[idx][1];
        int expectedNums = right - left + 1;
        int actualNums = seqCnt[right] - seqCnt[left] + 1;

        ans[idx] = expectedNums == actualNums;
    }

    return ans;
}

// DAY 10 (2981. Find Longest Special Substring That Occurs Thrice I)===========================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int maximumLength(string s) {
    unordered_map<string,int> subCnt;
    int maxLen = -1;
    for(int idx1 = 0, idx2 = idx1; idx1 < s.size(); ) {
        string sub = "";
        while(idx2 < s.size() && s[idx2] == s[idx1]) {
            sub += s[idx2++];
        }

        if(sub.size() >= 3) {
            maxLen = max(maxLen, (int)sub.size()-2);
        }
        if(++subCnt[sub] >= 3) {
            maxLen = max(maxLen, (int)sub.size());
        }
        sub.pop_back();
        if(!sub.empty()) {
            subCnt[sub] += 2;
            if(subCnt[sub] >= 3) {
                maxLen = max(maxLen, (int)sub.size());
            }
        }
        idx1 = idx2;
    }
    return maxLen;
}

// DAY 11 (2779. Maximum Beauty of an Array After Applying Operation)==============================================================

// APPROACH 1 (Sorting)

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

int maximumBeauty(vector<int>& nums, int k) {
    int size = nums.size();
    int maxLen = 1;
    sort(nums.begin(), nums.end());
    for(int curr = 1, prev = 0; curr < size; ) {
        if(nums[curr] - k <= nums[prev] + k) {
            maxLen = max(maxLen, curr - prev + 1);
            curr++;
        } else {
            prev++;
        }
    }

    return maxLen;
}

// APPROACH 2 (Prefix Sum)

// Time Complexity = O(2*n + M)
// Space Complexity = O(n)

int maximumBeauty(vector<int>& nums, int k) {
    int size = nums.size();
    int maxEle = *max_element(nums.begin(), nums.end()) + 2*k + 2;
    int maxLen = 1, len = 0;
    vector<int> numCnt(maxEle, 0);
    for(int idx = 0; idx < size; idx++) {
        numCnt[nums[idx]]++;
        numCnt[nums[idx] + 2*k + 1]--;
    }
    for(int num = 0; num < maxEle; num++) {
        len += numCnt[num];
        maxLen = max(maxLen, len);
    }

    return maxLen;
}

// DAY 12 (2558. Take Gifts From the Richest Pile)==========================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

long long pickGifts(vector<int>& gifts, int k) {
    long long totalGifts = 0;
    priority_queue<int> pq;
    for(int gift : gifts) {
        pq.push(gift);
    }
    while(k--) {
        int remGifts = sqrt(pq.top());
        pq.pop();

        if(remGifts) {
            pq.push(remGifts);
        }
    }
    while(!pq.empty()) {
        totalGifts += pq.top();
        pq.pop();
    }

    return totalGifts;
}

// DAY 13 (2593. Find Score of an Array After Marking All Elements)==========================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

long long findScore(vector<int>& nums) {
    int size = nums.size();
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minPq;
    long long score = 0;
    vector<bool> isMarked(size, false);
    for(int idx = 0; idx < size; idx++) {
        minPq.push({nums[idx], idx});
    }

    while(true) {
        while(!minPq.empty() && isMarked[minPq.top().second]) {
            minPq.pop();
        }
        if(minPq.empty()) {
            break;
        }
        int num = minPq.top().first;
        int idx = minPq.top().second;
        score += num;

        if(idx) {
            isMarked[idx-1] = true;
        }
        isMarked[idx] = true;
        if(nums.size()-idx-1) {
            isMarked[idx+1] = true;
        }
    }
    return score;
}

// DAY 14 (2762. Continuous Subarrays)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool isValidSubarray(int num, unordered_map<int,int> &numCnt) {
    int validNums = 0;
    for(int pairNum = num - 2; pairNum <= num + 2; pairNum++) {
        validNums += numCnt.count(pairNum);
    }
    return numCnt.size() == validNums;
}

long long continuousSubarrays(vector<int>& nums) {
    unordered_map<int,int> numCnt;
    long long totalSubarrays = 0;
    for(int curr = 0, prev = 0; curr < nums.size(); curr++) {
        numCnt[nums[curr]]++;
        while(!isValidSubarray(nums[curr], numCnt)) {
            if(--numCnt[nums[prev++]] == 0) {
                numCnt.erase(nums[prev-1]);
            }
        }
        totalSubarrays += curr - prev + 1;
    }
    return totalSubarrays;
}

// DAY 15 (1792. Maximum Average Pass Ratio)===========================================================================

// Time Complexity = O(n*logn + elogn)
// Time Complexity = O(n)

double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
    priority_queue<pair<double, pair<int,int>>> maxPq;
    double maxAvPassRatio = 0.0;
    for(vector<int> class_ : classes) {
        int pass = class_[0];
        int total = class_[1];
        double currRatio = 1.0 * pass / total;
        double nextRatio = 1.0 * (pass + 1) / (total + 1);
        maxPq.push({nextRatio - currRatio, {pass, total}});
    }

    while(extraStudents--) {
        double diff = maxPq.top().first;
        int pass = maxPq.top().second.first;
        int total = maxPq.top().second.second;
        double currRatio = 1.0 * (pass + 1) / (total + 1);
        double nextRatio = 1.0 * (pass + 2) / (total + 2);
        maxPq.pop();

        maxPq.push({nextRatio - currRatio, {pass + 1, total + 1}});
    }

    while(!maxPq.empty()) {
        int pass = maxPq.top().second.first;
        int total = maxPq.top().second.second;
        maxPq.pop();
        maxAvPassRatio += 1.0 * pass / total;
    }
    maxAvPassRatio /= classes.size();

    return maxAvPassRatio;
}

// DAY 16 (3264. Final Array State After K Multiplication Operations I)=======================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> minPq;
    int size = nums.size();
    for(int idx = 0; idx < size; idx++) {
        minPq.push({nums[idx], idx});
    }

    while(k--) {
        int num = minPq.top().first;
        int idx = minPq.top().second;
        minPq.pop();

        num *= multiplier;
        nums[idx] = num;
        minPq.push({num, idx});
    }
    
    return nums;
}

// DAY 17 (2182. Construct String With Repeat Limit)===================================================================

// Time Complexity = O(n + n*log26)
// Space Complexity = O(n)

string repeatLimitedString(string s, int repeatLimit) {
    priority_queue<pair<char,int>> maxPq;
    vector<int> charFreq(26, 0);
    string repeatLimitedString = "";
    char lastChar = '#';
    int lastFreq = 0;
    for(char c : s) {
        charFreq[c-'a']++;
    }
    for(int idx = 0; idx < 26; idx++) {
        if(charFreq[idx]) {
            maxPq.push({char(idx + 'a'), charFreq[idx]});
        }
    }
    while(!maxPq.empty()) {
        int limit = repeatLimit;
        char currChar = maxPq.top().first;
        int currFreq = maxPq.top().second;
        maxPq.pop();
        while(limit-- && currFreq) {
            repeatLimitedString += currChar;
            currFreq--;
        }
        if(currFreq && !maxPq.empty()) {
            char nextChar = maxPq.top().first;
            int nextFreq = maxPq.top().second;
            maxPq.pop();
            repeatLimitedString += nextChar;
            if(--nextFreq) {
                maxPq.push({nextChar, nextFreq});
            }
            maxPq.push({currChar, currFreq});
        }
    }
    return repeatLimitedString;
}

// DAY 18 (1475. Final Prices With a Special Discount in a Shop)===============================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n)

vector<int> finalPrices(vector<int>& prices) {
    int size = prices.size();
    vector<int> answer(size);
    for(int idx1 = 0; idx1 < size; idx1++) {
        answer[idx1] = prices[idx1];
        int idx2 = idx1 + 1;
        while(idx2 < size && prices[idx2] > prices[idx1]) {
            idx2++;
        }
        if(idx2 < size) {
            answer[idx1] -= prices[idx2];
        }
    }
    return answer;
}


// DAY 23 (2471. Minimum Number of Operations to Sort a Binary Tree by Level)============================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int countSwaps(vector<pair<int,int>> &nodes, vector<pair<int,int>> &sortedNodes) {
    int swaps = 0;
    for(int idx = 0; idx < nodes.size(); idx++) {
        int tempIdx = idx;
        while(nodes[tempIdx].first != sortedNodes[tempIdx].first) {
            swap(nodes[tempIdx].first, nodes[sortedNodes[tempIdx].second].first);
            tempIdx = sortedNodes[tempIdx].second;
            swaps++;
        }
    }
    return swaps;
}

int minimumOperations(TreeNode* root) {
    queue<pair<TreeNode*, int>> que;
    que.push({root, 0});
    int minSwaps = 0;

    while(!que.empty()) {
        int size = que.size();
        vector<pair<int,int>> nodes;
        int childIdx = 0;
        while(size--) {
            TreeNode* node = que.front().first;
            int idx = que.front().second;
            que.pop();
            nodes.push_back({node->val, idx});
            if(node->left) {
                que.push({node->left, childIdx++});
            }
            if(node->right) {
                que.push({node->right, childIdx++});
            }
        }

        vector<pair<int,int>> sortedNodes = nodes;
        sort(sortedNodes.begin(), sortedNodes.end());
        int swaps = countSwaps(nodes, sortedNodes);
        minSwaps += swaps;
    }

    return minSwaps;
}

// DAY 25 (515. Find Largest Value in Each Tree Row)===========================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> largestValues(TreeNode* root) {
    vector<int> maxVals;
    if(!root) {
        return maxVals;
    }
    queue<TreeNode*> que;
    que.push(root);

    while(!que.empty()) {
        int size = que.size();
        int maxLevelVal = INT_MIN;
        while(size--) {
            TreeNode* node = que.front();
            que.pop();

            maxLevelVal = max(maxLevelVal, node->val);
            if(node->left) {
                que.push(node->left);
            }
            if(node->right) {
                que.push(node->right);
            }
        }
        maxVals.push_back(maxLevelVal);
    }
    return maxVals;
}

// DAY 26 (494. Target Sum)=========================================================================

// APPROACH 1 (All subsequences) -> TLE

// Time Complexity = O(2^n * n)
// Space Complexity = O(1)

int findTargetSumWays(vector<int>& nums, int target) {
    int size = nums.size();
    int totalExpressions = 0;
    for(int mask = 0; mask < (1 << size); mask++) {
        int sum = 0;
        for(int idx = 0; idx < size; idx++) {
            sum += nums[idx] * (((mask >> idx) & 1)? 1 : -1);
        }
        totalExpressions += sum == target;
    }
    return totalExpressions;
}

// APPROACH 2 (Target sum of the difference)

// Time Complexity = O(n * d)
// Space Complexity = O(d)

int findTargetSumWays(vector<int>& nums, int target) {
    int sum = accumulate(nums.begin(), nums.end(), 0);
    int diff = sum - target;
    if(diff < 0 || diff & 1) {
        return 0;
    }
    diff >>= 1;
    vector<int> cache(diff + 1, 0);
    cache[0] = 1;
    for(int num : nums) {
        for(int sum = diff; sum >= num; sum--) {
            cache[sum] += cache[sum - num];
        }
    }

    return cache[diff];
}

// DAY 27 (1014. Best Sightseeing Pair)===============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxScoreSightseeingPair(vector<int>& values) {
    int currMaxVal = 0, maxScore = INT_MIN;
    for(int idx = 0; idx < values.size(); idx++) {
        int currVal = values[idx] - idx;
        maxScore = max(maxScore, currVal + currMaxVal);
        currMaxVal = max(currMaxVal, values[idx] + idx);
    }
    return maxScore;
}

// DAY 30 (2466. Count Ways To Build Good Strings)=====================================================================

// Time Complexity = O(high)
// Space Complexity = O(high)

int MOD = 1e9 + 7;
int countGoodStrings(int low, int high, int zero, int one) {
    vector<int> cache(high + 1, 0);
    cache[0] = 1;
    int totalStrings = 0;
    for(int len = min(zero, one); len <= high; len++) {
        if(len >= zero) {
            cache[len] = (cache[len] % MOD + cache[len - zero] % MOD) % MOD;
        }
        if(len >= one) {
            cache[len] = (cache[len] % MOD + cache[len - one] % MOD) % MOD;
        }
    }
    for(int len = low; len <= high; len++) {
        totalStrings = (totalStrings % MOD + cache[len] % MOD) % MOD;
    }

    return totalStrings;
}

// DAY 31 (983. Minimum Cost For Tickets)==============================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

int mincostTickets(vector<int>& days, vector<int>& costs) {
    int TOTAL_DAYS = 365;
    vector<int> minCost(TOTAL_DAYS + 2, 0);
    for(int idx = days.size()-1, day = TOTAL_DAYS; day; day--) {
        if(idx >= 0 && days[idx] == day) {
            int oneDayPassCost = costs[0] + (day + 1 <= TOTAL_DAYS + 1? minCost[day + 1] : 0);
            int sevenDayPassCost = costs[1] + (day + 7 <= TOTAL_DAYS + 1? minCost[day + 7] : 0);
            int thirtyDayPassCost = costs[2] + (day + 30 <= TOTAL_DAYS + 1? minCost[day + 30] : 0);

            minCost[day] = min({oneDayPassCost, sevenDayPassCost, thirtyDayPassCost});
            idx--;
        }
        else {
            minCost[day] = minCost[day + 1];
        }
    }
    return minCost[1];
}
