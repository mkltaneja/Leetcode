
// Time Complexity = O(1)
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long flowerGame(int n, int m) 
    {
        ll e1 = n/2, o1 = (n + 1)/2;
        ll e2 = m/2, o2 = (m + 1)/2;
        ll ans = e1*o2 + e2*o1;
        return ans;
    }
};
