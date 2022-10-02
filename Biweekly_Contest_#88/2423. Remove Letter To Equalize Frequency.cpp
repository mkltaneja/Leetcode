
// APPROACH 1 (Brute Force) --> time = O(n^2)

bool equalFrequency(string word) 
{
    int mx = 0, mn = 105;
    vector<int> mp(26);
    for(char c : word)
        mp[c-'a']++;
    for(int x : mp)
        if(x)
            mx = max(mx, x), mn = min(mn, x);

    int a = 0, b = 0;
    for(int x : mp)
    {
        if(!x) continue;
        if(x == mx) a++;
        else if(x == mn) b++;
        else return false;
    }

    if(mx == mn) return mx == 1 || a == 1;
    if(mn == 1 && b == 1) return true;
    if(mx == mn+1) return a == 1;
    return false;
}

// APPROACH 2 --> time O(n)

bool equalFrequency(string word) 
{
    int mx = 0, mn = 105;
    vector<int> mp(26);
    for(char c : word)
        mp[c-'a']++;
    for(int x : mp)
        if(x)
            mx = max(mx, x), mn = min(mn, x);

    int a = 0, b = 0;
    for(int x : mp)
    {
        if(!x) continue;
        if(x == mx) a++;
        else if(x == mn) b++;
        else return false;
    }

    if(mx == mn) return mx == 1 || a == 1;
    if(mn == 1 && b == 1) return true;
    if(mx == mn+1) return a == 1;
    return false;
}
