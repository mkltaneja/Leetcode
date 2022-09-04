
bool ispal(int b, int n)
{
    vector<int> x;
    while(n)
    {
        x.push_back(n % b);
        n /= b;
    }
    vector<int> t = x;
    reverse(t.begin(), t.end());

    return t == x;
}

bool isStrictlyPalindromic(int n) 
{
    // JUST DO:
    // return n == 1;
    // OR

    for(int x = 2; x <= n-2; x++)
        if(!ispal(x, n))
            return false;
    return true;
}
