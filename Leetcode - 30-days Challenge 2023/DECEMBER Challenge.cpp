
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

// DAY 3 (1266. Minimum Time Visiting All Points)========================================================================================================

int minTimeToVisitAllPoints(vector<vector<int>>& points) 
{
    int n = points.size();
    int time = 0;
    for(int i = 1; i < n; i++)
    {
        int di = abs(points[i][0] - points[i-1][0]);
        int dj = abs(points[i][1] - points[i-1][1]);
        time += max(di, dj);
    }
    return time;
}

// DAY 4 (2264. Largest 3-Same-Digit Number in String)=========================================================================================

string largestGoodInteger(string num) 
{
    int n = num.size();
    int maxDig = -1;
    string maxNum = "";
    
    if(n < 3) return maxNum;

    for(int i = 2; i < n; i++)
        if(num[i] == num[i-1] && num[i] == num[i-2])
            maxDig = max(maxDig, num[i]-'0');
    maxNum = maxDig == -1? "" :
        maxDig == 0? "000" : to_string(maxDig*100 + maxDig*10 + maxDig);
    return maxNum;
}

// DAY 5 (1688. Count of Matches in Tournament)=================================================================================================

int numberOfMatches(int n) 
{
    int totalMatches = 0;
    while(n != 1)
    {
        totalMatches += n/2;
        n = (n+1)/2;
    }
    return totalMatches;
}
