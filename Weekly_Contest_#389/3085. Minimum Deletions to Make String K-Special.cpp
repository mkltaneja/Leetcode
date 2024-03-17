
// Time Complexity = O(n + 26*log(26) + 26*26)
// Space Complexity = O(26)

class Solution {
public:
    int minimumDeletions(string word, int k) 
    {
        int n = word.size();
        vector<int> fMap(26, 0);
        int ans = n;
        for(char c : word)
            fMap[c-'a']++;
        sort(fMap.rbegin(), fMap.rend());
        int st = 25;
        while(st >= 0 && fMap[st] == 0) st--;
        
        int rem = 0;
        while(st >= 0)
        {
            int curr = 0;
            int thres = fMap[st] + k;
            for(int i = 0; i < 26 && fMap[i] > thres; i++)
                curr += fMap[i] - thres;
            ans = min(ans, curr + rem);
            rem += fMap[st--];
        }
        return ans;
    }
};
