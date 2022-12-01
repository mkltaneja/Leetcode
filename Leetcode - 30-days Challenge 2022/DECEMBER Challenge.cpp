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
