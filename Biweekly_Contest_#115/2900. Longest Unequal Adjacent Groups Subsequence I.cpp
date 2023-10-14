class Solution {
public:
    
    vector<string> solve(int st, int n, vector<string>& words, vector<int>& groups)
    {
        int i = 0;
        while(i < n && groups[i] == (st ^ 1)) i++;
        
        int x = st, last = -1;
        vector<string> ans;
        while(i < n)
        {
            if(groups[i] != x)
                x = groups[i];
            if(x != last)
                ans.push_back(words[i]);
            last = x;
            i++;
        }
        
        return ans;
    }
    
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) 
    {
        vector<string> ans1, ans2;
        ans1 = solve(0, n, words, groups);
        ans2 = solve(1, n, words, groups);
        
        if(ans1.size() > ans2.size())
            return ans1;
        return ans2;
    }
};
