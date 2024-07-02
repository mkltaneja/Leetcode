
// DAY 1 (1550. Three Consecutive Odds)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool threeConsecutiveOdds(vector<int>& arr)
{
    int size = arr.size();
    for(int idx = 0; idx < size-2; idx++)
        if((arr[idx] & 1) && (arr[idx+1] & 1) && (arr[idx+2] & 1))
            return true;
    return false;
}

// DAY 2 (350. Intersection of Two Arrays II)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ans;
    unordered_map<int,int> nums1Map;
    for(int num : nums1)
        nums1Map[num]++;
    for(int num : nums2)
        if(nums1Map[num]-- > 0)
            ans.push_back(num);
    return ans;
}
