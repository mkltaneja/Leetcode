// Time Complexity = O(n + 26*log26)
// Space Complexity = O(26)

class Solution {
public:
    int minimumPushes(string word) 
    {
        int n = word.size();
        int ans = 0;
        vector<int> f(26);
        for(int i = 0; i < n; i++)
            f[word[i]-'a']++;
        sort(f.rbegin(), f.rend());

        for(int i = 0; i < 26 && f[i]; i++)
        {
            int t = i/8 + 1;
            ans += t*f[i];
        }
        
        return ans;
    }
};
