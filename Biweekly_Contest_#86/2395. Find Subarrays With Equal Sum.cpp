
bool findSubarrays(vector<int>& nums) 
{
    unordered_map<long,int> mp;
    long sum = 0;
    for(int j = 0; j+1 < nums.size(); j++)
    {
        sum = nums[j] + nums[j+1];
        if(mp[sum]++) return true;
    }

    return false;
}
