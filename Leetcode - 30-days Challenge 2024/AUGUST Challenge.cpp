// DAY 1 (2678. Number of Senior Citizens)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int countSeniors(vector<string>& details)
{
    int totalPassengers = 0;
    for(string detail : details)
        totalPassengers += (detail[11]-'0') * 10 + (detail[12]-'0') > 60;
    
    return totalPassengers;
}

// DAY 2 (2134. Minimum Swaps to Group All 1's Together II)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minSwaps(vector<int>& nums)
{
    int size = nums.size();
    int totalOnes = 0;
    for(int num : nums)
        totalOnes += num;
    
    int currOnes = 0;
    for(int idx = 0; idx < totalOnes; idx++)
        currOnes += nums[idx];
    
    int minSwaps = totalOnes - currOnes;
    for(int idx = 0; idx < size; idx++)
    {
        currOnes += nums[(idx + totalOnes) % size];
        currOnes -= nums[idx];
        minSwaps = min(minSwaps, totalOnes - currOnes);
    }

    return minSwaps;
}

// DAY 3 (1460. Make Two Arrays Equal by Reversing Subarrays)=================================================================================

// Time Complexity = O(n + 1000)
// Space Complexity = O(1000)

bool canBeEqual(vector<int>& target, vector<int>& arr)
{
    vector<int> freq(1001, 0);
    for(int num : arr)
        freq[num]++;
    for(int num : target)
        freq[num]--;
    for(int num = 1; num <= 1000; num++)
        if(freq[num])
            return false;

    return true;
}

// DAY 4 (1508. Range Sum of Sorted Subarray Sums)=====================================================================================================

// APPROACH 1 (Brute Force)

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    vector<int> narr;
    for(int i = 0; i < n; i++)
    {
        int currSum = 0;
        for(int j = i; j < n; j++)
        {
            currSum += nums[j];
            narr.push_back(currSum);
        }
    }
    sort(narr.begin(), narr.end());

    int ans = 0;
    for(int i = left-1; i < right; i++)
        ans = (ans % MOD + narr[i] % MOD) % MOD;

    return ans;
}

// APPROACH 2 (Binary Search)

// Time Complexity = O(n*log(sum))
// Space Complexity = O(1)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    long long ans = getSumOfFirstK(nums, n, right) % MOD - getSumOfFirstK(nums, n, left-1) % MOD;
    return (ans + MOD) % MOD;
}

pair<int, long long> totalSubarraysLessThanMaxsum(vector<int>& nums, int n, int maxSum)
{
    int count = 0;
    long long currSum = 0, windowSum = 0, totalSum = 0;
    for(int i = 0, j = 0; i < n; i++)
    {
        currSum += nums[i];
        windowSum += nums[i] * (i - j + 1);
        while(currSum > maxSum)
        {
            windowSum -= currSum;
            currSum -= nums[j++];
        }
        count += i - j + 1;
        totalSum += windowSum;
    }

    return {count, totalSum};
}

long long getSumOfFirstK(vector<int>& nums, int n, int k)
{
    int minSum = *min_element(nums.begin(), nums.end());
    int maxSum = accumulate(nums.begin(), nums.end(), 0);
    long long lo = minSum, hi = maxSum;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);

        if(totalSubarraysLessThanMaxsum(nums, n, mid).first >= k)
            hi = mid - 1;
        else lo = mid + 1;
    }

    auto [count, sum] = totalSubarraysLessThanMaxsum(nums, n, lo);

    return sum - lo * (count - k);
}

// DAY 5 (2053. Kth Distinct String in an Array)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string kthDistinct(vector<string>& arr, int k)
{
    int size = arr.size();
    unordered_map<string, int> freqMap;
    for(int idx = 0; idx < size; idx++)
        freqMap[arr[idx]]++;
    
    int visited = 0;
    for(int idx = 0; idx < size; idx++)
        if(freqMap[arr[idx]] == 1 && ++visited == k)
            return arr[idx];
    
    return "";
}

// DAY 6 (3016. Minimum Number of Pushes to Type Word II)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumPushes(string word)
{
    vector<int> charFreqMap(26, 0);
    for(char c : word)
        charFreqMap[c-'a']++;
    sort(charFreqMap.rbegin(), charFreqMap.rend());
    
    int numKeysPushed = 0;
    for(int idx = 0; idx < 26 && charFreqMap[idx]; idx++)
        numKeysPushed += charFreqMap[idx] * ((idx / 8) + 1);
    
    return numKeysPushed;
}

