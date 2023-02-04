
// APPROACH 1 (Finding the previous valid pointer by Binary Search every time) --> time = O(n*logn)

class Solution {
public:
    int maximizeWin(vector<int>& pp, int k) 
    {
        int n = pp.size();
        int ans = 0;
        vector<int> rans(n);
        for(int i = n-1; i >= 0; i--)
        {
            int ub = upper_bound(pp.begin()+i, pp.end(), pp[i]+k) - pp.begin();
            rans[i] = ub - i;
            if(i == n-1) continue;
            rans[i] = max(rans[i], rans[i+1]);
        }
        
        for(int i = 0; i < n; i++)
        {
            int ub = upper_bound(pp.begin(), pp.begin()+i+1, pp[i]-k-1) - pp.begin();
            int lans = i - ub + 1;
            ans = max(ans, lans + (i+1 < n? rans[i+1] : 0));
        }
        
        return ans;
    }
};

// APPROACH 2 (2 Pointer approach) --> time = O(n)

class Solution {
public:
    int maximizeWin(vector<int>& pp, int k) 
    {
        int n = pp.size();
        int ans = 0;
        vector<int> cmax(n);
        for(int i = 0, j = 0; i < n; i++)
        {
            while(pp[j] + k < pp[i]) j++;
            cmax[i] = max(i-j+1, (i? cmax[i-1] : 0));
            ans = max(ans, i-j+1 + (j? cmax[j-1] : 0));
        }
        
        return ans;
    }
};
