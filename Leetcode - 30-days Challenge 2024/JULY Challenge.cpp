
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

// DAY 3 (1509. Minimum Difference Between Largest and Smallest Value in Three Moves)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minDifference(vector<int>& nums)
{
    if(nums.size() <= 4)
        return 0;
    int min1 = INT_MAX, min2 = INT_MAX, min3 = INT_MAX, min4 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN, max4 = INT_MIN;
    for(int num : nums)
    {
        if(num >= max1)
        {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if(num >= max2)
        {
            max4 = max3;
            max3 = max2;
            max2 = num;
        }
        else if(num >= max3)
        {
            max4 = max3;
            max3 = num;
        }
        else if(num >= max4)
            max4 = num;
        
        if(num <= min1)
        {
            min4 = min3;
            min3 = min2;
            min2 = min1;
            min1 = num;
        }
        else if(num <= min2)
        {
            min4 = min3;
            min3 = min2;
            min2 = num;
        }
        else if(num <= min3)
        {
            min4 = min3;
            min3 = num;
        }
        else if(num <= min4)
            min4 = num;
    }
    return min({max1 - min4, max2 - min3, max3 - min2, max4 - min1});
}
