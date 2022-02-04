
// DAY 1 (121. Best Time to Buy and Sell Stock)================================================================================

int maxProfit(vector<int> &prices)
{
    int mn = INT_MAX, ans = 0;
    for (int x : prices)
    {
        ans = max(ans, x - mn);
        mn = min(mn, x);
    }
    return ans;
}

// DAY 2 (438. Find All Anagrams in a String)======================================================================

vector<int> findAnagrams(string s, string p)
{
    int n = s.size(), m = p.size();
    vector<int> ans;
    if (n < m)
        return ans;

    vector<int> sx(26, 0), px(26, 0);
    for (int i = 0; i < m; i++)
        sx[s[i] - 'a']++;
    for (int i = 0; i < m; i++)
        px[p[i] - 'a']++;

    if (sx == px)
        ans.push_back(0);

    for (int i = m; i < n; i++)
    {
        sx[s[i] - 'a']++;
        sx[s[i - m] - 'a']--;
        if (sx == px)
            ans.push_back(i - m + 1);
    }

    return ans;
}

// DAY 3 (454. 4Sum II)=========================================================================================

int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
{
    int n = nums1.size();
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mp[nums1[i] + nums2[j]]++;

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ans += mp[-(nums3[i] + nums4[j])];

    return ans;
}

// DAY 4 (525. Contiguous Array)======================================================================

int findMaxLength(vector<int> &nums)
{
    unordered_map<int, int> mp;
    mp[0] = -1;
    int pol = 0;
    int ans = 0;
    for (int x : nums)
    {
        pol += (x == 1);
        pol -= (x == 0);
        if (!mp.count(pol))
            mp[pol] = i;
        else
            ans = max(ans, i - mp[pol]);
    }
    return ans;
}