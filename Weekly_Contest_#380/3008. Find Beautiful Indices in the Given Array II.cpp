
// Time Complexity = O(5*sz + n + m)
// Space Complexity = O(5*sz + n + m)

class Solution {
public:
    
    void kmp(string &s, int x, int n, vector<int> &eq)
    {
        vector<int> lps(n, 0);
        lps[0] = 0;
        int len = 0;
        for(int i = 1; i < n; )
        {
            if(s[i] == s[len])
            {
                lps[i] = ++len;
                if(len == x)
                    eq[i - (x+1) - (x-1)] = 1;
                i++;
            }
            else
            {
                if(len) len = lps[len-1];
                else i++;
            }
        }
    }
    
    vector<int> beautifulIndices(string s, string a, string b, int k) 
    {
        string as = a + "#" + s;
        string bs = b + "#" + s;
        int sz = s.size(), n = a.size(), m = b.size();
        int n1 = as.size(), m1 = bs.size();
        
        vector<int> eq1(sz), eq2(sz);
        kmp(as, n, n1, eq1);
        kmp(bs, m, m1, eq2);
        
        vector<int> eqk(sz);
        for(int i = 0; i < sz; i++)
        {
            eqk[i] += eq2[i];
            eqk[i] += i? eqk[i-1] : 0;
            eqk[i] -= (i-k-1 >= 0)? eq2[i-k-1] : 0;
        }
        
        vector<int> tmp(sz+1, 0);
        for(int i = sz-1; i >= 0; i--)
        {
            eqk[i] += tmp[i+1];

            tmp[i] += eq2[i];
            tmp[i] += sz-i-1? tmp[i+1] : 0;
            tmp[i] -= (i+k < sz)? eq2[i+k] : 0;
        }

        vector<int> ans;
        for(int i = 0; i < sz; i++)
        {
            if(!eq1[i]) continue;
            if(!eqk[i]) continue;
            
            ans.push_back(i);
        }
        
        return ans;
    }
};
