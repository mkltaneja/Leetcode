class Solution {
public:
    int alternateDigitSum(int n) 
    {
        int pos = 1, ans = 0;
        while(n)
        {
            ans += pos * (n%10);
            pos *= -1;
            n /= 10;
        }
        
        return -pos * ans;
    }
};
