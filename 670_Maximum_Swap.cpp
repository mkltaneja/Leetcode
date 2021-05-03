
// APPROACH 1 --> O(n^2)

int maximumSwap(int num)
{
    string s = to_string(num);
    // sort(s.begin(), s.end(), greater<char>());
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '9')
            continue;
        char mx = s[i] + 1;
        int idx = -1;
        for (int j = i + 1; j < s.size(); j++)
            if (s[j] >= mx)
                mx = s[j], idx = j;
        if (idx != -1)
        {
            swap(s[i], s[idx]);
            break;
        }
    }
    return stoi(s);
}

// APPROACH 2 --> O(n)

int maximumSwap(int num)
{
    string s = to_string(num);
    int n = s.size();
    int i = n - 1, j = n - 1, idx1 = -1, idx2 = -1;
    while (i >= 0)
    {
        if (s[i] < s[j])
            idx1 = i, idx2 = j;
        else if (s[i] > s[j])
            j = i;
        i--;
    }
    if (idx1 != -1)
        swap(s[idx1], s[idx2]);

    return stoi(s);
}