
// DAY 1 (455. Assign Cookies)===========================================================================================

// Time Complexity = O(n*logn)
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
