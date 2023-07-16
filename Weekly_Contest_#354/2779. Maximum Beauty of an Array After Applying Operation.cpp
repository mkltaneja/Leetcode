class Solution {
public:
    
    int maximumBeauty(vector<int>& nums, int k) 
    {
        int n = nums.size();
        int mx = 0;
        for(int x : nums)
            mx = max(mx, x);
        vector<int> psum(mx+1, 0);
        for(int x : nums)
        {
            psum[min(x + 1 + k, mx)]--;
            psum[max(x - k, 0)]++;
        }
        int ans = 0, maxCnt = 0;
        for(int i = 0; i <= mx; i++)
        {
            psum[i] = psum[i] + (i? psum[i-1] : 0l);
            ans = max(ans, psum[i]);
        }
        
        return ans;
    }
};
