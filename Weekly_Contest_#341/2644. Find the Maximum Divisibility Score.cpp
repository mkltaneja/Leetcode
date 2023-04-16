class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) 
    {
        sort(divisors.begin(), divisors.end());
        int mx = 0, mxc = -1;
        for(int x : divisors)
        {
            int c = 0;
            for(int y : nums)
                c += (y % x == 0);
            if(c > mxc) mxc = c, mx = x;
        }
        
        return mx;
    }
};
