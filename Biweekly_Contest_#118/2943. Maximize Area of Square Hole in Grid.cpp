class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) 
    {
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());
        
        int hmx = 0, vmx = 0, p = -2, cnt = 0;
        for(int x : hBars)
        {
            if(x == p+1)
                cnt++;
            else cnt = 1;
            p = x;
            hmx = max(hmx, cnt);
        }
        
        p = -2;
        for(int x : vBars)
        {
            if(x == p+1)
                cnt++;
            else cnt = 1;
            p = x;
            vmx = max(vmx, cnt);
        }
        
        int mmx = min(hmx, vmx) + 1;
        
        return mmx * mmx;
    }
};
