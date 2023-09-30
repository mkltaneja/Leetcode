class Solution {
public:
    #define f first
    #define s second
    int minOperations(vector<int>& nums) 
    {
        unordered_map<int,int> mp;
        for(int x : nums)
            mp[x]++;
        int ans = 0;
        for(auto p : mp)
        {
            if(p.s == 1)
                return -1;
            if(p.s % 3 == 0)
                ans += p.s / 3;
            else if(p.s % 3 == 1)
                ans += ((p.s - 1) / 3) + 1;
            else ans += (p.s / 3) + 1;
        }
        
        return ans;
    }
};
