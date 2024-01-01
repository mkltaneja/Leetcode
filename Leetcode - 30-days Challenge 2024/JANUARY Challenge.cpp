
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
