
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) 
    {
        unordered_map<int,int> mp;
        int ans = 0;
        for(int x : nums)
            mp[x]++;
        int mx = 0;
        for(auto p : mp)
        {
            if(p.second > mx)
                mx = p.second, ans = p.second;
            else if(p.second == mx)
                ans += p.second;
        }
        
        return ans;
    }
};
