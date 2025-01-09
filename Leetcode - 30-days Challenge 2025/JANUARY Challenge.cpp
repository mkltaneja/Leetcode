
// DAY 1 (1422. Maximum Score After Splitting a String)=====================================================

// Time Complexcity = O(n)
// Space Complexcity = O(1)

int maxScore(string s) {
    int totalOnes = 0;
    for(char c : s) {
        totalOnes += c - '0';
    }

    s.pop_back();
    int maxScore = 0;
    int leftZeros = 0;
    int rightOnes = totalOnes;
    for(char c : s) {
        leftZeros += c == '0';
        rightOnes -= c == '1';
        maxScore = max(maxScore, leftZeros + rightOnes);
    }

    return maxScore;
}

// DAY 2 (2559. Count Vowel Strings in Ranges)=================================================================

// Time Complexity = O(n + q)
// Space Complexity = O(n + q)

bool isVowel(char c) {
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return true;
    }
    return false;
}

vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
    int wsize = words.size();
    int qsize = queries.size();
    vector<int> prefCount(wsize, 0);
    vector<int> ans(qsize);
    for(int idx = 0; idx < wsize; idx++) {
        prefCount[idx] = (isVowel(words[idx][0]) && isVowel(words[idx].back())) + (idx? prefCount[idx-1] : 0);
    }

    for(int idx = 0; idx < qsize; idx++) {
        int left = queries[idx][0];
        int right = queries[idx][1];
        ans[idx] = prefCount[right] - (left? prefCount[left-1] : 0);
    }

    return ans;
}

// DAY 3 (2270. Number of Ways to Split Array)==============================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int waysToSplitArray(vector<int>& nums) {
    int size = nums.size();
    vector<long long> prefixSum(size, 0);
    for(int idx = 0; idx < size; idx++) {
        prefixSum[idx] = (idx? prefixSum[idx-1] : 0) + nums[idx];
    }
    long long postfixSum = 0, totalSplits = 0;
    for(int idx = size-1; idx >= 1; idx--) {
        postfixSum += nums[idx];
        if(postfixSum <= prefixSum[idx-1]) {
            totalSplits++;
        }
    }

    return totalSplits;
}

// DAY 4 (1930. Unique Length-3 Palindromic Subsequences)==========================================================

// Time Complexity = O(n + 26*26)
// Space Complexity = O(n*26)

int getTotalUniqueCharactersBetween(int start, int end, vector<vector<int>> &arr) {
    int uniqueChars = 0;
    for(int idx = 0; idx < 26; idx++) {
        uniqueChars += (arr[end - 1][idx] - arr[start][idx]) > 0;
    }
    return uniqueChars;
}

int countPalindromicSubsequence(string s) {
    int size = s.size();
    vector<vector<int>> firstLastPos(26, vector<int>(2, -1));
    vector<int> charMap(26, 0);
    vector<vector<int>> prefixUniqueCount(size, vector<int>(26, 0));
    int totalCount = 0;
    for(int idx = 0; idx < size; idx++) {
        if(firstLastPos[s[idx]-'a'][0] == -1) {
            firstLastPos[s[idx]-'a'][0] = idx;
        }
        else {
            firstLastPos[s[idx]-'a'][1] = idx;
        }
        ++charMap[s[idx]-'a'];
        prefixUniqueCount[idx] = charMap;
    }

    for(vector<int> &pair : firstLastPos) {
        int firstPos = pair[0];
        int lastPos = pair[1];
        if(lastPos != -1) {
            totalCount += getTotalUniqueCharactersBetween(firstPos, lastPos, prefixUniqueCount);
        }
    }

    return totalCount;
}

// DAY 5 (2381. Shifting Letters II)=================================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(n)

string shiftingLetters(string s, vector<vector<int>>& shifts) {
    int size = s.size();
    vector<int> netShift(size+1, 0);
    for(vector<int> &shift : shifts) {
        int start = shift[0];
        int end = shift[1];
        int dir = shift[2]? 1 : -1;
        netShift[start] += dir;
        netShift[end+1] += -1 * dir;
    }
    for(int idx = 0; idx < size; idx++) {
        netShift[idx] += idx? netShift[idx-1] : 0;
        netShift[idx] = (netShift[idx] % 26 + 26) % 26;

        s[idx] = char((((s[idx] - 'a') + netShift[idx]) % 26) + 'a');
    }

    return s;
}

// DAY 6 (1769. Minimum Number of Operations to Move All Balls to Each Box)====================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> minOperations(string boxes) {
    int size = boxes.size();
    int leftOnes = 0, leftJumps = 0, rightOnes = 0, rightJumps = 0;
    vector<int> answer(size, 0);
    for(int left = 0, right = size-1; left < size; left++, right--) {
        answer[left] += leftJumps;
        answer[right] += rightJumps;

        leftOnes += boxes[left] == '1';
        rightOnes += boxes[right] == '1';

        leftJumps += leftOnes;
        rightJumps += rightOnes;
    }

    return answer;
}

// DAY 7 (1408. String Matching in an Array)========================================================================

// Time Complexity = O()
// Space Complexity = O(n^2*m^2)

bool isSubstring(string &word1, string &word2) {
    if(word2.size() <= word1.size()) {
        return false;
    }

    for(int idx = 0; idx <= word2.size()-word1.size(); idx++) {
        if(word1 == word2.substr(idx, word1.size())) {
            return true;
        }
    }

    return false;
}

vector<string> stringMatching(vector<string>& words) {
    int size = words.size();
    vector<string> ans;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = 0; idx2 < size; idx2++) {
            if(isSubstring(words[idx1], words[idx2])) {
                ans.push_back(words[idx1]);
                break;
            }
        }
    }
    return ans;
}

// DAY 8 (3042. Count Prefix and Suffix Pairs I)==============================================================

// Time Complexity = O(n^2 * m1)
// Space Complexity = O(1)

bool isPrefixAndSuffix(string &word1, string &word2) {
    int size1 = word1.size(), size2 = word2.size();
    if(size2 < size1) {
        return false;
    }
    return word1 == word2.substr(0, size1) && word1 == word2.substr(size2-size1);
}

int countPrefixSuffixPairs(vector<string>& words) {
    int size = words.size();
    int pairs = 0;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1+1; idx2 < size; idx2++) {
            if(isPrefixAndSuffix(words[idx1], words[idx2])) {
                pairs++;
            }
        }
    }
    return pairs;
}

// DAY 9 (2185. Counting Words With a Given Prefix)===========================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

int prefixCount(vector<string>& words, string pref) {
    int totalWords = 0;
    for(string word : words) {
        totalWords += word.size() >= pref.size() && word.substr(0, pref.size()) == pref;
    }
    return totalWords;
}
