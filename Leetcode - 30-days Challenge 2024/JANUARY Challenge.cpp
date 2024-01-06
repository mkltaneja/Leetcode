
// DAY 1 (455. Assign Cookies)===========================================================================================

// APPROACH 1 (Using Map)

// Time Complexity = O(n + m*logn)
// Space Complexity = O(n)

int findContentChildren(vector<int>& g, vector<int>& s) 
{
    int gSize = g.size(), sSize = s.size();
    map<int, int> gMap;
    int satisfiedCount = 0;
    for(int greed : g)
        gMap[greed]++;
    for(int size : s)
    {
        auto justSmallerGreed = gMap.upper_bound(size);
        if(justSmallerGreed == gMap.begin()) continue;
        
        justSmallerGreed--;
        if(--(*justSmallerGreed).second == 0)
            gMap.erase(justSmallerGreed);
        satisfiedCount++;
    }
    return satisfiedCount;
}

// APPROACH 2 (2 pointer approach)

// Time Complexity = O(max(m*logn, n*logn))
// Space Complexity = O(1)

int findContentChildren(vector<int>& g, vector<int>& s)
{
    int gSize = g.size(), sSize = s.size();
    sort(g.rbegin(), g.rend());
    sort(s.rbegin(), s.rend());
    int satisfiedCount = 0;
    
    for(int p1 = 0, p2 = 0; p1 < gSize && p2 < sSize; p1++)
    {
        if(g[p1] <= s[p2])
        {
            satisfiedCount++;
            p2++;
        }
    }
    return satisfiedCount;
}

// DAY 2 (2610. Convert an Array Into a 2D Array With Conditions)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<vector<int>> findMatrix(vector<int>& nums) 
{
    int size = nums.size();
    unordered_map<int,int> freqMap;
    vector<vector<int>> ans;
    for(int num : nums)
        freqMap[num]++;
    
    while(!freqMap.empty())
    {
        vector<int> rowTemp;
        for(auto itr = freqMap.begin(); itr != freqMap.end(); )
        {
            rowTemp.push_back(itr->first);
            if(--itr->second == 0)
                itr = freqMap.erase(itr);
            else itr++;
        }
        ans.push_back(rowTemp);
    }
    return ans;
}

// DAY 3 (2125. Number of Laser Beams in a Bank)==================================================================================

// Time Complexity = O(rows*cols)
// Space Complexity = O(1)

int numberOfBeams(vector<string>& bank)
{
    int rows = bank.size();
    int cols = bank[0].size();
    
    int totalBeams = 0;
    int previousRowDevices = 0;
    for(string plan : bank)
    {
        int totalDevices = 0;
        for(char device : plan)
            totalDevices += (device == '1');
        totalBeams += totalDevices * previousRowDevices;
        if(totalDevices)
            previousRowDevices = totalDevices;
    }
    return totalBeams;
}

// DAY 4 (2870. Minimum Number of Operations to Make Array Empty)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int minOperations(vector<int> &nums)
{
    int size = nums.size();
    unordered_map<int,int> numCnt;
    for(int x : nums)
        numCnt[x]++;
    
    int totalOperations = 0;
    for(auto pair : numCnt)
    {
        int num = pair.first;
        int cnt = pair.second;
        if(cnt == 1) return -1;

        int k = cnt / 3;
        if(cnt % 3 == 0)
            totalOperations += k;
        else if(cnt % 3 == 1)
            totalOperations += k-1 + 2;
        else
            totalOperations += k + 1;
    }
    return totalOperations;
}

// DAY 5 (300. Longest Increasing Subsequence)=======================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int findLowerBound(vector<int> &lis, int num)
{
    int low = 0, high = lis.size()-1;
    int ans = lis.size();
    while(low <= high)
    {
        int mid = low + ((high - low) >> 1);
        if(lis[mid] < num)
            low = mid + 1;
        else
        {
            high = mid - 1;
            ans = mid;
        }
    }
    return ans;
}

int lengthOfLIS(vector<int> &nums)
{
    int size = nums.size();
    vector<int> lis;
    for(int num : nums)
    {
        int justGreaterIdx = findLowerBound(lis, num);
        if(justGreaterIdx == lis.size())
            lis.push_back(num);
        else lis[justGreaterIdx] = num;
    }
    return lis.size();
}

// DAY 6 (1235. Maximum Profit in Job Scheduling)=========================================================================================================

int findLowerBound(int endTime, int lo, int hi, vector<vector<int>> &times)
{
    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(times[mid][0] < endTime)
            lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int size = startTime.size();
    vector<vector<int>> times(size);
    for(int idx = 0; idx < size; idx++)
        times[idx] = {startTime[idx], endTime[idx], profit[idx]};
    sort(times.begin(), times.end());

    vector<int> maxProfit(size, 0);
    maxProfit[size-1] = times[size-1][2];
    for(int idx = size-2; idx >= 0; idx--)
    {
        int nextJobIdx = findLowerBound(times[idx][1], idx+1, size, times);
        int nextJobProfit = nextJobIdx == size? 0 : maxProfit[nextJobIdx];
        maxProfit[idx] = max(maxProfit[idx+1], nextJobProfit + times[idx][2]);
    }

    return maxProfit[0];
}
