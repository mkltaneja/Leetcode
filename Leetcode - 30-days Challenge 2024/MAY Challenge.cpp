
// DAY 1 (2000. Reverse Prefix of Word)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string reversePrefix(string word, char ch) 
{
    int size = word.size();
    string ans = "";
    bool found = false;
    for(int partIdx = 0; partIdx < size; partIdx++)
    {
        ans += word[partIdx];
        if(word[partIdx] == ch && !found)
        {
            reverse(ans.begin(), ans.end());
            found = true;
        }
    }

    return ans;
}

// DAY 2 (2441. Largest Positive Integer That Exists With Its Negative)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int findMaxK(vector<int>& nums) 
{
    unordered_set<int> numSet;
    int ans = -1;
    for(int num : nums)
    {
        if(numSet.count(-num))
            ans = max(ans, abs(num));
        numSet.insert(num);
    }
    return ans;
}

// DAY 3 (165. Compare Version Numbers)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int compareVersion(string version1, string version2) 
{
    int idx1 = 0, idx2 = 0;
    int size1 = version1.size(), size2 = version2.size();
    while(idx1 < size1 || idx2 < size2)
    {
        int num1 = 0, num2 = 0;
        while(idx1 < size1 && version1[idx1] != '.')
            num1 = num1*10 + (version1[idx1++]-'0');
        while(idx2 < size2 && version2[idx2] != '.')
            num2 = num2*10 + (version2[idx2++]-'0');
        
        if(num1 > num2)
            return 1;
        if(num2 > num1)
            return -1;
        
        idx1++, idx2++;
    }

    return 0;
}

// DAY 4 (881. Boats to Save People)=====================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

int numRescueBoats(vector<int>& people, int limit) 
{
    int size = people.size();
    sort(people.begin(), people.end());
    int start = 0, end = size-1;
    int minBoats = 0;
    while(start <= end)
    {
        if(people[start] + people[end] <= limit)
            start++, end--;
        else end--;
        minBoats++;
    }
    return minBoats;
}

// DAY 5 (237. Delete Node in a Linked List)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void deleteNode(ListNode* node) 
{
    if(!node) return;
    ListNode* prevNode = nullptr;
    while(node->next)
    {
        node->val = node->next->val;
        prevNode = node;
        node = node->next;
    }
    assert(prevNode != nullptr);

    prevNode->next = nullptr;
}

// DAY 6 (2487. Remove Nodes From Linked List)====================================================================================

// APPROACH 1 (Using deque to compare values)

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* removeNodes(ListNode* head) 
{
    vector<ListNode*> deque;
    ListNode* itr = head;
    ListNode* res = new ListNode(-1);
    while(itr)
    {
        while(!deque.empty() && deque.back()->val < itr->val)
            deque.pop_back();
        deque.push_back(itr);
        itr = itr->next;
    }
    itr = res;
    for(ListNode* node : deque)
    {
        itr->next = node;
        itr = itr->next;
    }

    return res->next;
}

