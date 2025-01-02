
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
