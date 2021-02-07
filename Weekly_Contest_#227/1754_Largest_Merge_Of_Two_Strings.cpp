
string largestMerge(string word1, string word2)
{
    int n = word1.size(), m = word2.size();
    string ans = "";
    int i = 0, j = 0;
    for (; i < n && j < m;)
    {
        if (word1[i] > word2[j])
            ans += word1[i++];
        else if (word2[j] > word1[i])
            ans += word2[j++];
        else
        {
            int ii = i, jj = j;
            while (ii < n && jj < m && word1[ii] == word2[jj])
                ii++, jj++;
            if (word1[ii] > word2[jj])
                ans += word1[i++];
            else
                ans += word2[j++];
        }
    }
    while (i < n)
        ans += word1[i++];
    while (j < m)
        ans += word2[j++];
    return ans;
}