// DAY 8 (885. Spiral Matrix III)================================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
{
    int totalNums = rows * cols;
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int minRow = rStart, minCol = cStart, maxRow = rStart, maxCol = cStart;
    int currRow = rStart, currCol = cStart;
    int numsCovered = 0;
    int currDir = 0;
    vector<vector<int>> ans;

    while(numsCovered < totalNums)
    {
        while(numsCovered < totalNums && currCol >= minCol && currCol <= maxCol && currRow >= minRow && currRow <= maxRow)
        {
            if(currRow >= 0 && currRow < rows && currCol >= 0 && currCol < cols)
            {
                ans.push_back({currRow, currCol});
                numsCovered++;
            }
            
            currRow += dir[currDir][0];
            currCol += dir[currDir][1];
        }

        if(currDir == 0)
            maxCol++;
        else if(currDir == 1)
            maxRow++;
        else if(currDir == 2)
            minCol--;
        else minRow--;

        currDir = (currDir + 1) % 4;
    }

    return ans;
}

// DAY 9 (840. Magic Squares In Grid)=============================================================================

// Time Compexity = O(n*m)
// Space Compexity = O(1)

bool isMagicSquare(int row, int col, vector<vector<int>> &grid)
{
    unordered_set<int> st;
    int rowSum[3] = {0}, colSum[3] = {0}, diagSum[2] = {0};
    for(int r = row; r < row + 3; r++)
    {
        for(int c = col; c < col + 3; c++)
        {
            if(grid[r][c] < 1 || grid[r][c] > 9)
                return false;
            st.insert(grid[r][c]);

            int ridx = r - row;
            int cidx = c - col;
            rowSum[ridx] += grid[r][c];
            colSum[cidx] += grid[r][c];
            if(ridx == cidx)
                diagSum[0] += grid[r][c];
            if(ridx + cidx == 2)
                diagSum[1] += grid[r][c];
        }
    }
    if((rowSum[0] != rowSum[1] || rowSum[0] != rowSum[2]) || (colSum[0] != colSum[1] || colSum[0] != colSum[2]) || (diagSum[0] != diagSum[1]) || st.size() != 9)
        return false;
    return true;
}

int numMagicSquaresInside(vector<vector<int>>& grid)
{
    int rows = grid.size(), cols = grid[0].size();
    int magicSquares = 0;
    for(int row = 0; row <= rows-3; row++)
        for(int col = 0; col <= cols-3; col++)
            if(isMagicSquare(row, col, grid))
                magicSquares++;

    return magicSquares;
}

// DAY 13 (40. Combination Sum II)============================================================

// Time Complexity = O(2^n)
// Space Complexity = O(2^n)

vector<vector<int>> ans;

