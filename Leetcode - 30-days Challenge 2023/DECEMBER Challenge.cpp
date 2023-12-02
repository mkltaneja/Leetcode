
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

// DAY 2 (1160. Find Words That Can Be Formed by Characters)=====================================================================================================

int countCharacters(vector<string>& words, string chars) 
{
    vector<int> map(26, 0);
    for(char c : chars)
        map[c - 'a']++;
    
    int ans = 0;
    for(string word : words)
    {
        vector<int> tmp = map;
        bool isValid = true;
        for(char c : word)
        {
            if(--tmp[c-'a'] < 0)
            {
                isValid = false;
                break;
            }
        }
        if(isValid) ans += word.size();
    }
    return ans;
}
