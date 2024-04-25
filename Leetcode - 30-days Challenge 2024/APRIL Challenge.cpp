
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

// DAY 7 (678. Valid Parenthesis String)==================================================================================

// APPROACH 1 (Using Stacks)

// Time Complexity = O(n)
// Space Complexity = O(n)

bool checkValidString(string s)
{
    int size = s.size();
    stack<int> bracketStack, starStack;
    for(int idx = 0; idx < size; idx++)
    {
        if(s[idx] == '(')
            bracketStack.push(idx);
        else if(s[idx] == ')')
        {
            if(!bracketStack.empty())
                bracketStack.pop();
            else if(!starStack.empty())
                starStack.pop();
            else return false;
        }
        else starStack.push(idx);
    }

    while(!bracketStack.empty())
    {
        if(starStack.empty() || starStack.top() < bracketStack.top())
            return false;
        bracketStack.pop();
        starStack.pop();
    }

    return true;
}

// APPROACH 2 (Using Full and Partial Polarities of brackets)

// Time Complexity = O(n)
// Space Complexity = O(1)

bool checkValidString(string s) 
{
    int bracketPol = 0, starPol = 0;
    for(char c : s)
    {
        if(c == '(')
        {
            bracketPol++;
            starPol++;
        }
        else if(c == ')')
        {
            bracketPol--;
            starPol = max(0, starPol - 1);
        }
        else
        {
            bracketPol++;
            starPol = max(0, starPol - 1);
        }
        if(bracketPol < 0)
            return false;
    }

    return starPol == 0;
}

// DAY 8 (1700. Number of Students Unable to Eat Lunch)=====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int countStudents(vector<int>& students, vector<int>& sandwiches) 
{
    int ones = 0, zeros = 0;
    for(int student : students)
    {
        ones += student == 1;
        zeros += student == 0;
    }
    for(int sandwich : sandwiches)
    {
        if(sandwich == 0)
        {
            if(zeros-- == 0)
                return ones;
        }
        else
        {
            if(ones-- == 0)
                return zeros;
        }
    }
    return 0;
}


// DAY 9 (2073. Time Needed to Buy Tickets)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int timeRequiredToBuy(vector<int>& tickets, int k)
{
    int size = tickets.size();
    int ticketsReqd = tickets[k];
    int time = 0;
    for(int idx = 0; idx < size; idx++)
    {
        time += min(ticketsReqd, tickets[idx]);
        if(idx == k)
            ticketsReqd--;
    }
    return time;
}

// DAY 10 (950. Reveal Cards In Increasing Order)===============================================================================

// Time Complexity = O(n*logn + 2*n)
// Space Complexity = O(2*n)

vector<int> deckRevealedIncreasing(vector<int>& deck) 
{
    int size = deck.size();
    queue<int> minIdx;
    vector<int> reorderedDeck(size);
    sort(deck.begin(), deck.end());
    for(int idx = 0; idx < size; idx++)
        minIdx.push(idx);
    
    for(int idx = 0; idx < size; idx++)
    {
        int currIdx = minIdx.front();
        minIdx.pop();
        reorderedDeck[currIdx] = deck[idx];
        if(!minIdx.empty())
        {
            minIdx.push(minIdx.front());
            minIdx.pop();
        }
    }
    return reorderedDeck;
}

// DAY 11 (402. Remove K Digits)=============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string removeKdigits(string num, int k) 
{
    stack<char> numStack;
    string ans = "";
    for(char x : num)
    {
        while(!numStack.empty() && numStack.top() > x && k-- > 0)
            numStack.pop();
        if(x == '0' && numStack.empty()) continue;
        numStack.push(x);
    }
    while(!numStack.empty() && k-- > 0)
        numStack.pop();
    while(!numStack.empty())
    {
        ans += numStack.top();
        numStack.pop();
    }
    reverse(ans.begin(), ans.end());

    return ans.empty()? "0" : ans;
}

// DAY 12 (42. Trapping Rain Water)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int trap(vector<int>& height) 
{
    int size = height.size();
    int totalWater = 0;
    stack<int> heightSt;
    for(int idx = 0; idx < size; idx++)
    {
        while(!heightSt.empty() && height[heightSt.top()] < height[idx])
        {
            int bottom = height[heightSt.top()];
            heightSt.pop();
            if(!heightSt.empty())
            {
                int top = min(height[idx], height[heightSt.top()]);
                int left = heightSt.top();
                int right = idx;
                int currentWaterArea = (right - left - 1) * (top - bottom);
                totalWater += currentWaterArea;
            }
        }
        heightSt.push(idx);
    }
    return totalWater;
}

