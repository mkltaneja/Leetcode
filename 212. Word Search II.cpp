
class trie
{
    public:
    vector<trie*> t;
    string wordAns;
    trie()
    {
        this->t.assign(26, nullptr);
        this->wordAns = "";
    }
};
trie* root = new trie();

void insert(string &s)
{
    trie* tmp = root;
    for(char c : s)
    {
        if(!tmp->t[c-'a'])
            tmp->t[c-'a'] = new trie();
        tmp = tmp->t[c-'a'];
    }
    tmp->wordAns = s;
}

set<string> uans;
void dfs(int i, int j, int n, int m, vector<vector<char>> &arr, trie* itr)
{
    if(i == -1 || j == -1 || i==n || j==m || arr[i][j] == '#' || !itr->t[arr[i][j]-'a'])
        return;
    
    char c = arr[i][j];
    arr[i][j] = '#';
    
    if(!itr->t[c-'a']->wordAns.empty())
        uans.insert(itr->t[c-'a']->wordAns);
    
    trie* nxt = itr->t[c-'a'];
    dfs(i+1, j, n, m, arr, nxt);
    dfs(i, j+1, n, m, arr, nxt);
    dfs(i-1, j, n, m, arr, nxt);
    dfs(i, j-1, n, m, arr, nxt);
    arr[i][j] = c;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
{
    for(string s : words)
        insert(s);
    
    int n = board.size(), m = board[0].size();
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            trie* itr = root;
            dfs(i, j, n, m, board, itr);
        }
    }
    
    vector<string> ans;
    for(string x : uans)
        ans.push_back(x);
    
    return ans;
}