
// Time Complexity = O(k)
// Space Complexity = O(1)

class Solution {
public:
    int numberOfChild(int n, int k) 
    {
        int ans = 0, dir = 1;
        while(k--)
        {
            ans += dir;
            if(ans == 0 || ans == n-1) dir *= -1;
        }
        return ans;
    }
};