// DAY 13 (85. Maximal Rectangle)============================================================================================

// Time Complexity = O(rows * cols)
// Space Complexity = O(rols * cols)

void fillNextSmaller(vector<int> &heights, vector<int> &nextSmaller, int size, bool isLeft)
{
    stack<int> heightSt;
    for(int idx = 0; idx < size; idx++)
    {
        while(!heightSt.empty() && heights[idx] < heights[heightSt.top()])
        {
            nextSmaller[heightSt.top()] = isLeft? size - idx - 1 : idx;
            heightSt.pop();
        }
        heightSt.push(idx);
    }
}

int getAreaForRow(vector<int> &heights, int size)
{
    int maxArea = 0;
    vector<int> leftSmaller(size, -1), rightSmaller(size, size);
    fillNextSmaller(heights, rightSmaller, size, 0);
    
    reverse(heights.begin(), heights.end());
    fillNextSmaller(heights, leftSmaller, size, 1);
    reverse(heights.begin(), heights.end());
    reverse(leftSmaller.begin(), leftSmaller.end());

    for(int idx = 0; idx < size; idx++)
    {
        int height = heights[idx];
        int width = rightSmaller[idx] - leftSmaller[idx] - 1;
        int area = height * width;

        maxArea = max(maxArea, area);
    }

    return maxArea;
}

int maximalRectangle(vector<vector<char>>& matrix) 
{
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> matHeight(rows, vector<int>(cols, 0));
    int maxArea = 0;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(row == 0)
                matHeight[row][col] = matrix[row][col] - '0';
            else if(matrix[row][col]-'0')
                matHeight[row][col] = matHeight[row-1][col] + (matrix[row][col] - '0');
        }
        maxArea = max(maxArea, getAreaForRow(matHeight[row], cols));
    }
    
    return maxArea;
}

// DAY 14 (404. Sum of Left Leaves)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int sumOfLeftLeaves(TreeNode* root) 
{
    if(!root || !root->left && !root->right)
        return 0;
    int currSum = 0;
    if(root->left && !root->left->left && !root->left->right)
        currSum += root->left->val;
    else currSum += sumOfLeftLeaves(root->left);
    currSum += sumOfLeftLeaves(root->right);

    return currSum;
}

// DAY 15 (129. Sum Root to Leaf Numbers)============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int sumNumbersDFS(TreeNode* node, int num)
{
    if(!node) return 0;
    num = num*10 + node->val;
    if(!node->left && !node->right)
        return num;
    return sumNumbersDFS(node->left, num)
        + sumNumbersDFS(node->right, num);
}

int sumNumbers(TreeNode* root) 
{
    return sumNumbersDFS(root, 0);
}

// DAY 16 (623. Add One Row to Tree)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

TreeNode* addOneRowDFS(TreeNode* node, int val, bool isLeft, int currDepth, int depth)
{
    if(currDepth == depth)
        return isLeft? new TreeNode(val, node, nullptr) : new TreeNode(val, nullptr, node);
    if(!node)
        return nullptr;

    node->left = addOneRowDFS(node->left, val, true, currDepth+1, depth);
    node->right = addOneRowDFS(node->right, val, false, currDepth+1, depth);

    return node;
}

TreeNode* addOneRow(TreeNode* root, int val, int depth) 
{
    return addOneRowDFS(root, val, 1, 1, depth);
}

// DAY 17 (988. Smallest String Starting From Leaf)==========================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

string smallestString = string(9000, 'z');
void smallestFromLeafDFS(TreeNode* node, string &currString)
{
    if(!node) return;
    if(!node->left && !node->right)
    {
        string tempString = currString + char(node->val + 'a');
        reverse(tempString.begin(), tempString.end());
        smallestString = min(smallestString, tempString);
        return;
    }

    currString += char(node->val + 'a');
    smallestFromLeafDFS(node->left, currString);
    smallestFromLeafDFS(node->right, currString);
    currString.pop_back();
}

string smallestFromLeaf(TreeNode* root) 
{
    string currString = "";
    smallestFromLeafDFS(root, currString);
    return smallestString;
}

// DAY 18 (463. Island Perimeter)================================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

