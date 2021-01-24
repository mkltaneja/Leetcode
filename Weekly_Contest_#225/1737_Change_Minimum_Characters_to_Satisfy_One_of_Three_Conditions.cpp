
int SmallLarge(string &a, string &b, vector<int> &ca, vector<int> &cb)
{
    int minops = INT_MAX;
    for (int i = 0; i < 25; i++)
    {
        int ops = 0;
        for (int j = i + 1; j < 26; j++)
            ops += ca[j];
        for (int j = 0; j <= i; j++)
            ops += cb[j];
        minops = min(minops, ops);
    }
    return minops;
}

int one_letter(string a, string b)
{
    vector<int> cab(26, 0);
    for (char c : a)
        cab[c - 'a']++;
    for (char c : b)
        cab[c - 'a']++;
    int maxab = 0;
    for (int i = 0; i < 26; i++)
        maxab = max(maxab, cab[i]);

    return a.size() + b.size() - maxab;
}

int minCharacters(string a, string b)
{
    vector<int> ca(26, 0), cb(26, 0);
    for (char c : a)
        ca[c - 'a']++;
    for (char c : b)
        cb[c - 'a']++;
    int ans = min(SmallLarge(a, b, ca, cb), SmallLarge(b, a, cb, ca));

    int ol = one_letter(a, b);
    // cout<<ans<<" "<<ol<<endl;
    return min(ans, ol);
}