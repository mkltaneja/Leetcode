
// Time Compplexity = O(n*logn)
// Space Compplexity = O(n)

class Solution {
public:
    int minimumCost(int m, int n, vector<int>& horizontalCut, vector<int>& verticalCut)
    {
        vector<vector<int>> cut;
        for(int hcut : horizontalCut)
            cut.push_back({hcut, 1});
        for(int vcut : verticalCut)
            cut.push_back({vcut, 2});
        
        sort(cut.rbegin(), cut.rend());
        int hcuts = 0, vcuts = 0;
        int cost = 0;
        for(vector<int> ct : cut)
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
