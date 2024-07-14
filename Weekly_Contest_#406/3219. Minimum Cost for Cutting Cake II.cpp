
// Time Complexity = O(n*logn)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    long long minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut)
    {
        vector<vector<ll>> cut;
        for(int hcut : horizontalCut)
            cut.push_back({hcut, 1});
        for(int vcut : verticalCut)
            cut.push_back({vcut, 2});
        
        sort(cut.rbegin(), cut.rend());
        ll hcuts = 0, vcuts = 0;
        ll cost = 0;
        for(vector<ll> ct : cut)
        {
            if(ct[1] == 1)
            {
                cost += ct[0] * (vcuts+1);
                hcuts++;
            }
            else
            {
                cost += ct[0] * (hcuts+1);
                vcuts++;
            }
        }
        return cost;
    }
};
