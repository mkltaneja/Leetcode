
string subStrHash(string s, int pow, int m, int k, int hashValue)
{
    int n = s.size();
    long long hash = 0, p = 1;
    for (int i = n - 1; i >= n - k; i--)
    {
        hash = (hash * pow + (s[i] - 'a' + 1)) % m;
        p = p * pow % m;
    }

    int ansi = (hash == hashValue) ? n - k : -1;

    for (int i = n - k - 1; i >= 0; i--)
    {
        hash = (hash * pow + (s[i] - 'a' + 1) - (s[i + k] - 'a' + 1) * p % m + m) % m;
        if (hash == hashValue)
            ansi = i;
    }
    return s.substr(ansi, k);
}