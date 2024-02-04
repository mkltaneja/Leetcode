
// Time Complexity = O(3*n)
// Space Complexity = O(n)

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) 
    {
        int n = word.size();
        vector<int> lps(n, 0);
        int len = 0;
        for(int i = 1; i < n; )
        {
            if(word[i] == word[len])
                lps[i++] = ++len;
            else
            {
                if(len) len = lps[len-1];
                else lps[i++] = 0;
            }
        }
        len = lps[n-1];
        int i = n-1;
        int ans = (n + k - 1) / k;
        while(len)
        {
            int idx = n - len;
            if(idx % k == 0)
            {
                ans = idx / k;
                break;
            }
            len = lps[len-1];
        }
        
        return ans;
    }
};