// APPROACH 2 (Without additional space - reversing the list) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* reverseList(ListNode* head)
{
    ListNode* curr = head, *prev = nullptr;
    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

ListNode* removeNodes(ListNode* head) 
{
    ListNode* newHead = reverseList(head);
    ListNode* itr = newHead;
    while(itr)
    {
        while(itr->next && itr->next->val < itr->val)
            itr->next = itr->next->next;
        itr = itr->next;
    }
    head = reverseList(newHead);
    return head;
}

// DAY 7 (2816. Double a Number Represented as a Linked List)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* reverseList(ListNode* head)
{
    ListNode* curr = head, *prev = nullptr;
    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

ListNode* doubleIt(ListNode* head) 
{
    ListNode* newHead = reverseList(head);
    ListNode* itr = newHead, *prev = nullptr;
    int carry = 0;
    while(itr)
    {
        int sum = itr->val*2 + carry;
        int currVal = sum % 10;
        carry = sum / 10;
        itr->val = currVal;
        prev = itr;
        itr = itr->next;
    }
    if(carry && prev)
        prev->next = new ListNode(carry);

    head = reverseList(newHead);

    return head;
}

// DAY 8 (506. Relative Ranks)==========================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<string> findRelativeRanks(vector<int>& score) 
{
    vector<int> scoreSorted = score;
    unordered_map<int,int> posInSorted;
    vector<string> place;
    sort(scoreSorted.rbegin(), scoreSorted.rend());
    for(int idx = 0; idx < scoreSorted.size(); idx++)
        posInSorted[scoreSorted[idx]] = idx+1;
    for(int currScore : score)
    {
        if(posInSorted[currScore] == 1)
            place.emplace_back("Gold Medal");
        else if(posInSorted[currScore] == 2)
            place.emplace_back("Silver Medal");
        else if(posInSorted[currScore] == 3)
            place.emplace_back("Bronze Medal");
        else place.emplace_back(to_string(posInSorted[currScore]));
    }
    return place;
}

// DAY 9 (3075. Maximize Happiness of Selected Children)==================================================================

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

long long maximumHappinessSum(vector<int>& happiness, int k) 
{
    int n = happiness.size();
    long long maxScore = 0;
    sort(happiness.begin(), happiness.end(), greater<int>());
    for(int i = 0; i < k && i < n; i++)
        maxScore += max(0, happiness[i] - i);
    return maxScore;
}

// DAY 10 (786. K-th Smallest Prime Fraction)=============================================================================

// APPROACH 1 (Brute Force -> Comparing all pairs)

// Time Complexity = O(n^2 + n*logn)
// Space Complexity = O(n^2)

#define f first
#define s second
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) 
{
    int size = arr.size();
    vector<pair<double, pair<int,int>>> fractions;
    for(int idx1 = 0; idx1 < size; idx1++)
        for(int idx2 = idx1+1; idx2 < size; idx2++)
            fractions.push_back({1.0 * arr[idx1] / arr[idx2], {arr[idx1], arr[idx2]}});
    sort(fractions.begin(), fractions.end());

    return {fractions[k-1].s.f, fractions[k-1].s.s};
}

// APPROACH 2 (Binary Search) --> [OPTIMIZED]

// Time Complexity = O(n*log(n))
// Space Complexity = O(1)

vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) 
{
    double lo = 0, hi = 1;
    int size = arr.size();
    while(lo <= hi)
    {
        double mid = (lo + hi) / 2;
        int count = 0, num = 0, den = 0;
        double maxFrac = 0;
        for(int idx1 = 0, idx2 = 1; idx1 < size; idx1++)
        {
            while(idx2 < size && 1.0*arr[idx1]/arr[idx2] > mid) 
                idx2++;
            count += size - idx2;
            if(idx2 < size && 1.0*arr[idx1]/arr[idx2] > maxFrac)
            {
                maxFrac = 1.0*arr[idx1]/arr[idx2];
                num = arr[idx1];
                den = arr[idx2];
            }
        }
        if(count == k)
            return {num, den};
        if(count < k)
            lo = mid;
        else hi = mid;
    }
    return {-1, -1};
}

// DAY 11 (857. Minimum Cost to Hire K Workers)==============================================================================

// Time Complexity = O(n*logn + n*logk)
// Space Complexity = O(n + k)

double mincostToHireWorkers(vector<int>& quality, vector<int>& wage, int k) 
{
    int size = wage.size();
    vector<pair<double, int>> wqRatio(size);
    priority_queue<int> minkQualities;
    int totalQuality = 0;
    double minPay = DBL_MAX;
    for(int idx = 0; idx < size; idx++)
        wqRatio[idx] = {1.0 * wage[idx] / quality[idx], quality[idx]};
    sort(wqRatio.begin(), wqRatio.end());

    for(int idx = 0; idx < size; idx++)
    {
        minkQualities.push(wqRatio[idx].second);
        double ratio = wqRatio[idx].first;
        totalQuality += wqRatio[idx].second;

        if(minkQualities.size() > k)
        {
            totalQuality -= minkQualities.top();
            minkQualities.pop();
        }

        if(minkQualities.size() == k)
            minPay = min(minPay, totalQuality * ratio);
    }

    return minPay;
}

