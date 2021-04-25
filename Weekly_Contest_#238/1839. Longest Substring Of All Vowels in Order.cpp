
// APPROACH 1 (Using map)

int longestBeautifulSubstring(string word)
{
    int n = word.size();
    int ans = 0, i = 1;
    while (i < n)
    {
        unordered_map<char, bool> m;
        m[word[i - 1]] = true;
        int len = 1;
        while (i < n && word[i] >= word[i - 1])
        {
            m[word[i]] = true;
            i++, len++;
        }
        // cout<<i<<endl;
        // cout<<m['a']<<" "<<m['e']<<" "<<m['i']<<" "<<m['o']<<" "<<m['u']<<endl;
        i++;
        if (m['a'] && m['e'] && m['i'] && m['o'] && m['u'])
            ans = max(ans, len);
    }
    // cout<<endl;
    return ans;
}

// APPROACH 2 (Naive -- OPTIMIZED)

int longestBeautifulSubstring(string word)
{
    char c[5] = {'a', 'e', 'i', 'o', 'u'};
    int n = word.size();
    int ans = 0, i = 0;
    while (i < n)
    {
        if (word[i] != 'a')
        {
            i++;
            continue;
        }
        int j = i;
        bool flag = true;
        for (int k = 0; k < 5; k++)
        {
            while (i < n && word[i] == c[k])
                i++;
            if (k != 4 && (word[i] != c[k + 1] || i == n))
            {
                flag = false;
                break;
            }
        }
        if (flag)
            ans = max(ans, (i - j));
    }
    return ans;
}