
// Time Complexity = O(n+26)
// Time Complexity = O(26)

class Solution {
public:
    int findPermutationDifference(string s, string t) 
    {
        int n = s.size();
        vector<int> mp1(26, -1), mp2(26, -1);
        int ans = 0;
        for(int i = 0; i < n; i++)
            mp1[s[i]-'a'] = i, mp2[t[i]-'a'] = i;
        for(int i = 0; i < 26; i++)
            ans += abs(mp1[i] - mp2[i]);
        
        return ans;
    }
};
