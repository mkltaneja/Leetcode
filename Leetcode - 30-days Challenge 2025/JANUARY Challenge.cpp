
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
