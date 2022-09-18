
class trie
{
    public:
    vector<trie*> t;
    int x;
    trie()
    {
        this->t.assign(26,nullptr);
        this->x = 0;
    }
};
trie* root = new trie();

vector<int> sumPrefixScores(vector<string>& words) 
{
    for(string s : words)
    {
        trie* tmp = root;
        for(char c : s)
        {
            if(!tmp->t[c-'a'])
                tmp->t[c-'a'] = new trie();
            tmp->t[c-'a']->x++;
            tmp = tmp->t[c-'a'];
        }
    }

    vector<int> ans(words.size());
    for(int i = 0; i < words.size(); i++)
    {
        trie* tmp = root;
        for(char c : words[i])
        {
            ans[i] += tmp->t[c-'a']->x;
            tmp = tmp->t[c-'a'];
        }
    }

    return ans;
}
