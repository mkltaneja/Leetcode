
int longestNiceSubarray(vector<int>& nums) 
{
    int j = 0;
    int ans = 0, x = 0;
    for(int i = 0; i < nums.size(); i++)
    {
        while(nums[i] & x)
        {
            x &= ~nums[j++];
        }
        x |= nums[i];
        ans = max(ans, i-j+1);
    }

    return ans;
}
