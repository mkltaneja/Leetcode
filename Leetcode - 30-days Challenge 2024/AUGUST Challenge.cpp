// DAY 1 (2678. Number of Senior Citizens)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int countSeniors(vector<string>& details)
{
    int totalPassengers = 0;
    for(string detail : details)
        totalPassengers += (detail[11]-'0') * 10 + (detail[12]-'0') > 60;
    
    return totalPassengers;
}

// DAY 2 (2134. Minimum Swaps to Group All 1's Together II)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minSwaps(vector<int>& nums)
{
    int size = nums.size();
    int totalOnes = 0;
    for(int num : nums)
        totalOnes += num;
    
    int currOnes = 0;
    for(int idx = 0; idx < totalOnes; idx++)
        currOnes += nums[idx];
    
    int minSwaps = totalOnes - currOnes;
    for(int idx = 0; idx < size; idx++)
    {
        currOnes += nums[(idx + totalOnes) % size];
        currOnes -= nums[idx];
        minSwaps = min(minSwaps, totalOnes - currOnes);
    }

    return minSwaps;
}

// DAY 3 (1460. Make Two Arrays Equal by Reversing Subarrays)=================================================================================

// Time Complexity = O(n + 1000)
// Space Complexity = O(1000)

bool canBeEqual(vector<int>& target, vector<int>& arr)
{
    vector<int> freq(1001, 0);
    for(int num : arr)
        freq[num]++;
    for(int num : target)
        freq[num]--;
    for(int num = 1; num <= 1000; num++)
        if(freq[num])
            return false;

    return true;
}
