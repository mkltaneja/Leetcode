class Solution {
public:
    
    vector<string> getWordsInLongestSubsequence(int n, vector<string>& words, vector<int>& groups) 
    {
        vector<int> maxLen(n, 1), path(n, -1);
        int max = -1, maxi = -1;
        for(int i = n-1; i >= 0; i--)
        {
            for(int j = i+1; j < n; j++)
            {
                if(groups[j] == groups[i] || words[j].size() != words[i].size())
                    continue;
                int hd = 0;
                for(int k = 0; k < words[i].size(); k++)
                    hd += words[i][k] != words[j][k];
                if(hd != 1) continue;
                
                if(maxLen[i] < maxLen[j] + 1)
                {
                    maxLen[i] = maxLen[j] + 1;
                    path[i] = j;
                }
            }
            if(maxLen[i] > max)
                max = maxLen[i], maxi = i;
        }
        
        vector<string> ans;
        int itr = maxi;
        while(itr != -1)
        {
            ans.push_back(words[itr]);
            itr = path[itr];
        }
        
        return ans;
    }
};
