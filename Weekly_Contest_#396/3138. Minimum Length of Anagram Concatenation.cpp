
// Time Complexity = O(n + sqrt(n) + sqrt(n)*log(sqrt(n)) + sqrt(n) * n * 26)
// Space Complexity = O(sqrt(n) + 26)

class Solution {
public:
    
    vector<int> findFacs(int n)
    {
        vector<int> ans;
        for(int i = 1; i*i <= n; i++)
        {
            if(n % i == 0)
            {
                ans.push_back(i);
                if(i != n/i)
                    ans.push_back(n/i);
            }
        }
        return ans;
    }
    
    int minAnagramLength(string s) 
    {
        int n = s.size();
        vector<int> facs = findFacs(n);
        sort(facs.begin(), facs.end());
        for(int len : facs)
        {
            int poss = 1;
            vector<int> mask(26, 0), pmask(26, -1);
            for(int i = 0; i < n && poss; i++)
            {
                mask[s[i]-'a']++;
                if(i % len == len-1)
                {
                    if(pmask[0] != -1 && mask != pmask)
                        poss = 0;
                    pmask = mask;
                    mask.assign(26, 0);
                }
            }
            if(poss)
                return len;
        }
        
        return n;
    }
};
