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

// DAY 4 (1508. Range Sum of Sorted Subarray Sums)=====================================================================================================

// APPROACH 1 (Brute Force)

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    vector<int> narr;
    for(int i = 0; i < n; i++)
    {
        int currSum = 0;
        for(int j = i; j < n; j++)
        {
            currSum += nums[j];
            narr.push_back(currSum);
        }
    }
    sort(narr.begin(), narr.end());

    int ans = 0;
    for(int i = left-1; i < right; i++)
        ans = (ans % MOD + narr[i] % MOD) % MOD;

    return ans;
}

// APPROACH 2 (Binary Search)

// Time Complexity = O(n*log(sum))
// Space Complexity = O(1)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    long long ans = getSumOfFirstK(nums, n, right) % MOD - getSumOfFirstK(nums, n, left-1) % MOD;
    return (ans + MOD) % MOD;
}

pair<int, long long> totalSubarraysLessThanMaxsum(vector<int>& nums, int n, int maxSum)
{
    int count = 0;
    long long currSum = 0, windowSum = 0, totalSum = 0;
    for(int i = 0, j = 0; i < n; i++)
    {
        currSum += nums[i];
        windowSum += nums[i] * (i - j + 1);
        while(currSum > maxSum)
        {
            windowSum -= currSum;
            currSum -= nums[j++];
        }
        count += i - j + 1;
        totalSum += windowSum;
    }

    return {count, totalSum};
}

long long getSumOfFirstK(vector<int>& nums, int n, int k)
{
    int minSum = *min_element(nums.begin(), nums.end());
    int maxSum = accumulate(nums.begin(), nums.end(), 0);
    long long lo = minSum, hi = maxSum;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);

        if(totalSubarraysLessThanMaxsum(nums, n, mid).first >= k)
            hi = mid - 1;
        else lo = mid + 1;
    }

    auto [count, sum] = totalSubarraysLessThanMaxsum(nums, n, lo);

    return sum - lo * (count - k);
}

// DAY 5 (2053. Kth Distinct String in an Array)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string kthDistinct(vector<string>& arr, int k)
{
    int size = arr.size();
    unordered_map<string, int> freqMap;
    for(int idx = 0; idx < size; idx++)
        freqMap[arr[idx]]++;
    
    int visited = 0;
    for(int idx = 0; idx < size; idx++)
        if(freqMap[arr[idx]] == 1 && ++visited == k)
            return arr[idx];
    
    return "";
}

// DAY 6 (3016. Minimum Number of Pushes to Type Word II)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumPushes(string word)
{
    vector<int> charFreqMap(26, 0);
    for(char c : word)
        charFreqMap[c-'a']++;
    sort(charFreqMap.rbegin(), charFreqMap.rend());
    
    int numKeysPushed = 0;
    for(int idx = 0; idx < 26 && charFreqMap[idx]; idx++)
        numKeysPushed += charFreqMap[idx] * ((idx / 8) + 1);
    
    return numKeysPushed;
}
