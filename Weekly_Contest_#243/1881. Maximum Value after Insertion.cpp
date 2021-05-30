
// APPROACH 1

string maxValue(string n, int x)
{
    int pos = -1, m = n.size();
    if (n[0] != '-')
    {
        for (int i = 0; i < m; i++)
        {
            while (i < m && (n[i] - '0') == x)
                i++;

            if ((n[i] - '0') < x)
            {
                pos = i;
                break;
            }
        }
    }
    else
    {
        for (int i = 1; i < m; i++)
        {
            while ((n[i] - '0') == x)
                i++;

            if ((n[i] - '0') > x)
            {
                pos = i;
                break;
            }
        }
    }
    if (pos == -1)
        pos = m;
    n.insert(n.begin() + pos, x + '0');

    return n;
}

// APPROACH 2

string maxValue(string n, int x)
{
    int pos = 0, m = n.size();

    if (n[0] == '-')
    {
        pos++;
        while (pos < m && n[pos] - '0' <= x)
            pos++;
    }
    else
        while (pos < m && n[pos] - '0' >= x)
            pos++;

    n.insert(n.begin() + pos, x + '0');

    return n;
}