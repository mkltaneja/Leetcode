// DAY 1 (290. Word Pattern)================================================================================

bool wordPattern(string pattern, string s) 
{
    vector<string> map(26, "#");
    unordered_set<string> vis;
    int j = 0;
    for(int i = 0; i < pattern.size(); i++)
    {
        string curr = "";
        while(j < s.size() && s[j] != ' ') curr += s[j++];
        j++;
        cout<<pattern[i]<<" -> "<<curr<<endl;
        if(map[pattern[i]-'a'] == curr) continue;
        if(curr.empty() || vis.count(curr)) return false;
        if(map[pattern[i]-'a'] == "#")
        {
            vis.insert(curr);
            map[pattern[i]-'a'] = curr;
        }
        else return false;
    }

    return j == s.size()+1;
}

// DAY 2 (520. Detect Capital)==================================================================================

bool isCap(char &c)
{
    return c >= 'A' && c <= 'Z';
}

bool detectCapitalUse(string word) 
{
    int caps = 0;
    for(char &c : word)
        if(isCap(c))
            caps++;
    return caps == word.size() || caps == 0 || (caps == 1 && isCap(word[0]));
}

// DAY 3 (944. Delete Columns to Make Sorted)====================================================================

int minDeletionSize(vector<string>& strs) 
{
    int dels = 0;
    int n = strs.size(), m = strs[0].size();
    for(int i = 0; i < m; i++)
    {
        for(int j = 1; j < n; j++)
        {
            if(strs[j][i] < strs[j-1][i])
            {
                dels++;
                break;
            }
        }
    }

    return dels;
}

// DAY 4 (2244. Minimum Rounds to Complete All Tasks)=====================================================================

int minimumRounds(vector<int>& tasks) 
{
    unordered_map<int,int> mp;
    for(int &x : tasks)
        mp[x]++;

    int ans = 0;
    for(auto &p : mp)
    {
        if(p.second == 1) return -1;
        ans += (p.second/3) + (p.second%3 > 0);
    }

    return ans;
}
