
// DAY 1 (1550. Three Consecutive Odds)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool threeConsecutiveOdds(vector<int>& arr)
{
    int size = arr.size();
    for(int idx = 0; idx < size-2; idx++)
        if((arr[idx] & 1) && (arr[idx+1] & 1) && (arr[idx+2] & 1))
            return true;
    return false;
}

// DAY 2 (350. Intersection of Two Arrays II)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ans;
    unordered_map<int,int> nums1Map;
    for(int num : nums1)
        nums1Map[num]++;
    for(int num : nums2)
        if(nums1Map[num]-- > 0)
            ans.push_back(num);
    return ans;
}

// DAY 3 (1509. Minimum Difference Between Largest and Smallest Value in Three Moves)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minDifference(vector<int>& nums)
{
    if(nums.size() <= 4)
        return 0;
    int min1 = INT_MAX, min2 = INT_MAX, min3 = INT_MAX, min4 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN, max4 = INT_MIN;
    for(int num : nums)
    {
        if(num >= max1)
        {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if(num >= max2)
        {
            max4 = max3;
            max3 = max2;
            max2 = num;
        }
        else if(num >= max3)
        {
            max4 = max3;
            max3 = num;
        }
        else if(num >= max4)
            max4 = num;
        
        if(num <= min1)
        {
            min4 = min3;
            min3 = min2;
            min2 = min1;
            min1 = num;
        }
        else if(num <= min2)
        {
            min4 = min3;
            min3 = min2;
            min2 = num;
        }
        else if(num <= min3)
        {
            min4 = min3;
            min3 = num;
        }
        else if(num <= min4)
            min4 = num;
    }
    return min({max1 - min4, max2 - min3, max3 - min2, max4 - min1});
}

// DAY 4 (2181. Merge Nodes in Between Zeros)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* mergeNodes(ListNode* head)
{
    ListNode* newHead = new ListNode(-1);
    ListNode* itr1 = head, *itr2 = newHead;
    int currSum = 0;
    while(itr1)
    {
        currSum += itr1->val;
        if(itr1->val == 0)
        {
            if(currSum)
            {
                itr2->next = new ListNode(currSum);
                itr2 = itr2->next;
            }
            currSum = 0;
        }
        itr1 = itr1->next;
    }
    return newHead->next;
}

// DAY 5 (2058. Find the Minimum and Maximum Number of Nodes Between Critical Points)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> nodesBetweenCriticalPoints(ListNode* head)
{
    int idx = 1, prevCriticalIdx = -1, a = -1;
    vector<int> dist(2);
    dist[0] = INT_MAX, dist[1] = INT_MIN;
    ListNode* itr = head->next, *prev = head;
    while(itr->next)
    {
        if((prev->val < itr->val && itr->next->val < itr->val) || (prev->val > itr->val && itr->next->val > itr->val))
        {
            if(prevCriticalIdx != -1)
            {
                dist[0] = min(dist[0], idx - prevCriticalIdx);
                dist[1] = idx - a;
            }
            else a = idx;
            prevCriticalIdx = idx;
        }
        prev = itr;
        itr = itr->next;
        idx++;
    }
    return dist[0] == INT_MAX? vector<int>(2, -1) : dist;
}

// WEEK 1 (1101. The Earliest Moment When Everyone Become Friends)===================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

class DSU
{
    public:
    int size;
    vector<int> par, parSize;
    DSU(int size)
    {
        this->size = size;
        par.resize(size);
        parSize.assign(size, 1);
        for(int node = 0; node < size; node++)
            par[node] = node;
    }

    int findPar(int u)
    {
        return par[u] = par[u] == u? u : findPar(par[u]);
    }

    bool canMergeAndAllConnected(int u, int v)
    {
        int paru = findPar(u);
        int parv = findPar(v);

        if(paru == parv)
            return false;
        
        if(parSize[parv] > parSize[paru])
            swap(paru, parv);
        
        parSize[paru] += parSize[parv];
        par[parv] = paru;

        return parSize[paru] == this->size;
    }
};

int earliestAcq(vector<vector<int>>& logs, int n)
{
    sort(logs.begin(), logs.end());
    DSU dsu(n);

    for(vector<int> log : logs)
    {
        int timestamp = log[0];
        int x = log[1];
        int y = log[2];

        if(dsu.canMergeAndAllConnected(x, y))
            return timestamp;
    }
    return -1;
}

// DAY 6 (2582. Pass the Pillow)=============================================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

int passThePillow(int n, int time)
{
    int dir = int(ceil(1.0 * time / (n-1))) & 1;
    int index = (time % (n-1));
    if(index == 0)
        dir = (time / (n-1)) & 1? 0 : 1;
    return dir? (1 + index) : (n - index);
}

// DAY 7 (1518. Water Bottles)==========================================================================================

// Time Complexity = O(log[numExchange](numBottles))
// Space Complexity = O(1)

int numWaterBottles(int numBottles, int numExchange)
{
    int bottlesDrunk = 0, emptyBottles = 0;
    while(numBottles)
    {
        bottlesDrunk += numBottles;
        int currBottles = numBottles;
        numBottles = (currBottles + emptyBottles) / numExchange;
        emptyBottles = (currBottles + emptyBottles) % numExchange;
    }
    return bottlesDrunk;
}

// DAY 8 (1823. Find the Winner of the Circular Game)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getWinnerIndex(int n, int k)
{
    if(n == 1) return 0;
    return (getWinnerIndex(n-1, k) + k) % n;
}

int findTheWinner(int n, int k)
{
    return getWinnerIndex(n, k) + 1;
}

// DAY 9 (1701. Average Waiting Time)========================================================================================

// Time Complexity = O(n)
// Time Complexity = O(1)

double averageWaitingTime(vector<vector<int>>& customers)
{
    int totalCustomers = customers.size();
    long totalWaitingTime = 0, lastEndingTime = 0;
    for(vector<int> customer : customers)
    {
        long arrivalTime = customer[0];
        long time = customer[1];
        long currentWaitingTime = max(0l, lastEndingTime - arrivalTime) + time;
        lastEndingTime = arrivalTime + currentWaitingTime;
        totalWaitingTime += currentWaitingTime;
    }
    return 1.0 * totalWaitingTime / totalCustomers;
}

// DAY 10 (1598. Crawler Log Folder)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int minOperations(vector<string>& logs)
{
    int distanceFromRoot = 0;
    for(string log : logs)
    {
        if(log == "../")
            distanceFromRoot = max(distanceFromRoot - 1, 0);
        else if(log[0] != '.')
            distanceFromRoot++;
    }
    return distanceFromRoot;
}

// DAY 11 (1190. Reverse Substrings Between Each Pair of Parentheses)=============================================================

// APPROACH 1 (Naive way)

// Time Complexity = O(n^2)
// Space Complexity = O(n)

string reverseParentheses(string s)
{
    string ans = "";
    stack<int> st;
    for(char c : s)
    {
        if(c == '(')
            st.push(ans.size());
        else if(c == ')')
        {
            int startIdx = st.top();
            st.pop();
            reverse(ans.begin() + startIdx, ans.end());
        }
        else ans += c;
    }
    return ans;
}

// APPROACH 2 (Wormhole Teleportation Technique) --> [OPTIMIZED[

// Time Complexity = O(n)
// Space Complexity = O(n)

string reverseParentheses(string s)
{
    int n = s.size();
    string ans = "";
    stack<int> st;
    vector<int> bracePair(n);
    for(int idx = 0; idx < n; idx++)
    {
        if(s[idx] == '(')
            st.push(idx);
        else if(s[idx] == ')')
        {
            int pairIdx = st.top();
            st.pop();
            bracePair[pairIdx] = idx;
            bracePair[idx] = pairIdx;
        }
    }

    for(int idx = 0, dir = 1; idx < n; idx += dir)
    {
        if(s[idx] == '(' || s[idx] == ')')
        {
            idx = bracePair[idx];
            dir *= -1;
        }
        else ans += s[idx];
    }
    return ans;
}

// WEEK 2 (1836. Remove Duplicates From an Unsorted Linked List)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* deleteDuplicatesUnsorted(ListNode* head)
{
    unordered_map<int,int> freqMap;
    ListNode* itr = head;
    while(itr)
    {
        freqMap[itr->val]++;
        itr = itr->next;
    }

    itr = head;
    ListNode* prev = nullptr;
    while(itr)
    {
        if(freqMap[itr->val] > 1)
        {
            if(prev)
                prev->next = itr->next;
            else head = head->next;
        }
        else prev = itr;
        itr = itr->next;
    }
    return head;
}

// DAY 12 (1717. Maximum Score From Removing Substrings)===================================================================

// APPROACH 1 (Using Stack)

// Time Complexity = O(n)
// Space Complexity = O(n)

int getValue(stack<char> &st, int val)
{
    if(st.empty()) return 0;

    int cnt1 = 0, cnt2 = 0;
    char ch2 = st.top();
    while(!st.empty() && st.top() == ch2)
    {
        cnt2++;
        st.pop();
    }
    if(st.empty()) return 0;

    char ch1 = st.top();
    while(!st.empty() && st.top() == ch1)
    {
        cnt1++;
        st.pop();
    }

    return min(cnt1, cnt2) * val;
}

int maximumGain(string s, int x, int y)
{
    int ans = 0;
    stack<char> st;
    for(char c : s)
    {
        if(c == 'a' || c == 'b')
        {
            int xx = x, yy = y;
            char ch = 'b';
            if(c == 'b')
            {
                swap(xx, yy);
                ch = 'a';
            }
            if(yy > xx && !st.empty() && st.top() == ch)
            {
                ans += yy;
                st.pop();
            }
            else st.push(c);
        }
        else ans += getValue(st, min(x, y));
    }
    ans += getValue(st, min(x, y));

    return ans;
}

// APPROACH 2 (Without Stack - Considering "ab" as the greater string)

// Time Complexity = O(n)
// Space Complexity = O(1)

int maximumGain(string s, int x, int y)
{
    if(x < y)
    {
        swap(x, y);
        reverse(s.begin(), s.end());
    }

    int aCount = 0, bCount = 0, ans = 0;
    for(char c : s)
    {
        if(c == 'a')
            aCount++;
        else if(c == 'b')
        {
            if(aCount)
            {
                aCount--;
                ans += x;
            }
            else bCount++;
        }
        else
        {
            ans += min(aCount, bCount) * y;
            aCount = bCount = 0;
        }
    }
    ans += min(aCount, bCount) * y;
    return ans;
}

// DAY 13 (2751. Robot Collisions)=================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions)
{
    int size = positions.size();
    vector<vector<int>> roboStack;
    vector<vector<int>> confs(size);
    for(int idx = 0; idx < size; idx++)
        confs[idx] = {positions[idx], healths[idx], directions[idx] == 'R'? 1 : -1, idx};
    sort(confs.begin(), confs.end());
    
    for(vector<int> conf : confs)
    {
        int pos = conf[0];
        int health = conf[1];
        int dir = conf[2];
        int idx = conf[3];
        if(dir == -1)
        {
            while(!roboStack.empty() && roboStack.back()[1] > 0 && health > roboStack.back()[1])
            {
                roboStack.pop_back();
                health--;
            }
            if(!roboStack.empty() && health == roboStack.back()[1])
                roboStack.pop_back();
            else if(roboStack.empty() || roboStack.back()[1] < 0)
                roboStack.push_back({idx, dir * health});
            else roboStack.back()[1]--;
        }
        else roboStack.push_back({idx, dir * health});
    }

    sort(roboStack.begin(), roboStack.end());
    vector<int> ans;
    for(vector<int> robo : roboStack)
        ans.push_back(abs(robo[1]));
    
    return ans;
}

// DAY 14 (726. Number of Atoms)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool isNum(char c)
{
    return c >= '0' && c <= '9';
}

bool isUppercaseLetter(char c)
{
    return c >= 'A' && c <= 'Z';
}

bool isLowercaseLetter(char c)
{
    return c >= 'a' && c <= 'z';
}

string getAtom(string &formula, int size, int &start)
{
    if(!isUppercaseLetter(formula[start]))
        return "";
    string atom = string(1, formula[start++]);
    while(start < size && isLowercaseLetter(formula[start]))
        atom += formula[start++];
    return atom;
}

int getNum(string &formula, int size, int &start)
{
    int num = 0;
    while(start < size && isNum(formula[start]))
        num = num*10 + (formula[start++] - '0');
    return num? num : 1;
}

string countOfAtoms(string formula)
{
    int size = formula.size();
    map<string,int> tempMap;
    stack<map<string,int>> atomSt;
    
    atomSt.push(tempMap);

    for(int idx = 0; idx < size; )
    {
        if(formula[idx] == '(')
        {
            map<string,int> tempMap;
            atomSt.push(tempMap);
            idx++;
        }
        else if(formula[idx] == ')')
        {
            idx++;
            int num = getNum(formula, size, idx);
            map<string,int> tempMap = atomSt.top();
            atomSt.pop();

            for(pair<string,int> atomPair : tempMap)
            {
                atomPair.second *= num;
                atomSt.top()[atomPair.first] += atomPair.second;
            }
        }
        else
        {
            string atom = getAtom(formula, size, idx);
            if(atom == "")
                return "";
            int num = getNum(formula, size, idx);
            atomSt.top()[atom] += num;
        }
    }
    string ans = "";
    for(pair<string,int> atomPair : atomSt.top())
    {
        ans += atomPair.first;
        if(atomPair.second > 1)
            ans += to_string(atomPair.second);
    }
    return ans;
}

// DAY 15 (2196. Create Binary Tree From Descriptions)====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

TreeNode* createBinaryTree(vector<vector<int>>& descriptions)
{
    unordered_map<int,int> inDegree;
    unordered_map<int, TreeNode*> nodeMap;

    for(vector<int> desc : descriptions)
    {
        int parent = desc[0];
        int child = desc[1];
        int isLeft = desc[2];
        
        TreeNode* parentNode = nullptr;
        if(nodeMap.count(parent))
            parentNode = nodeMap[parent];
        else parentNode = new TreeNode(parent);
        nodeMap[parent] = parentNode;
        
        TreeNode* childNode = nullptr;
        if(nodeMap.count(child))
            childNode = nodeMap[child];
        else childNode = new TreeNode(child);
        nodeMap[child] = childNode;

        if(!isLeft)
            parentNode->right = childNode;
        else parentNode->left = childNode;

        inDegree[child]++;
    }
    for(vector<int> desc : descriptions)
        if(inDegree[desc[0]] == 0)
            return nodeMap[desc[0]];
    return nullptr;
}

// DAY 16 (2096. Step-By-Step Directions From a Binary Tree Node to Another)============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string path = "";
string startPath = "", destPath = "";

int getDirectionsDFS(TreeNode* root, int startValue, int destValue)
{
    if(!root) return 0;

    int leftVal = getDirectionsDFS(root->left, startValue, destValue);
    int rightVal = getDirectionsDFS(root->right, startValue, destValue);

    if(!leftVal && !rightVal)
        return root->val == startValue? 1 : (root->val == destValue? 2 : 0);
    if((leftVal && rightVal) || ((leftVal || rightVal) && (root->val == startValue || root->val == destValue)))
    {
        if(leftVal == 2)
            destPath += 'L';
        else if(rightVal == 2)
            destPath += 'R';
        if(leftVal == 1 || rightVal == 1)
            startPath += 'U';

        if(path.empty())
        {
            reverse(destPath.begin(), destPath.end());
            path = startPath + destPath;
        }
        return 0;
    }
    if(leftVal == 1 || rightVal == 1)
    {
        startPath += 'U';
        return 1;
    }

    destPath += leftVal == 2? 'L' : 'R';
    return 2;
}

string getDirections(TreeNode* root, int startValue, int destValue)
{
    getDirectionsDFS(root, startValue, destValue);
    return path;
}

// DAY 17 (1110. Delete Nodes And Return Forest)==============================================================================

// Time Complexty = O(n)
// Space Complexty = O(n)

vector<TreeNode*> roots;
unordered_set<int> toDeleteSet;

TreeNode* delNodesDFS(TreeNode* node)
{
    if(!node)
        return nullptr;
    
    node->left = delNodesDFS(node->left);
    node->right = delNodesDFS(node->right);

    if(toDeleteSet.count(node->val))
    {
        if(node->left)
            roots.push_back(node->left);
        if(node->right)
            roots.push_back(node->right);
        return nullptr;
    }
    return node;
}

vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete)
{
    toDeleteSet.insert(to_delete.begin(), to_delete.end());
    delNodesDFS(root);
    if(!toDeleteSet.count(root->val))
        roots.push_back(root);
    
    return roots;
}

