
// Time Complexity = O(n + k*(n+k))
// Space Complexity = O(k)

class Solution {
public:
    int maximumLength(vector<int>& nums, int k)
    {
        int n = nums.size();
        vector<int> kmap(k, 0);
        int maxAlts = 0;
        for(int num : nums)
            ++kmap[num % k];
        int ans = 0;
        
        for(int i = 0; i < k; i++)
        {
            int lasti = -1;
            vector<int> lastj(k, -1), cnt(k, 0);
            for(int j = 0; j < n; j++)
            {
                int num = nums[j] % k;
                if((lasti == -1 && !cnt[num]) || lasti > lastj[num])
                {
                    cnt[num] += lasti == -1? 1 : 2;
                    lastj[num] = j;
                }
                if(num == i)
                    lasti = j;
            }
            for(int j = 0; j < k; j++)
                ans = max(ans, cnt[j] + (lasti > lastj[j]));
        }
        return ans;
    }
};
