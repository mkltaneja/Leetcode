
string mergeAlternately(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    int i = 0, j = 0, k = 0;
    string ans = "";
    while (i < n && j < m)
    {
        if (k & 1)
            ans += word2[j++];
        else
            ans += word1[i++];
        k = (k + 1) % 2;
    }
    while (i < n)
        ans += word1[i++];
    while (j < m)
        ans += word2[j++];
    return ans;
}