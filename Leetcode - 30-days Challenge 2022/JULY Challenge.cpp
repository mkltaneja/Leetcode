//  DAY 1 (1710. Maximum Units on a Truck)========================================================================================================

int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) 
{
    sort(boxTypes.begin(), boxTypes.end(), [](auto const &a, auto const &b){
        return a[1] > b[1];
    });
    int ans = 0;
    for(vector<int> v : boxTypes)
    {
        ans += min(truckSize, v[0]) * v[1];
        truckSize -= min(truckSize, v[0]);
    }
    return ans;
}

//  DAY 2 (1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts)========================================================================================================

int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts)
{
    horizontalCuts.insert(horizontalCuts.begin(), 0);
    horizontalCuts.push_back(h);
    verticalCuts.insert(verticalCuts.begin(), 0);
    verticalCuts.push_back(w);
    sort(horizontalCuts.begin(), horizontalCuts.end());
    sort(verticalCuts.begin(), verticalCuts.end());
    int mxw = 0, mxh = 0;
    for(int i = 0; i < horizontalCuts.size()-1; i++)
        mxh = max(mxh, horizontalCuts[i+1] - horizontalCuts[i]);
    for(int i = 0; i < verticalCuts.size()-1; i++)
        mxw = max(mxw, verticalCuts[i+1] - verticalCuts[i]);

    return (long)mxh * mxw % 1000000007;
}
