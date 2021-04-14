
bool isvowel(char &c)
{
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return true;
    return false;
}

string reverseVowels(string s)
{
    string vow = "";
    for (char c : s)
        if (isvowel(c))
            vow += c;
    for (char &c : s)
    {
        if (isvowel(c))
        {
            c = vow.back();
            vow.pop_back();
        }
    }
    return s;
}