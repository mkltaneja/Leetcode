
int maxProduct(vector<int>& nums) 
{
    int n = nums.size();
    int mx = nums[0], mn = nums[0];
    int ans = nums[0];
    for(int i = 1; i < n; i++)
    {
        if(nums[i] < 0) 
        {
            swap(mn, mx);
        }                
        mx = max(mx*nums[i], nums[i]);
        mn = min(mn*nums[i], nums[i]);
        // cout<<mx<<" "<<mn<<endl;
        
        ans = max({ans, mx, mn});
    }
    return ans;
}