
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
