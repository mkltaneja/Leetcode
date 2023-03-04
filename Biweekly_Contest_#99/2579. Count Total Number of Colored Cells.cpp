class Solution {
public:
    
    #define ll long long
    long long coloredCells(int n) 
    {
        ll ans = 1;
        while(--n)
            ans += 4ll*n;
        return ans;
    }
};
