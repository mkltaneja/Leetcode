class Solution {
public:
    int sumOfMultiples(int n) 
    {
        int ans = 0;
        for(int x = 1; x <= n; x++)
            ans += (x % 3 == 0) || (x % 5 == 0) || (x % 7 == 0)? x : 0;
        
        return ans;
    }
};
