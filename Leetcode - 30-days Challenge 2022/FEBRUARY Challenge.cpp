
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