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
