// Method 1

char findKthBit(int n, int k)
{
    string s = "0", rs = "1";
    while (--n)
    {
        s += "1" + rs;
        rs = s;
        reverse(rs.begin(), rs.end());
        for (int i=0;i<rs.size();i++)
            rs[i] = (rs[i] == '0')? '1' : '0';
    }
    return s[k-1];
}

// Method 2

char findKthBit(int n, int k)
{
    int len = (1<<n) - 1;
    if (len == 1)
        return '0';
    if (k == len/2 + 1)
        return '1';
    else if (k < len/2 + 1)
        return findKthBit(n-1, k);
    else
        return findKthBit(n-1, len - k + 1) == '0' ? '1' : '0';
}