void getCombinations(int i, vector<int> &candidates, int target, vector<int> &curr)
{
    if(target <= 0)
    {
        if(target == 0)
            ans.push_back(curr);
        return;
    }
    for(int j = i; j < candidates.size(); j++)
    {
        if(j == i || candidates[j] != candidates[j-1])
        {
            curr.push_back(candidates[j]);
            getCombinations(j+1, candidates, target - candidates[j], curr);
            curr.pop_back();
        }
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    sort(candidates.begin(), candidates.end());
    vector<int> curr;
    getCombinations(0, candidates, target, curr);
    return ans;
}

// DAY 15 (860. Lemonade Change)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool lemonadeChange(vector<int>& bills)
{
    int fives = 0, tens = 0;
    for(int bill : bills)
    {
        if(bill == 5)
            fives++;
        else if(bill == 10)
        {
            if(!fives)
                return false;
            fives--;
            tens++;
        }
        else
        {
            if(tens && fives)
                tens--, fives--;
            else if(fives >= 3)
                fives -= 3;
            else return false;
        }
    }

    return true;
}

// DAY 16 (624. Maximum Distance in Arrays)======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxDistance(vector<vector<int>>& arrays)
{
    int st1 = -1, st2 = -1, end1 = -1, end2 = -1;
    for(int idx = 0; idx < arrays.size(); idx++)
    {
        if(st1 == -1 || arrays[st1][0] >= arrays[idx][0])
        {
            st2 = st1;
            st1 = idx;
        }
        else if(st2 == -1 || arrays[st2][0] >= arrays[idx][0])
            st2 = idx;
        
        if(end1 == -1 || arrays[end1].back() <= arrays[idx].back())
        {
            end2 = end1;
            end1 = idx;
        }
        else if(end2 == -1 || arrays[end2].back() <= arrays[idx].back())
            end2 = idx;
    }

    return st1 == end1? max(arrays[end1].back() - arrays[st2][0], arrays[end2].back() - arrays[st1][0]) : arrays[end1].back() - arrays[st1][0];
}

// DAY 19 (650. 2 Keys Keyboard)================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int minStepsDFS(int n, int chars, int lastCopied, vector<vector<int>> &cache)
{
    if(chars > n)
        return INT_MAX;
    if(chars == n)
        return 0;
    if(cache[chars][lastCopied] != -1)
        return cache[chars][lastCopied];
    long long pasteSteps = INT_MAX, copySteps = INT_MAX;
    
    if(lastCopied != chars)
        copySteps = 1ll + minStepsDFS(n, chars, chars, cache);
    if(lastCopied)
        pasteSteps = 1ll + minStepsDFS(n, chars + lastCopied, lastCopied, cache);

    return cache[chars][lastCopied] = min({copySteps, pasteSteps, 1ll * INT_MAX});
}

int minSteps(int n)
{
    vector<vector<int>> cache(n+1, vector<int>(n, -1));
    return minStepsDFS(n, 1, 0, cache);
}

// DAY 20 (1140. Stone Game II)==================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int getMaximumStones(int idx, int m, bool isAliceTurn, vector<int> &piles, vector<vector<vector<int>>> &cache)
{
    if(idx == piles.size())
        return 0;
    if(cache[idx][m][isAliceTurn] != -1)
        return cache[idx][m][isAliceTurn];
    
    int totalStones = 0, res = isAliceTurn? 0 : INT_MAX;
    for(int x = 1; x <= min(2*m, (int)piles.size() - idx); x++)
    {
        totalStones += piles[idx + x - 1];
        if(isAliceTurn)
            res = max(res, getMaximumStones(idx + x, max(x, m), false, piles, cache) + totalStones);
        else res = min(res, getMaximumStones(idx + x, max(x, m), true, piles, cache));
    }
    return cache[idx][m][isAliceTurn] = res;
}

int stoneGameII(vector<int>& piles)
{
    vector<vector<vector<int>>> cache(piles.size(), vector<vector<int>>(piles.size()+1, vector<int>(2, -1)));
    return getMaximumStones(0, 1, true, piles, cache);
}

// DAY 21 (664. Strange Printer)===========================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int strangePrinterDFS(int lidx, int ridx, string &s, vector<vector<int>> &cache)
{
    if(lidx == ridx)
        return 1;
    if(cache[lidx][ridx] != -1)
        return cache[lidx][ridx];
    
    int minPrints = INT_MAX;
    for(int idx = lidx; idx < ridx; idx++)
    {
        minPrints = min(minPrints, strangePrinterDFS(lidx, idx, s, cache) + strangePrinterDFS(idx+1, ridx, s, cache));
    }
    return cache[lidx][ridx] = minPrints - (s[lidx] == s[ridx]);
}

int strangePrinter(string s)
{
    vector<vector<int>> cache(s.size(), vector<int>(s.size(), -1));
    return strangePrinterDFS(0, s.size()-1, s, cache);
}

// DAY 22 (476. Number Complement)=========================================================

// Time Complexity = O(log(num))
// Space Complexity = O(1)

int findComplement(int num)
{
    int newNum = 0, tmp = num, shifts = 0;
    while(tmp)
    {
        newNum |= ((tmp & 1 ^ 1) << shifts);
        tmp >>= 1;
        shifts++;
    }
    return newNum;
}

// DAY 23 (592. Fraction Addition and Subtraction)==========================================================

// Time Complexity = O(n*max(num))
// Space Complexity = O(1)

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
} 

void calculateExpression(int prevNum, int prevDen, int &currNum, int &currDen, int &currSign)
{
    if(prevDen == 0)
    {
        if(currSign == -1)
            currNum *= -1;
        return;
    }
    
    int newDen = (prevDen * currDen) / __gcd(prevDen, currDen);

    int prevFactor = newDen / prevDen;
    int currFactor = newDen / currDen;

    prevNum *= prevFactor;
    currNum *= currFactor;

    int newNum = prevNum + currSign * currNum;

    currNum = newNum;
    currDen = newDen;
}