// DAY 18 (1530. Number of Good Leaf Nodes Pairs)========================================================================================

// Time Complexity = O(n * distance * distance)
// Space Complexity = O(n * distance)

vector<int> countPairsDFS(TreeNode* node, int distance)
{
    if(!node)
        return vector<int>(distance + 2);
    if(!node->left && !node->right)
    {
        vector<int> ret(distance + 2);
        ret[0] = 1;
        return ret;
    }

    vector<int> lans = countPairsDFS(node->left, distance);
    vector<int> rans = countPairsDFS(node->right, distance);

    vector<int> curr(distance + 2);
    for(int d = 0; d < distance; d++)
        curr[d+1] = lans[d] + rans[d];
    curr[distance+1] = lans[distance+1] + rans[distance+1];

    for(int d1 = 0; d1 <= distance; d1++)
    {
        for(int d2 = 0; d2 <= distance; d2++)
        {
            if(d1 + d2 + 2 > distance)
                continue;
            curr[distance+1] += lans[d1] * rans[d2];
        }
    }

    return curr;
}

int countPairs(TreeNode* root, int distance)
{
    return countPairsDFS(root, distance)[distance+1];
}

// DAY 19 (1380. Lucky Numbers in a Matrix)===============================================================================

// Time Complexity = O(n * m)
// Space Complexity = O(n + m)

vector<int> luckyNumbers (vector<vector<int>>& matrix)
{
    int rows = matrix.size(), cols = matrix[0].size();
    vector<int> rowMin(rows, -1), colMax(cols, -1);
    vector<int> ans;
    for(int row = 0; row <= rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(row == rows)
            {
                if(rowMin[colMax[col]] == col)
                    ans.push_back(matrix[colMax[col]][col]);
                continue;
            }
            if(rowMin[row] == -1 || matrix[row][col] < matrix[row][rowMin[row]])
                rowMin[row] = col;
            if(colMax[col] == -1 || matrix[row][col] > matrix[colMax[col]][col])
                colMax[col] = row;
        }
    }
    return ans;
}

// DAY 20 (1605. Find Valid Matrix Given Row and Column Sums)=================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

vector<vector<int>> restoreMatrix(vector<int>& rowSum, vector<int>& colSum)
{
    int rows = rowSum.size(), cols = colSum.size();
    vector<vector<int>> matrix(rows, vector<int>(cols, 0));
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            int currVal = min(rowSum[row], colSum[col]);
            matrix[row][col] = currVal;
            rowSum[row] -= currVal;
            colSum[col] -= currVal;
        }
    }
    return matrix;
}
