
// Time Complexity = O(n)
// Space Complexity = O(n/k)

class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k) 
    {
        int n = word.size();
        unordered_map<string,int> mp;
        int maxCnt = 0;
        for(int i = 0; i < n; i+=k)
            maxCnt = max(maxCnt, ++mp[word.substr(i, k)]);
        return n/k - maxCnt;
    }
};