void simplifyExpression(int &num, int &den)
{
    if(num == 0)
    {
        den = 1;
        return;
    }
    for(int fac = 2; fac <= min(abs(num), abs(den)); fac++)
    {
        while(num % fac == 0 && den % fac == 0)
        {
            num /= fac;
            den /= fac;
        }
    }
}

string fractionAddition(string expression)
{
    int size = expression.size();
    int prevNum = 0, prevDen = 0, currNum = 0, currDen = 0, currSign = 1;
    bool isDen = false;
    for(int idx = 0; idx < size; idx++)
    {
        if(expression[idx] == '+' || expression[idx] == '-')
        {
            currSign = expression[idx] == '+'? 1 : -1;
            isDen = false;
        }
        else if(expression[idx] == '/')
            isDen = true;
        else
        {
            while(idx < size && isDigit(expression[idx]))
            {
                if(isDen)
                    currDen = currDen * 10 + (expression[idx]-'0');
                else currNum = currNum * 10 + (expression[idx]-'0');
                idx++;
            }
            idx--;


            if(isDen)
            {
                calculateExpression(prevNum, prevDen, currNum, currDen, currSign);
                simplifyExpression(currNum, currDen);
            
                prevNum = currNum;
                prevDen = currDen;
                currNum = 0, currDen = 0, currSign = 1;
            }
        }
    }

    return to_string(prevNum) + "/" + to_string(prevDen);
}

// DAY 24 (564. Find the Closest Palindrome)================================================================================

// Time Complexity = O(log2(n)*log10(n))
// Space Complexity = O(log10(n))

#define ll long long

ll findPal(ll num)
{
    string numStr = to_string(num);
    int size = numStr.size();
    int left = (size - 1) / 2, right = size / 2;
    while(left >= 0)
        numStr[right++] = numStr[left--];
    ll numAns = stoll(numStr);
    return numAns;
}

ll findClosestSmaller(ll num)
{
    ll lo = 0, hi = num, ans = -1;
    while(lo <= hi)
    {
        ll mid = lo + ((hi - lo) >> 1);
        ll palNum = findPal(mid);
        if(palNum < num)
        {
            ans = palNum;
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
    return ans;
}

ll findClosestLarger(ll num)
{
    ll lo = num, hi = LLONG_MAX, ans = -1;
    while(lo <= hi)
    {
        ll mid = lo + ((hi - lo) >> 1);
        ll palNum = findPal(mid);
        if(palNum > num)
        {
            ans = palNum;
            hi = mid - 1;
        }
        else lo = mid + 1;
    }
    return ans;
}

string nearestPalindromic(string n)
{
    ll num = stoll(n);
    ll closestSmaller = findClosestSmaller(num);
    ll closestLarger = findClosestLarger(num);
    if(abs(num - closestLarger) < abs(num - closestSmaller))
        return to_string(closestLarger);
    return to_string(closestSmaller);
}

// DAY 25 (145. Binary Tree Postorder Traversal)===================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

void postorderTraversalDFS(TreeNode* node, vector<int> &postNodes)
{
    if(!node) return;
    postorderTraversalDFS(node->left, postNodes);
    postorderTraversalDFS(node->right, postNodes);
    postNodes.push_back(node->val);
}

vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> postNodes;
    postorderTraversalDFS(root, postNodes);
    return postNodes;
}

// DAY 26 (590. N-ary Tree Postorder Traversal)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Solution {
public:

    void postorderDFS(Node* root, vector<int> &postNodes)
    {
        if(!root) return;
        for(Node* node : root->children)
            postorderDFS(node, postNodes);
        postNodes.push_back(root->val);
    }

    vector<int> postorder(Node* root)
    {
        vector<int> postNodes;
        postorderDFS(root, postNodes);
        return postNodes;
    }
};

// DAY 27 (1514. Path with Maximum Probability)=======================================================================

