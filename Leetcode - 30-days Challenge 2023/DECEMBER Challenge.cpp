
// DAY 1 (1662. Check If Two String Arrays are Equivalent)========================================================================================

bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) 
{
    int i = 0, j = 0, ii = 0, jj = 0, n = word1.size(), m = word2.size();
    while(i < n && j < m)
    {
        if(ii < word1[i].size() && jj < word2[j].size() && word1[i][ii] != word2[j][jj]) 
            return false;
        ii++, jj++;
        if(ii == word1[i].size()) i++, ii = 0;
        if(jj == word2[j].size()) j++, jj = 0;
    }
    return i == n && j == m;
}
