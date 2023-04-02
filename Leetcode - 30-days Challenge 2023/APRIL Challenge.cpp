// DAY 1 (704. Binary Search)====================================================================================

int search(vector<int>& nums, int target) 
{
    int lo = 0, hi = nums.size()-1;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(nums[mid] == target)
            return mid;
        if(nums[mid] < target)
            lo = mid + 1;
        else hi = mid - 1;
    }

    return -1;
}

// DAY 2 (2300. Successful Pairs of Spells and Potions)==========================================================

#define ll long long
vector<int> successfulPairs(vector<int>& spells, vector<int>& potions, long long success) 
{
    int n = spells.size(), m = potions.size();
    vector<int> ans(n);

    sort(potions.begin(), potions.end());

    for(int i = 0; i < n; i++)
    {
        ll req = (success + spells[i] - 1) / spells[i];
        int lb = lower_bound(potions.begin(), potions.end(), req) - potions.begin();
        ans[i] = m - lb;
    }

    return ans;
}
