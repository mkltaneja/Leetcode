class Solution {
public:
    int averageValue(vector<int>& nums) 
    {
        int sum = 0, tot = 0;
        for(int x : nums)
            if(x%6 == 0)
                sum += x, tot++;
        return tot? sum/tot : 0;
    }
};
