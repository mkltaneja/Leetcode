
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
