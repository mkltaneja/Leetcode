
// Time Complexity = O(sqrt(n))
// Space Complexity = O(1)

class Solution {
public:
    
    int getMaxAns(int clr1, int clr2)
    {
        int x = 1, ans = 0;
        while(true)
        {
            if(clr1-x < 0) break;
            clr1 -= x++;
            if(clr2-x < 0) break;
            clr2 -= x++;
        }
        ans = max(ans, x-1);
        return ans;
    }
    
    int maxHeightOfTriangle(int red, int blue)
    {
        return max(getMaxAns(red, blue), getMaxAns(blue, red));
    }
};
