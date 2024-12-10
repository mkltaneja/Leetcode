
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