int islandPerimeter(vector<vector<int>>& grid) 
{
    int rows = grid.size(), cols = grid[0].size();
    int totalPerimeter = 0;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(grid[row][col] == 0) continue;
            int isTopOutside = row == 0 || grid[row-1][col] == 0;
            int isBottomOutside = row == rows-1 || grid[row+1][col] == 0;
            int isLeftOutside = col == 0 || grid[row][col-1] == 0;
            int isRightOutside = col == cols-1 || grid[row][col+1] == 0;
            totalPerimeter += isTopOutside + isBottomOutside + isLeftOutside + isRightOutside;
        }
    }
    return totalPerimeter;
}

// DAY 19 (200. Number of Islands)=========================================================================================

// Time Complexity = O(rows * cols)
// Space Complexity = O(rows * cols)

void visitIsland(int row, int col, int rows, int cols, vector<vector<char>>& grid)
{
    if(row == -1 || col == -1 || row == rows || col == cols || grid[row][col] != '1')
        return;
    grid[row][col] = '2';
    visitIsland(row+1, col, rows, cols, grid);
    visitIsland(row, col+1, rows, cols, grid);
    visitIsland(row-1, col, rows, cols, grid);
    visitIsland(row, col-1, rows, cols, grid);
}

int numIslands(vector<vector<char>>& grid)
{
    int rows = grid.size(), cols = grid[0].size();
    int totalIslands = 0;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(grid[row][col] == '1')
            {
                totalIslands++;
                visitIsland(row, col, rows, cols, grid);
            }
        }
    }
    return totalIslands;
}

// DAY 20 (1992. Find All Groups of Farmland)==========================================================================

// Time Complexity = O(rows * cols)
// Space Complexity = O(rows * cols)

vector<int> visitFarmland(int row, int col, int rows, int cols, vector<vector<int>> &land)
{
    int startRow = row, endRow = row;
    int startCol = col, endCol = col;
    while(endRow < rows && land[endRow][col]) endRow++;
    while(endCol < cols && land[row][endCol]) endCol++;
    for(int row = startRow; row < endRow; row++)
        for(int col = startCol; col < endCol; col++)
            land[row][col] = 0;
    return {endRow-1, endCol-1};
}

vector<vector<int>> findFarmland(vector<vector<int>>& land)
{
    int rows = land.size(), cols = land[0].size();
    const int OFFSET = 2;
    int currGroupId = 2;
    vector<vector<int>> ans;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(land[row][col] == 0) continue;

            vector<int> bottomRight = visitFarmland(row, col, rows, cols, land);
            ans.push_back({row, col, bottomRight[0], bottomRight[1]});
        }
    }
    return ans;
}

// DAY 21 (1971. Find if Path Exists in Graph)=========================================================================================

// Time Complexity = O(E)
// Space Complexity = O(V)

class DSU
{
    public:
    int size;
    vector<int> parent, parentSize;

    DSU(int size)
    {
        this->size = size;
        this->parent.resize(size);
        this->parentSize.assign(size, 1);
        for(int node = 0; node < size; node++)
            parent[node] = node;
    }

    int findParent(int node)
    {
        return parent[node] = node == parent[node]? node : findParent(parent[node]);
    }

    void merge(int node1, int node2)
    {
        int parent1 = findParent(node1);
        int parent2 = findParent(node2);
        if(parent1 == parent2)
            return;
        if(parentSize[parent1] < parentSize[parent2])
            swap(parent1, parent2);
        
        parentSize[parent1] += parentSize[parent2];
        parent[parent2] = parent1;
    }
};

bool validPath(int n, vector<vector<int>>& edges, int source, int destination) 
{
    DSU dsu(n);
    for(vector<int> &edge : edges)
    {
        int fromNode = edge[0];
        int toNode = edge[1];
        dsu.merge(fromNode, toNode);
    }
    int sourceParent = dsu.findParent(source);
    int destinationParent = dsu.findParent(destination);

    return sourceParent == destinationParent;
}

// DAY 22 (752. Open the Lock)======================================================================================================

// Time Complexity = O(n + 10^4)
// Space Complexity = O(n + 2*10^4)

