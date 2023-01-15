class Solution {
public:
    int differenceOfSum(vector<int>& nums) 
    {
        int sum1 = 0, sum2 = 0;
        for(int x : nums)
        {
            sum1 += x;
            while(x)
            {
                sum2 += x%10;
                x /= 10;
            }
        }
        
        return abs(sum1 - sum2);
    }
};
