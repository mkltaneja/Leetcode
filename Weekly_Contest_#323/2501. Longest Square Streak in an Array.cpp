class Solution {
public:
    int longestSquareStreak(vector<int>& nums) 
    {
        sort(nums.begin(), nums.end());
        unordered_map<long,int> mp;
        int n = nums.size();
        int ans = 0;
        for(int i = n-1; i >= 0; i--)
        {
            int mpSq = mp[(long)nums[i]*nums[i]];
            ans = max(ans, mpSq + 1);
            mp[nums[i]] = mpSq + 1;
        }
        
        return ans < 2? -1 : ans;
    }
};
