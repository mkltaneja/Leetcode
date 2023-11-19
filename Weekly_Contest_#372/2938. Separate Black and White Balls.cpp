class Solution {
public:
    long long minimumSteps(string s) 
    {
        int n = s.size();
        long long ones = 0, ans = 0;
        for(char c : s)
        {
            if(c == '1') ones++;
            else ans += ones;
        }
        return ans;
    }
};
