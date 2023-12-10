
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int countTestedDevices(vector<int>& batteryPercentages) 
    {
        int t = 0;
        for(int x : batteryPercentages)
            t += (x - t) > 0;
        return t;
    }
};
