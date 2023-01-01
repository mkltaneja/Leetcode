class Solution {
public:
    int countDigits(int num) 
    {
        int n = num;
        int ans = 0;
        while(num)
        {
            if(n % (num%10) == 0) ans++;
            num /= 10;
        }
        
        return ans;
    }
};
