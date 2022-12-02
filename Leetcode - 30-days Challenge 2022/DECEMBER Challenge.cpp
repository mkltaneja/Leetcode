// DAY 1 (1704. Determine if String Halves Are Alike)===============================================================================

bool halvesAreAlike(string s) 
{
    int n = s.size();

    auto isVowel = [&](char c)
    {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int cnt = 0;
    for(int i = 0, j = n/2; j < n; i++, j++)
    {
        if(isVowel(s[i])) cnt++;
        if(isVowel(s[j])) cnt--;
    }
    return cnt == 0;
}

// DAY 2 (1657. Determine if Two Strings Are Close)==========================================================================

bool closeStrings(string word1, string word2) 
{
    vector<int> map1(26), map2(26);
    for(char &c : word1)
        map1[c-'a']++;
    for(char &c : word2)
        map2[c-'a']++;

    vector<int> unique1, unique2;
    for(int i = 0; i < 26; i++)
        if(map1[i])
            unique1.push_back(i);
    for(int i = 0; i < 26; i++)
        if(map2[i])
            unique2.push_back(i);

    sort(map1.begin(), map1.end());
    sort(map2.begin(), map2.end());

    return (unique1 == unique2) && (map1 == map2);
}
