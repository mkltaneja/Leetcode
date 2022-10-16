class Solution {
public:
    
    int reverse(int x)
    {
        int y = 0;
        while(x)
        {
            y = y*10 + x%10;
            x /= 10;
        }
        return y;
    }
    
    bool sumOfNumberAndReverse(int num) 
    {
        int x = 0;
        while(x <= num)
        {
            int y = reverse(x);
            if(x++ + y == num) return true;
        }
        return false;
    }
};