// DAY 12 (2373. Largest Local Values in a Matrix)=====================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

vector<vector<int>> largestLocal(vector<vector<int>>& grid) 
{
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> maxLocal(n-2, vector<int>(m-2, 0));
    for(int i = 0; i < n-2; i++)
        for(int j = 0; j < m-2; j++)
            maxLocal[i][j] = max({grid[i][j], grid[i][j+1], grid[i][j+2],
                                  grid[i+1][j], grid[i+1][j+1], grid[i+1][j+2],
                                  grid[i+2][j], grid[i+2][j+1], grid[i+2][j+2]});
    return maxLocal;
}

// DAY 13 (861. Score After Flipping Matrix)==============================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

int countOffBitsForColumn(int col, int rows, vector<vector<int>> &grid)
{
    int count = 0;
    for(int row = 0; row < rows; row++)
        count += grid[row][col] == 0;
    return count;
}

void toggleRow(int row, int cols, vector<vector<int>> &grid)
{
    for(int col = 0; col < cols; col++)
        grid[row][col] ^= 1;
}

void toggleColumn(int col, int rows, vector<vector<int>> &grid)
{
    for(int row = 0; row < rows; row++)
        grid[row][col] ^= 1;
}

int getMaxScore(int rows, int cols, vector<vector<int>> &grid)
{
    int score = 0;
    for(int row = 0; row < rows; row++)
    {
        int num = 0;
        for(int col = 0; col < cols; col++)
            num = num*2 + grid[row][col];
        score += num;
    }
    return score;
}

void solveForRemainingBits(int rows, int cols, vector<vector<int>> &grid)
{
    for(int col = 1; col < cols; col++)
    {
        int offBits = countOffBitsForColumn(col, rows, grid);
        if(offBits > rows/2)
            toggleColumn(col, rows, grid);
    }
}

void solveForMSB(int rows, int cols, vector<vector<int>> &grid)
{
    int offBits = countOffBitsForColumn(0, rows, grid);
    if(offBits == rows)
        toggleColumn(0, rows, grid);
    else if(offBits)
        for(int row = 0; row < rows; row++)
            if(grid[row][0] == 0)
                toggleRow(row, cols, grid);
}

int matrixScore(vector<vector<int>>& grid)
{
    int rows = grid.size(), cols = grid[0].size();

    solveForMSB(rows, cols, grid);
    solveForRemainingBits(rows, cols, grid);
    
    int maxScore = getMaxScore(rows, cols, grid);

    return maxScore;
}


// DAY 14 (1219. Path with Maximum Gold)=======================================================================================

// Time Complexity = O(4^g * (n*m)) [g = gold depth]
// Space Complexity = O(g) [g = gold depth]

int getMaximumGoldDFS(int row, int col, int rows, int cols, vector<vector<int>> &grid)
{
    if(row == -1 || col == -1 || row == rows || col == cols || grid[row][col] == 0)
        return 0;

    int currGold = grid[row][col];
    grid[row][col] = 0;

    int bottomMax = getMaximumGoldDFS(row+1, col, rows, cols, grid);
    int rightMax = getMaximumGoldDFS(row, col+1, rows, cols, grid);
    int topMax = getMaximumGoldDFS(row-1, col, rows, cols, grid);
    int leftMax = getMaximumGoldDFS(row, col-1, rows, cols, grid);

    grid[row][col] = currGold;

    return currGold + max({bottomMax, rightMax, topMax, leftMax});
}

