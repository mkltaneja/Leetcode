// DAY 1 (1706. Where Will the Ball Fall)===========================================================================

vector<int> findBall(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();

    vector<int> ans(m, -1);
    for(int x = 0; x < m; x++)
    {
        int i = 0, j = x;
        while(i < n)
        {
            if(grid[i][j] == 1 && (j+1 == m || grid[i][j+1] == -1)) break;
            if(grid[i][j] == -1 && (j-1 == -1 || grid[i][j-1] == 1)) break;
            j += grid[i++][j];
        }
        if(i == n) ans[x] = j;
    }

    return ans;
}

// DAY 2 (433. Minimum Genetic Mutation)=================================================================================

int minMutation(string start, string end, vector<string>& bank) 
{
    if(start == end) return 0;

    unordered_set<string> st;
    for(string &s : bank)
        st.insert(s);

    queue<string> que;
    que.push(start);

    int lvl = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            string curr = que.front();
            que.pop();

            for(int i = 0; i < 8; i++)
            {
                for(char c : {'A', 'C', 'G', 'T'})
                {
                    if(c == curr[i]) continue;

                    string nxt = curr.substr(0,i) + c + curr.substr(i+1);
                    if(!st.count(nxt)) continue;
                    st.erase(nxt);

                    if(nxt == end) return lvl+1;

                    que.push(nxt);
                }
            }
        }
        lvl++;
    }

    return -1;
}

// DAY 3 (2131. Longest Palindrome by Concatenating Two Letter Words)===================================================================================

int longestPalindrome(vector<string>& words) 
{
    int match = 0, mid = 0;
    unordered_map<string,int> mp;
    for(string &s : words)
    {
        string opp = string() + s[1] + s[0];
        if(mp[opp]) 
        {
            match++;
            mp[opp]--;
        }
        else mp[s]++;
    }
    for(auto &p : mp)
    {
        if(!p.second) continue;
        if(p.first[0] == p.first[1])
        {
            mid++;
            break;
        }
    }

    return match*4 + mid*2;
}

// DAY 4 (345. Reverse Vowels of a String)=======================================================================================================

string reverseVowels(string s) 
{
    auto isVowel = [&](char c){
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int i = 0, j = s.size()-1;
    while(i < j)
    {
        while(i < j && !isVowel(tolower(s[i]))) i++;
        while(i < j && !isVowel(tolower(s[j]))) j--;

        swap(s[i++], s[j--]);
    }

    return s;
}

// DAY 5 (212. Word Search II)========================================================================================================

class Trie
{
    public:
    vector<Trie*> trie;
    bool wordEnd;
    Trie()
    {
        this->trie.assign(26, nullptr);
        this->wordEnd = false;
    }

    void insert(Trie* &node, string &word)
    {
        Trie* itr = node;
        for(char &c : word)
        {
            if(!itr->trie[c-'a'])
                itr->trie[c-'a'] = new Trie();
            itr = itr->trie[c-'a'];
        }
        itr->wordEnd = true;
    }
};
Trie* root = new Trie();

unordered_set<string> res;
void dfs(int i, int j, int n, int m, string &curr, vector<vector<char>> &board, Trie* node, vector<vector<bool>> &vis)
{
    if(i == -1 || j == -1 || i == n || j == m || !node->trie[board[i][j]-'a'] || vis[i][j])
        return;

    curr += board[i][j];
    vis[i][j] = true;

    if(node->trie[board[i][j]-'a']->wordEnd) res.insert(curr);

    dfs(i+1, j, n, m, curr, board, node->trie[board[i][j]-'a'], vis);
    dfs(i, j+1, n, m, curr, board, node->trie[board[i][j]-'a'], vis);
    dfs(i-1, j, n, m, curr, board, node->trie[board[i][j]-'a'], vis);
    dfs(i, j-1, n, m, curr, board, node->trie[board[i][j]-'a'], vis);

    curr.pop_back();
    vis[i][j] = false;
}

vector<string> findWords(vector<vector<char>>& board, vector<string>& words) 
{
    int n = board.size(), m = board[0].size();

    for(string &word : words)
        root->insert(root, word);

    vector<vector<bool>> vis(n, vector<bool>(m, false));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            string curr = "";
            dfs(i, j, n, m, curr, board, root, vis);
        }
    }

    vector<string> ans;
    for(string s : res)
        ans.push_back(s);

    return ans;
}

// DAY 6 (899. Orderly Queue)===========================================================================================

string orderlyQueue(string s, int k) 
{
    if(k > 1)
    {
        sort(s.begin(), s.end());
        return s;
    }

    string ans = string(s.size(), 'z');
    for(int i = 0; i < s.size(); i++)
        ans = min(ans, s.substr(i) + s.substr(0,i));
    return ans;
}
