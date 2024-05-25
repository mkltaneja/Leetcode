
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    int duplicateNumbersXOR(vector<int>& nums) 
    {
        unordered_map<int,int> mp;
        for(int x : nums)
            mp[x]++;
        int x = 0;
        for(auto p : mp)
            if(p.second == 2)
                x ^= p.first;
        return x;
    }
};
