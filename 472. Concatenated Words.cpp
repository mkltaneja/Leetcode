
class trie
{
    public:
    vector<trie*> v;
    bool wordEnd;
    trie()
    {
        this->v.assign(26,nullptr);
        this->wordEnd = false;
    }
};
trie* t = new trie();

void insert(string &s)
{
    trie* temp = t;
    for(char c : s)
    {
        if(!temp->v[c-'a'])
            temp->v[c-'a'] = new trie();
        temp = temp->v[c-'a'];
    }
    temp->wordEnd = true;
}

bool checkans(int i, string &s, int wes, vector<string> &ans, vector<int> &dp)
{
    if(dp[i] != -1) return dp[i];
    trie *itr = t;
    for(int j = i; j < s.size(); j++)
    {
        if(itr->v[s[j]-'a'])
        {
            itr = itr->v[s[j]-'a'];
            if(itr->wordEnd && checkans(j+1, s, wes+1, ans, dp))
                return dp[i] = true;
        }
        else return dp[i] = false;
    }
    if(itr == t && wes > 1)
    {
        ans.push_back(s);
        return dp[i] = true;
    }
    return dp[i] = false;
}

vector<string> findAllConcatenatedWordsInADict(vector<string>& words) 
{
    for(string s : words)
        insert(s);
    
    vector<string> ans;
    for(string s : words)
    {
        vector<int> dp(s.size()+1, -1);
        checkans(0, s, 0, ans, dp);
    }
    return ans;
}