int getMaximumGold(vector<vector<int>>& grid)
{
    int maxGold = 0;
    int rows = grid.size(), cols = grid[0].size();
    for(int row = 0; row < rows; row++)
        for(int col = 0; col < cols; col++)
            if(grid[row][col])
                maxGold = max(maxGold, getMaximumGoldDFS(row, col, rows, cols, grid));
    return maxGold;
}

// DAY 15 (2812. Find the Safest Path in a Grid)=================================================================================================


// Time Complexity = O(n^2 + n^2 * log(n))
// Space Complexity = O(n^2)

int rows = 0, cols = 0;
int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int maxDist = 0;
int minDist[404][404];
bool visited[404][404];

void getMinimumDistances(vector<vector<int>> &grid)
{
    memset(minDist, -1, sizeof(minDist));
    queue<pair<int,int>> que;
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(grid[row][col])
            {
                que.push({row, col});
                minDist[row][col] = 0;
            }
        }
    }
    
    int dist = 0;
    while(!que.empty())
    {
        int size = que.size();
        while(size--)
        {
            int row = que.front().first;
            int col = que.front().second;
            que.pop();

            for(int d = 0; d < 4; d++)
            {
                int nxtRow = row + dir[d][0], nxtCol = col + dir[d][1];
                if(nxtRow != -1 && nxtCol != -1 && nxtRow < rows && nxtCol < cols && minDist[nxtRow][nxtCol] == -1)
                {
                    minDist[nxtRow][nxtCol] = dist + 1;
                    maxDist = max(maxDist, dist + 1);
                    que.push({nxtRow, nxtCol});
                }
            }
        }
        dist++;
    }
}

bool isValidSF(int candidate, int row, int col)
{
    if(row == -1 || col == -1 || row == rows || col == cols || minDist[row][col] < candidate || visited[row][col])
        return false;
    if(row == rows-1 && col == cols-1)
        return true;
    visited[row][col] = true;

    return isValidSF(candidate, row + 1, col) | 
        isValidSF(candidate, row, col + 1) | 
        isValidSF(candidate, row - 1, col) | 
        isValidSF(candidate, row, col - 1);
}

int getMaxSafenessFactor()
{
    int lo = 0, hi = maxDist;
    int safenessFactor = 0;
    while(lo <= hi)
    {
        int mid = (lo + hi) >> 1;
        memset(visited, false, sizeof(visited));
        if(isValidSF(mid, 0, 0))
        {
            safenessFactor = mid;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    return safenessFactor;
}

int maximumSafenessFactor(vector<vector<int>>& grid)
{
    rows = grid.size(), cols = grid[0].size();
    getMinimumDistances(grid);

    int maxSafenessFactor = minDist[0][0] == 0 || minDist[rows-1][cols-1] == 0? 0 : getMaxSafenessFactor();
    return maxSafenessFactor;
}

// DAY 16 (2331. Evaluate Boolean Binary Tree)=========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool evaluateTree(TreeNode* root) 
{
    if(!root)
        return false;
    if(!root->left && !root->right)
        return root->val;
    
    bool leftAns = evaluateTree(root->left);
    bool rightAns = evaluateTree(root->right);
    if(root->val == 2)
        return leftAns | rightAns;
    return leftAns & rightAns;
}

// DAY 17 (1325. Delete Leaves With a Given Value)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(h)

TreeNode* removeLeafNodes(TreeNode* root, int target) 
{
    if(!root)
        return nullptr;
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);

    if(!root->left && !root->right && root->val == target)
        return nullptr;
    return root;
}

// DAY 18 (979. Distribute Coins in Binary Tree)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(h)

int totalMoves = 0;

int distributeCoinsDFS(TreeNode* node)
{
    if(!node) return 0;

    int leftStones = distributeCoinsDFS(node->left);
    int rightStones = distributeCoinsDFS(node->right);

    totalMoves += abs(leftStones) + abs(rightStones);

    return leftStones + rightStones + (node->val - 1);
}

int distributeCoins(TreeNode* root) 
{
    distributeCoinsDFS(root);
    return totalMoves;
}
