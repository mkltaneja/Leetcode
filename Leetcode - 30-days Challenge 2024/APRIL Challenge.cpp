
// DAY 1 (58. Length of Last Word)=============================================================================================================

// Time Complexity = <O(n)
// Space Complexity = O(1)

int lengthOfLastWord(string s) 
{
    int len = 0;
    for(int idx = s.size()-1; idx >= 0; idx--)
    {
        if(s[idx] == ' ')
        {
            if(len) return len;
            continue;
        }
        len++;
    }
    return len;
}

// DAY 2 (205. Isomorphic Strings)====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(256)

bool isIsomorphic(string s, string t) 
{
    unordered_map<char,char> sCharMap, tCharMap;
    for(int idx = 0; idx < s.size(); idx++)
    {
        char a = s[idx], b = t[idx];
        if(sCharMap[a] && sCharMap[a] != b)
            return false;
        if(!sCharMap[a] && tCharMap[b] && tCharMap[b] != a)
            return false;
        sCharMap[a] = b;
        tCharMap[b] = a;
    }
    return true;
}

// DAY 3 (79. Word Search)=====================================================================================================

// Time Complexity = O(rows * cols * 4^wordSize)
// Space Complexity = O(wordSize) [Stack Space]

bool isWordPresent(int row, int col, int idx, int rows, int cols, int wordSize, string &word, vector<vector<char>> &board)
{
    if(idx == wordSize)
        return true;
    if(row == -1 || col == -1 || row == rows || col == cols || word[idx] != board[row][col])
        return false;

    char currChar = board[row][col];
    board[row][col] = '#';
    bool ans = isWordPresent(row+1, col, idx+1, rows, cols, wordSize, word, board) ||
        isWordPresent(row, col+1, idx+1, rows, cols, wordSize, word, board) ||
        isWordPresent(row-1, col, idx+1, rows, cols, wordSize, word, board) ||
        isWordPresent(row, col-1, idx+1, rows, cols, wordSize, word, board);
    board[row][col] = currChar;

    return ans;
}

bool exist(vector<vector<char>>& board, string word) 
{
    int rows = board.size(), cols = board[0].size(), wordSize = word.size();
    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            if(isWordPresent(row, col, 0, rows, cols, wordSize, word, board))
                return true;
    return false;
}

// DAY 4 (1614. Maximum Nesting Depth of the Parentheses)==================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxDepth(string s) 
{
    int currDepth = 0, maxDepth = 0;
    for(char c : s)
    {
        if(c != '(' && c != ')') continue;
        currDepth += c == '(';
        currDepth -= c == ')';
        maxDepth = max(maxDepth, currDepth);
    }
    return maxDepth;
}

// DAY 5 (1544. Make The String Great)============================================================================================

// APPROACH 1 (Brute Force)

// Time Complexity = O(n^2)
// Space Complexity = O(1)

bool areEqual(char a, char b)
{
    return (tolower(a) == tolower(b))
        && ((a == tolower(a) && b != tolower(b))
            || (a != tolower(a) && b == tolower(b)));
}

string makeGood(string s) 
{
    int size = s.size();
    bool checkMore = true;
    while(checkMore)
    {
        checkMore = false;
        string tmp = "";
        for(int idx = 0; idx < size; idx++)
        {
            if(idx+1 < size && areEqual(s[idx], s[idx+1]))
            {
                checkMore = true;
                idx++;
            }
            else tmp += s[idx];
        }
        s = tmp;
        tmp = "";
        size = s.size();
    }
    return s;
}

// APPROACH 2 (Using Stack)

// Time Complexity = O(n)
// Space Complexity = O(n)

bool areEqual(char a, char b)
{
    return (tolower(a) == tolower(b))
        && ((a == tolower(a) && b != tolower(b))
            || (a != tolower(a) && b == tolower(b)));
}

string makeGood(string s) 
{
    stack<char> st;
    string ans = "";
    for(char c : s)
    {
        if(!st.empty() && areEqual(st.top(), c))
            st.pop();
        else st.push(c);
    }
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// DAY 6 (1249. Minimum Remove to Make Valid Parentheses)=============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string minRemoveToMakeValid(string s) 
{
    stack<int> st;
    unordered_set<int> ignore;
    string ans = "";
    for(int idx = 0; idx < s.size(); idx++)
    {
        char c = s[idx];
        if(c == '(')
            st.push(idx);
        else if(c == ')')
        {
            if(st.empty())
                ignore.insert(idx);
            else st.pop();
        }
    }
    while(!st.empty())
    {
        ignore.insert(st.top());
        st.pop();
    }

    for(int idx = 0; idx < s.size(); idx++)
        if(!ignore.count(idx))
            ans += s[idx];
    
    return ans;
}