int openLock(vector<string>& deadends, string target) 
{
    string start = "0000";
    queue<string> que;
    unordered_set<string> vis;
    unordered_set<string> deadendsSet;
    for(string deadend : deadends)
        deadendsSet.insert(deadend);
    if(deadendsSet.count(start))
        return -1;
    if(target == start)
        return 0;
    que.push(start);
    vis.insert(start);
    
    int minWays = 0;
    while(!que.empty())
    {
        int size = que.size();
        while(size--)
        {
            string curr = que.front();
            que.pop();
            for(int idx = 0; idx < 4; idx++)
            {
                string temp1 = curr;
                string temp2 = curr;
                temp1[idx] = char(((temp1[idx]-'0' + 1) % 10) + '0');
                temp2[idx] = char(((temp2[idx]-'0' + 9) % 10) + '0');
                if(!vis.count(temp1) && !deadendsSet.count(temp1))
                {
                    if(temp1 == target)
                        return minWays + 1;
                    que.push(temp1);
                    vis.insert(temp1);
                }
                if(!vis.count(temp2) && !deadendsSet.count(temp2))
                {
                    if(temp2 == target)
                        return minWays + 1;
                    que.push(temp2);
                    vis.insert(temp2);
                }
            }
        }
        minWays++;
    }
    return -1;
}

// DAY 23 (310. Minimum Height Trees)==================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) 
{
    if(n == 2)
        return {0, 1};
    vector<vector<int>> graph(n);
    vector<int> degree(n, 0);
    queue<int> que;
    unordered_set<int> remNodes;
    vector<int> ans;
    for(vector<int> &edge : edges)
    {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        degree[edge[0]]++;
        degree[edge[1]]++;
    }
    for(int node = 0; node < n; node++)
    {
        if(degree[node] == 1)
            que.push(node);
        else remNodes.insert(node);
    }
    
    while(remNodes.size() > 2)
    {
        int size = que.size();
        while(size--)
        {
            int currNode = que.front();
            que.pop();
            for(int nextNode : graph[currNode])
            {
                if(--degree[nextNode] == 1)
                {
                    que.push(nextNode);
                    remNodes.erase(nextNode);
                }
            }
        }
    }

    for(int node : remNodes)
        ans.push_back(node);
    return ans;
}

// DAY 24 (1137. N-th Tribonacci Number)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int tribonacci(int n) 
{
    if(n <= 1)
        return n;
    n -= 2;
    int curr = 1, prev = 1, prev_prev = 0;
    while(n--)
    {
        int currTemp = curr;
        curr = curr + prev + prev_prev;
        prev_prev = prev;
        prev = currTemp;
    }
    return curr;
}

// DAY 25 (2370. Longest Ideal Subsequence)==================================================================================

// APPROACH 1 (DFS - Going to every next valid character] -> Memory Limit Exceeded

// Time Complexity = O(n*2*k)
// Space Complexity = O(n*26)

int getMaxStringSize(int idx, int k, string s, vector<int> &cache, vector<vector<int>> &nextIdx)
{
    if(idx == s.size())
        return 0;
    if(cache[idx])
        return cache[idx];
    
    int maxSize = 0;
    for(int itr = max(0, s[idx]-'a'-k); itr <= min(25, s[idx]-'a'+k); itr++)
        maxSize = max(maxSize, getMaxStringSize(nextIdx[idx][itr], k, s, cache, nextIdx) + 1);
    return cache[idx] = maxSize;
}

int longestIdealString(string s, int k) 
{
    int size = s.size();
    vector<vector<int>> nextIdx(size, vector<int>(26, size));
    vector<int> charLastIdx(26, size);
    vector<int> cache(size, 0);
    int maxSize = 1;
    for(int idx = size-1; idx >= 0; idx--)
    {
        nextIdx[idx] = charLastIdx;
        charLastIdx[s[idx]-'a'] = idx;
    }

    for(int idx = 0; idx < size; idx++)
        maxSize = max(maxSize, getMaxStringSize(idx, k, s, cache, nextIdx));
    
    return maxSize;
}

// APPROACH 2 (Like LIS - Taking maximum of every character until now) [MOST OPTIMIZED]

// Time Complexity = O(n*2*k)
// Time Complexity = O(26)

int longestIdealString(string s, int k) 
{
    int size = s.size();
    int maxLen = 1;
    vector<int> cache(26, 0);
    for(int idx = 0; idx < size; idx++)
    {
        int chItr = s[idx]-'a';
        int currLen = 1;
        for(int itr = max(0, chItr-k); itr <= min(25, chItr+k); itr++)
            currLen = max(currLen, cache[itr] + 1);
        cache[chItr] = currLen;
        maxLen = max(maxLen, currLen);
    }
    return maxLen;
}
