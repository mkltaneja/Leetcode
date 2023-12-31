
// Time Complexity = O(n + m*26)
// Space Complexity = O(n*26 + m)

class Solution {
public:
    
    vector<vector<int>> fmap1, fmap2;
    vector<int> pal;
    int n, m;
    string s1, s2;
    
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) 
    {
        n = s.size(), m = queries.size();
        int n2 = n/2;
        s1 = s.substr(0, n2);
        s2 = s.substr(n2);
        reverse(s2.begin(), s2.end());
        fmap1.assign(n2, vector<int>(26, 0));
        fmap2.assign(n2, vector<int>(26, 0));
        pal.assign(n2, 0);
        
        vector<int> tmp1(26), tmp2(26);
        for(int i = 0; i < n2; i++)
        {
            tmp1[s1[i]-'a']++;
            fmap1[i] = tmp1;
            tmp2[s2[i]-'a']++;
            fmap2[i] = tmp2;
            
            pal[i] = s1[i] == s2[i];
            if(pal[i])
                pal[i] += i? pal[i-1] : 0;
        }
        
        vector<bool> ans;
        for(vector<int> &q : queries)
        {
            int a = q[0], b = q[1], c = n2 - (q[2] - n2) - 1, d = n2 - (q[3] - n2) - 1;
            vector<vector<int>> pts = {{a, b, 0}, {d, c, 1}};
            sort(pts.begin(), pts.end());
            a = pts[0][0], b = pts[0][1], c = pts[1][0], d = pts[1][1];
            int ss1 = pts[0][2], ss2 = pts[1][2];
            
            if(a > 0) // 0 -> pts[0][0]-1
            {
                if(pal[a-1] < a)
                {
                    ans.push_back(false);
                    continue;
                }
            }
            if(b+1 < c) // pts[0][1]+1 -> pts[1][0]-1
            {
                if(pal[c-1] < c - b - 1)
                {
                    ans.push_back(false);
                    continue;
                }
            }
            if(max(b, d) < n2-1) // max(pts[0][1], pts[1][1])+1 -> n-1
            {
                if(pal[n2-1] < n2 - max(b, d) - 1)
                {
                    ans.push_back(false);
                    continue;
                }
            }
            
            bool res = true;
            if(ss1 == 0)
            {
                if(b >= d)
                {
                    for(int i = 0; i < 26 && res; i++)
                        if(fmap1[b][i] - (a? fmap1[a-1][i] : 0) != fmap2[b][i] - (a? fmap2[a-1][i] : 0))
                            res = false;
                }
                else if(b >= c)
                {
                    for(int i = 0; i < 26 && res; i++)
                    {
                        if(fmap1[d][i] - (a? fmap1[a-1][i] : 0) != fmap2[d][i] - (a? fmap2[a-1][i] : 0))
                            res = false;
                        if(fmap1[b][i] - (a? fmap1[a-1][i] : 0) < (c? fmap2[c-1][i] : 0) - (a? fmap2[a-1][i] : 0))
                            res = false;
                        if(fmap1[d][i] - fmap1[b][i] > fmap2[d][i] - (c? fmap2[c-1][i] : 0))
                            res = false;
                    }
                }
                else
                {
                    for(int i = 0; i < 26 && res; i++)
                    {
                        if(fmap1[b][i] - (a? fmap1[a-1][i] : 0) != fmap2[b][i] - (a? fmap2[a-1][i] : 0))
                            res = false;
                        if(fmap1[d][i] - (c? fmap1[c-1][i] : 0) != fmap2[d][i] - (c? fmap2[c-1][i] : 0))
                            res = false;
                    }
                }
            }
            else
            {
                if(b >= d)
                {
                    for(int i = 0; i < 26 && res; i++)
                        if(fmap2[b][i] - (a? fmap2[a-1][i] : 0) != fmap1[b][i] - (a? fmap1[a-1][i] : 0))
                            res = false;
                }
                else if(b >= c)
                {
                    for(int i = 0; i < 26 && res; i++)
                    {
                        if(fmap2[d][i] - (a? fmap2[a-1][i] : 0) != fmap1[d][i] - (a? fmap1[a-1][i] : 0))
                            res = false;
                        if(fmap2[b][i] - (a? fmap2[a-1][i] : 0) < (c? fmap1[c-1][i] : 0) - (a? fmap1[a-1][i] : 0))
                            res = false;
                        if(fmap2[d][i] - fmap2[b][i] > fmap1[d][i] - (c? fmap1[c-1][i] : 0))
                            res = false;
                    }
                }
                else
                {
                    for(int i = 0; i < 26 && res; i++)
                    {
                        if(fmap2[b][i] - (a? fmap2[a-1][i] : 0) != fmap1[b][i] - (a? fmap1[a-1][i] : 0))
                            res = false;
                        if(fmap2[d][i] - (c? fmap2[c-1][i] : 0) != fmap1[d][i] - (c? fmap1[c-1][i] : 0))
                            res = false;
                    }
                }
            }
            
            ans.push_back(res);
        }
        
        return ans;
    }
};
