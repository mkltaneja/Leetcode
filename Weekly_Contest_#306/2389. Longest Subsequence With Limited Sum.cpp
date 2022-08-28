
vector<int> answerQueries(vector<int>& nums, vector<int>& queries) 
{
    sort(nums.begin(), nums.end());
    int m = queries.size();
    for(int i = 1; i < nums.size(); i++)
        nums[i] += nums[i-1];
    vector<int> ans(m);
    for(int i = 0; i < m; i++)
        ans[i] = upper_bound(nums.begin(), nums.end(), queries[i]) - nums.begin();

    return ans;
}
