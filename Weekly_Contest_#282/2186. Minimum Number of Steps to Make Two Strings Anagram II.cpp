int minSteps(string s, string t) 
{
    vector<int> map(26);
    for(char c : s)
        map[c-'a']++;
    for(char c : t)
        map[c-'a']--;

    int ans = 0;
    for(int x : map)
        ans += abs(x);

    return ans;
}
