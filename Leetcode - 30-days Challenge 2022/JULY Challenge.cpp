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

//  DAY 3 (376. Wiggle Subsequence)========================================================================================================

int wiggleMaxLength(vector<int>& nums) 
{
    int n = nums.size();
    int ans = 1, i = 1;

    while(i < n && nums[i] == nums[0]) i++;
    if(i == n) return ans;

    int up = nums[i] > nums[0];
    while(i < n)
    {
        while(up && i < n && nums[i] >= nums[i-1]) i++;
        while(!up && i < n && nums[i] <= nums[i-1]) i++;
        up ^= 1;
        ans++;
    }

    return ans;
}

//  DAY 4 (135. Candy)========================================================================================================

// APPROACH 1 --> O(n*logn)

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    vector<pair<int,int>> ri(n);
    for(int i = 0; i < n; i++)
        ri[i] = {ratings[i], i};

    sort(ri.begin(), ri.end());
    vector<int> candies(n);
    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int j = ri[i].second;
        int lans = (j && ratings[j-1] < ratings[j])? candies[j-1] + 1 : 1;
        int rans = (j+1 < n && ratings[j+1] < ratings[j])? candies[j+1] + 1 : 1;
        candies[j] = max(lans, rans);
        ans += candies[j];
    }

    return ans;
}

// APPROACH 2 --> O(n)

int candy(vector<int>& ratings) 
{
    int n = ratings.size();
    int ans = 0;

    vector<int> candies(n,1);
    for(int i = 1; i < n; i++)
        if(ratings[i] > ratings[i-1])
            candies[i] = candies[i-1] + 1;
    for(int i = n-2; i >= 0; i--)
        if(ratings[i] > ratings[i+1])
            candies[i] = max(candies[i], candies[i+1] + 1);
    for(int i = 0; i < n; i++)
        ans += candies[i];

    return ans;
}

// DAY 5 (128. Longest Consecutive Sequence)====================================================================================

int longestConsecutive(vector<int>& nums) 
{
    unordered_map<int,int> mp;
    for(int x : nums)
    {
        if(mp.count(x)) continue;
        mp[x] = 1;
        if(!mp.count(x-1) && !mp.count(x+1)) continue;
        if(mp.count(x-1) && mp.count(x+1))
        {
            int lcnt = mp[x - (mp[x-1])];
            int rcnt = mp[x + (mp[x+1])];
            mp[x - (mp[x-1])] = lcnt + rcnt + 1;
            mp[x + (mp[x+1])] = lcnt + rcnt + 1;
        }
        else 
        {
            if(mp.count(x-1))
                mp[x] = ++mp[x - mp[x-1]];
            else if(mp.count(x+1))
                mp[x] = ++mp[x + (mp[x+1])];
        }
    }
    
    int ans = 0;
    for(auto p : mp)
        ans = max(ans, p.second);
    
    return ans;
}