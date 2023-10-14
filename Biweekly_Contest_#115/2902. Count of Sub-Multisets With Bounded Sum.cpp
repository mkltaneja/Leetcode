class Solution {
public:
    
    int mod = 1e9 + 7;
    long cache[20005];
    
    int countSubMultisets(vector<int>& nums, int l, int r) 
    {
        int n = nums.size();
        
        sort(nums.begin(), nums.end());
        
        cache[0] = 1;
        int i = 0;
        
        while(i < n && nums[i] == 0)
        {
            cache[0]++;
            i++;
        }

        int sumSf = 0;
        while(i < n)
        {
            int j = i;
            while(j < n && nums[j] == nums[i]) j++;
            
            int cnt = j-i, num = nums[i];
            int maxNum = min(r, sumSf + num * cnt);
            
            for(int x = maxNum; x >= num; x--)
            {
                for(int c = 1; c <= cnt && x - num*c >= 0; c++)
                {
                    cache[x] += cache[x - num * c];
                    if(cache[x] >= mod) cache[x] -= mod;
                }
            }
            i = j;
            sumSf += num * cnt;
        }
        
        long ans = 0;
        for(int i = l; i <= r; i++)
        {
            ans += cache[i];
            if(ans >= mod) ans -= mod;
        }
        
        return ans;
    }
};
