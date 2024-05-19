
// Time Complexity = O(n * log10(x))
// Space Complexity = O(1)

class Solution {
public:
    #define ll long long
    long long sumDigitDifferences(vector<int>& nums) 
    {
        ll n = nums.size();
        ll ans = 0;
        while(nums[0])
        {
            vector<int> cnt(10,0);
            for(int &x : nums)
            {
                cnt[x % 10]++;
                x /= 10;
            }
            ll sum = 0;
            for(int x : cnt)
                sum += (n - x) * x;
            
            ans += sum;
        }
        ans >>= 1;
        return ans;
    }
};
