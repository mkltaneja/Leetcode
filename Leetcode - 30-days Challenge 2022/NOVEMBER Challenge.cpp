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

// DAY 7 (1323. Maximum 69 Number)========================================================================================

int maximum69Number (int num) 
{
    int tmp = num, p = 1, x = 0;
    while(tmp)
    {
        if(tmp%10 == 6) x = p;
        p *= 10;
        tmp /= 10;
    }
    return num + 3*x;
}

// DAY 8 (1544. Make The String Great)==================================================================================

string makeGood(string s) 
{
    stack<char> st;
    for(char c : s)
    {
        char low = tolower(c);
        char up = toupper(c);

        if(st.empty())
            st.push(c);
        else if(st.top() == low && c == up)
            st.pop();
        else if(st.top() == up && c == low)
            st.pop();
        else st.push(c);
    }

    string ans = "";
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 9 (901. Online Stock Span)================================================================================

class StockSpanner {
public:

    #define f first
    #define s second
    stack<pair<int,int>> st; // {price, days}
    StockSpanner() 
    {
        
    }
    
    int next(int price) 
    {
        int days = 1;
        while(!st.empty() && st.top().f <= price)
        {
            days += st.top().s;
            st.pop();
        }
        st.push({price, days});

        return days;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

// DAY 10 (1047. Remove All Adjacent Duplicates In String)=================================================================

string removeDuplicates(string s) 
{
    stack<char> st;
    for(char &c : s)
    {
        if(!st.empty() && st.top() == c)
            st.pop();
        else st.push(c);
    }

    string ans = "";
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans;
}

// DAY 11 (26. Remove Duplicates from Sorted Array)=============================================================================

int removeDuplicates(vector<int>& nums) 
{
    int k = 0, i = 0, n = nums.size();
    while(i < n)
    {
        int j = i;
        while(j < n && nums[j] == nums[i]) j++;
        nums[k++] = nums[i];
        i = j;
    }

    return k;
}

// DAY 13 (151. Reverse Words in a String)=====================================================================================

string reverseWords(string s) 
{
    string ans = "";
    stack<string> words;
    int i = 0, n = s.size();
    while(i < n)
    {
        int j = i;
        string tmp = "";
        while(j < n && s[j] != ' ') tmp += s[j++];
        i = ++j;
        if(tmp.empty()) continue;
        words.push(tmp);
    }

    while(!words.empty())
    {
        ans += words.top() + " ";
        words.pop();
    }
    ans.pop_back();

    return ans;
}

// DAY 15 (222. Count Complete Tree Nodes)====================================================================================

int goDeep(TreeNode* node)
{
    int h = 0;
    TreeNode* l = node, *r = node;
    while(l && r)
    {
        h++;
        l = l->left;
        r = r->right;
    }
    return (!l && !r)? (1 << h)-1 : 0;
}

int dfs(TreeNode* node)
{
    if(!node) return 0;

    int count = goDeep(node);
    if(count) return count;
    int lans = dfs(node->left);
    int rans = dfs(node->right);

    return lans + rans + 1;
}

int countNodes(TreeNode* root) 
{
    return dfs(root);
}

// DAY 16 (374. Guess Number Higher or Lower)=================================================================================

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

class Solution {
public:
    int guessNumber(int n) 
    {
        int st = 1, end = n;
        while(st < end)
        {
            int num = st + (end - st)/2;
            int g = guess(num);
            if(g == 0) return num;
            if(g == -1) end = num - 1;
            if(g == 1) st = num + 1;
        }

        return st;
    }
};
