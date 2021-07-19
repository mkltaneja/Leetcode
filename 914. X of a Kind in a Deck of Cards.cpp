
bool hasGroupsSizeX(vector<int> &deck)
{
    unordered_map<int, int> m;
    for (int x : deck)
        m[x]++;
    int g = 0;
    for (auto p : m)
        g = __gcd(g, p.second);
    return (g != 1);
}