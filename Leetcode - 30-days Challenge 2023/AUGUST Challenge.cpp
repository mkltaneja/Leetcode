// DAY 3 (17. Letter Combinations of a Phone Number)================================================================================================

vector<string> keys = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string> ans;

void dfs(int i, string &word, string &digits)
{
    if(i == digits.size())
    {
        if(!word.empty())
            ans.push_back(word);
        return;
    }

    for(char c : keys[digits[i]-'2'])
    {
        word += c;
        dfs(i+1, word, digits);
        word.pop_back();
    }
}

vector<string> letterCombinations(string digits) 
{
    string word = "";
    dfs(0, word, digits);
    return ans;
}

// DAY 4 (139. Word Break)===============================================================================================

class Trie
{
    public:
    vector<Trie*> child;
    bool wordEnd;
    Trie()
    {
        this->child.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(string &word, Trie* root)
    {
        Trie* curr = root;
        for(char c : word)
        {
            if(!curr->child[c-'a'])
                curr->child[c-'a'] = new Trie();
            curr = curr->child[c-'a'];
        }
        curr->wordEnd = true;
    }
};
Trie* root = new Trie();

bool canSegment(int i, Trie* itr, string &s, vector<int> &dp)
{
    if(i == s.size()) return true;
    if(dp[i] != -1) return dp[i];

    Trie* curr = itr;
    for(int j = i; j < s.size() && curr->child[s[j]-'a']; j++)
    {
        Trie* nxt = curr->child[s[j]-'a'];
        if(nxt->wordEnd)
            if(canSegment(j+1, root, s, dp))
                return dp[j] = 1;
        curr = nxt;
    }
    return dp[i] = 0;
}

bool wordBreak(string s, vector<string>& wordDict) 
{
    for(string &word : wordDict)
        root->insert(word, root);
    
    Trie* itr = root;
    vector<int> dp(s.size(), -1);
    return canSegment(0, itr, s, dp);
}
