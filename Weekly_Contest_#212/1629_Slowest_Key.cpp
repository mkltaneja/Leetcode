char slowestKey(vector<int> &releaseTimes, string keysPressed)
{
    vector<int> ans(26, 0);
    int n = releaseTimes.size();
    for (int i = 0; i < n; i++)
    {
        int time = i == 0 ? releaseTimes[i] : releaseTimes[i] - releaseTimes[i - 1];
        ans[keysPressed[i] - 'a'] = max(ans[keysPressed[i] - 'a'], time);
        // cout<<ans[keysPressed[i] - 'a']<<endl;
    }
    int maxtime = 0;
    char maxchar;
    for (int i = 0; i < 26; i++)
    {
        if (ans[i] >= maxtime)
        {
            maxtime = ans[i];
            maxchar = i + 'a';
        }
    }
    return maxchar;
}