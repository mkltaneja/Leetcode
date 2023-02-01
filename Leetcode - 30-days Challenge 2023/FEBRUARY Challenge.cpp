// DAY 1 (1071. Greatest Common Divisor of Strings)=============================================================================

// APPROACH 1 (Finding prime factors)

int gcd(int x, int y)
{
    while(x)
    {
        int z = y % x;
        y = x;
        x = z;
    }
    return y;
}

string gcdOfStrings(string str1, string str2) 
{
    vector<int> pFacs;
    int n = str1.size(), m = str2.size();
    int x = gcd(n, m);
    for(int i = 1; i*i <= x; i++)
    {
        if(x % i) continue;
        pFacs.push_back(i);
        if(i != x/i)
            pFacs.push_back(x/i);
    }

    sort(pFacs.rbegin(), pFacs.rend());
    for(int pf : pFacs)
    {
        bool isAns = true;
        string check = str1.substr(0,pf);
        for(int i = 0; i < n && isAns; i += pf)
        {
            if(str1.substr(i,pf) != check)
                isAns = false;
        }
        for(int i = 0; i < m && isAns; i += pf)
        {
            if(str2.substr(i,pf) != check)
                isAns = false;
        }

        if(isAns) return check;
    }

    return "";
}

// APPROACH 2 (GCD Approach)

string gcdOfStrings(string str1, string str2) 
{
    if(str1.size() < str2.size())
        return gcdOfStrings(str2, str1);
    if(str2.empty()) return str1;
    return str1.substr(0,str2.size()) == str2? gcdOfStrings(str1.substr(str2.size()), str2) : "";
}