// Time Complexity = O(n^2 * logn)
// Space Complexity = O(n^2)

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node)
{
    vector<vector<pair<int,double>>> graph(n);
    for(int idx = 0; idx < edges.size(); idx++)
    {
        graph[edges[idx][0]].push_back({edges[idx][1], succProb[idx]});
        graph[edges[idx][1]].push_back({edges[idx][0], succProb[idx]});
    }

    priority_queue<pair<double,int>> maxPq;
    vector<double> maxProb(n, 0);
    maxPq.push({1.0, start_node});
    maxProb[start_node] = 1.0;
    while(!maxPq.empty())
    {
        double currProb = maxPq.top().first;
        int currNode = maxPq.top().second;
        maxPq.pop();
        if(currNode == end_node)
            return currProb;

        for(pair<int,double> &child : graph[currNode])
        {
            int childNode = child.first;
            double prob = child.second;
            if(maxProb[childNode] < currProb * prob)
            {
                maxProb[childNode] = currProb * prob;
                maxPq.push({currProb * prob, childNode});
            }
        }
    }
    return 0.0;
}

// DAY 28 (1905. Count Sub Islands)==================================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void visitIsland(int row, int col, int rows, int cols, vector<vector<bool>> &isVisited, vector<vector<int>> &grid1, vector<vector<int>> &grid2, vector<vector<int>> &islandCells, bool &isValidIsland)
{
    if(row == -1 || col == -1 || row == rows || col == cols || isVisited[row][col] || !grid2[row][col])
        return;
    if(!grid1[row][col])
        isValidIsland = false;
    
    isVisited[row][col] = true;
    islandCells.push_back({row, col});
    
    for(int d = 0; d < 4; d++)
        visitIsland(row + dir[d][0], col + dir[d][1], rows, cols, isVisited, grid1, grid2, islandCells, isValidIsland);
}

int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2)
{
    int rows = grid2.size(), cols = grid2[0].size();
    int validIslands = 0;
    vector<vector<bool>> isVisited(rows, vector<bool>(cols, false));
    for(int row = 0; row < rows; row++)
    {
        for(int col = 0; col < cols; col++)
        {
            if(grid2[row][col] && !isVisited[row][col])
            {
                vector<vector<int>> islandCells;
                bool isValidIsland = true;
                visitIsland(row, col, rows, cols, isVisited, grid1, grid2, islandCells, isValidIsland);
                validIslands += isValidIsland;
            }
        }
    }
    return validIslands;
}

// DAY 29 (947. Most Stones Removed with Same Row or Column)==================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n)

class DSU
{
    public:
    int size;
    vector<int> par, parSize;

    DSU(int size)
    {
        this->size = size;
        this->par.resize(size);
        this->parSize.assign(size, 1);
        for(int node = 0; node < size; node++)
            this->par[node] = node;
    }

    int findPar(int node)
    {
        return par[node] == node? node : findPar(par[node]);
    }

    bool merge(int node1, int node2)
    {
        int par1 = findPar(node1);
        int par2 = findPar(node2);
        if(par1 == par2)
            return false;
        
        if(parSize[par1] < parSize[par2])
            swap(par1, par2);
        
        parSize[par2] = par1;
        par[par2] = par1;

        return true;
    }
};

int removeStones(vector<vector<int>>& stones)
{
    int size = stones.size();
    DSU dsu(size);
    int count = size;

    for(int idx1 = 0; idx1 < size; idx1++)
        for(int idx2 = idx1 + 1; idx2 < size; idx2++)
            if(stones[idx1][0] == stones[idx2][0] || stones[idx1][1] == stones[idx2][1])
                if(dsu.merge(idx1, idx2))
                    count--;
    return size - count;
}

// DAY 31 (1514. Path with Maximum Probability)===================================================================================

// Time Complexity = O(E * logV)
// Space Complexity = O(E)

double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node)
{
    vector<vector<pair<double, int>>> graph(n);
    priority_queue<pair<double, int>> maxPq;
    vector<double> maxProb(n, 0);
    
    maxProb[start_node] = 1;
    maxPq.push({1, start_node});

    for(int idx = 0; idx < edges.size(); idx++)
    {
        graph[edges[idx][0]].push_back({succProb[idx], edges[idx][1]});
        graph[edges[idx][1]].push_back({succProb[idx], edges[idx][0]});
    }

    while(!maxPq.empty())
    {
        double psf = maxPq.top().first;
        int parent = maxPq.top().second;
        maxPq.pop();

        if(parent == end_node)
            return psf;

        for(pair<double, int> &child : graph[parent])
        {
            if(psf * child.first > maxProb[child.second])
            {
                maxProb[child.second] = psf * child.first;
                maxPq.push({maxProb[child.second], child.second});
            }
        }
    }

    return 0;
}
