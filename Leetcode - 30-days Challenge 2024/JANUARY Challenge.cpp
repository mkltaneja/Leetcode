
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
