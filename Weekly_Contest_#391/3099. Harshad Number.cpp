
// Time Complexty = O(log10(x))
// Space Complexty = O(1)

class Solution {
public:
    int sumOfTheDigitsOfHarshadNumber(int x) 
    {
        int s = 0, t = x;
        while(t)
        {
            s += t%10;
            t /= 10;
        }
        return x % s? -1 : s;
    }
};
