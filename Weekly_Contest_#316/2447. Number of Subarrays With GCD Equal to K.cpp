class Solution {
public:
    int subarrayGCD(vector<int>& nums, int k) 
    {
        int ans = 0;
        int n = nums.size();
        for(int i = 0; i < n; i++)
        {
            int g = 0;
            for(int j = i; j < n && (nums[j] % k == 0); j++)
            {
                g = __gcd(g, nums[j]);
                if(g == k) ans++;
                else if(g < k || g % k) break;
            }
        }
        return ans;
    }
};
