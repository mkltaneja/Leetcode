
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
