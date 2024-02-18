
// Time Complexity = O(n * n * m)
// Space Complexity = O(1)

class Solution {
public:
    int countPrefixSuffixPairs(vector<string>& words) 
    {
        int n = words.size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                int m1 = words[i].size(), m2 = words[j].size();
                if(m1 <= m2 && words[i] == words[j].substr(0, m1) && words[i] == words[j].substr(m2-m1))
                    ans++;
            }
        }
        return ans;
    }
};
