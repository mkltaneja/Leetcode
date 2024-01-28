
// DAY 1 (455. Assign Cookies)===========================================================================================

// APPROACH 1 (Using Map)

// Time Complexity = O(n + m*logn)
// Space Complexity = O(n)

int findContentChildren(vector<int>& g, vector<int>& s) 
{
    int gSize = g.size(), sSize = s.size();
    map<int, int> gMap;
    int satisfiedCount = 0;
    for(int greed : g)
        gMap[greed]++;
    for(int size : s)
    {
        auto justSmallerGreed = gMap.upper_bound(size);
        if(justSmallerGreed == gMap.begin()) continue;
        
        justSmallerGreed--;
        if(--(*justSmallerGreed).second == 0)
            gMap.erase(justSmallerGreed);
        satisfiedCount++;
    }
    return satisfiedCount;
}

// APPROACH 2 (2 pointer approach)

// Time Complexity = O(max(m*logn, n*logn))
// Space Complexity = O(1)

int findContentChildren(vector<int>& g, vector<int>& s)
{
    int gSize = g.size(), sSize = s.size();
    sort(g.rbegin(), g.rend());
    sort(s.rbegin(), s.rend());
    int satisfiedCount = 0;
    
    for(int p1 = 0, p2 = 0; p1 < gSize && p2 < sSize; p1++)
    {
        if(g[p1] <= s[p2])
        {
            satisfiedCount++;
            p2++;
        }
    }
    return satisfiedCount;
}

// DAY 2 (2610. Convert an Array Into a 2D Array With Conditions)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<vector<int>> findMatrix(vector<int>& nums) 
{
    int size = nums.size();
    unordered_map<int,int> freqMap;
    vector<vector<int>> ans;
    for(int num : nums)
        freqMap[num]++;
    
    while(!freqMap.empty())
    {
        vector<int> rowTemp;
        for(auto itr = freqMap.begin(); itr != freqMap.end(); )
        {
            rowTemp.push_back(itr->first);
            if(--itr->second == 0)
                itr = freqMap.erase(itr);
            else itr++;
        }
        ans.push_back(rowTemp);
    }
    return ans;
}

// DAY 3 (2125. Number of Laser Beams in a Bank)==================================================================================

// Time Complexity = O(rows*cols)
// Space Complexity = O(1)

int numberOfBeams(vector<string>& bank)
{
    int rows = bank.size();
    int cols = bank[0].size();
    
    int totalBeams = 0;
    int previousRowDevices = 0;
    for(string plan : bank)
    {
        int totalDevices = 0;
        for(char device : plan)
            totalDevices += (device == '1');
        totalBeams += totalDevices * previousRowDevices;
        if(totalDevices)
            previousRowDevices = totalDevices;
    }
    return totalBeams;
}

// DAY 4 (2870. Minimum Number of Operations to Make Array Empty)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int minOperations(vector<int> &nums)
{
    int size = nums.size();
    unordered_map<int,int> numCnt;
    for(int x : nums)
        numCnt[x]++;
    
    int totalOperations = 0;
    for(auto pair : numCnt)
    {
        int num = pair.first;
        int cnt = pair.second;
        if(cnt == 1) return -1;

        int k = cnt / 3;
        if(cnt % 3 == 0)
            totalOperations += k;
        else if(cnt % 3 == 1)
            totalOperations += k-1 + 2;
        else
            totalOperations += k + 1;
    }
    return totalOperations;
}

// DAY 5 (300. Longest Increasing Subsequence)=======================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int findLowerBound(vector<int> &lis, int num)
{
    int low = 0, high = lis.size()-1;
    int ans = lis.size();
    while(low <= high)
    {
        int mid = low + ((high - low) >> 1);
        if(lis[mid] < num)
            low = mid + 1;
        else
        {
            high = mid - 1;
            ans = mid;
        }
    }
    return ans;
}

int lengthOfLIS(vector<int> &nums)
{
    int size = nums.size();
    vector<int> lis;
    for(int num : nums)
    {
        int justGreaterIdx = findLowerBound(lis, num);
        if(justGreaterIdx == lis.size())
            lis.push_back(num);
        else lis[justGreaterIdx] = num;
    }
    return lis.size();
}

// DAY 6 (1235. Maximum Profit in Job Scheduling)=========================================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int findLowerBound(int endTime, int lo, int hi, vector<vector<int>> &times)
{
    while(lo < hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(times[mid][0] < endTime)
            lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int jobScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &profit)
{
    int size = startTime.size();
    vector<vector<int>> times(size);
    for(int idx = 0; idx < size; idx++)
        times[idx] = {startTime[idx], endTime[idx], profit[idx]};
    sort(times.begin(), times.end());

    vector<int> maxProfit(size, 0);
    maxProfit[size-1] = times[size-1][2];
    for(int idx = size-2; idx >= 0; idx--)
    {
        int nextJobIdx = findLowerBound(times[idx][1], idx+1, size, times);
        int nextJobProfit = nextJobIdx == size? 0 : maxProfit[nextJobIdx];
        maxProfit[idx] = max(maxProfit[idx+1], nextJobProfit + times[idx][2]);
    }

    return maxProfit[0];
}

// DAY 7 (446. Arithmetic Slices II - Subsequence)================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int numberOfArithmeticSlices(vector<int> &nums)
{
    int size = nums.size();
    unordered_map<int, unordered_map<long,int>> numDiffMap;
    int totalSeqs = 0;
    for(int idx1 = size-1; idx1 >= 0; idx1--)
    {
        for(int idx2 = idx1 + 1; idx2 < size; idx2++)
        {
            int num1 = nums[idx1];
            int num2 = nums[idx2];
            long diff = (long)num2 - num1;
            
            numDiffMap[idx1][diff] += numDiffMap[idx2][diff] + 1;
            totalSeqs += numDiffMap[idx2][diff];
        }
    }
    return totalSeqs;
}

// DAY 8 (938. Range Sum of BST)=================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(logn)

int rangeSumBST(TreeNode* root, int low, int high)
{
    if(!root) return 0;
    if(root->val < low)
        return rangeSumBST(root->right, low, high);
    if(root->val > high)
        return rangeSumBST(root->left, low, high);

    int leftSum = rangeSumBST(root->left, low, high);
    int rightSum = rangeSumBST(root->right, low, high);

    return leftSum + rightSum + root->val;
}

// DAY 9 (872. Leaf-Similar Trees)================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool isLeafNode(TreeNode* node)
{
    return !node->left && !node->right;
}

void addAllLeaves(TreeNode* node, vector<int> &leaves)
{
    if(!node)
        return;
    if(isLeafNode(node))
    {
        leaves.push_back(node->val);
        return;
    }

    addAllLeaves(node->left, leaves);
    addAllLeaves(node->right, leaves);
}

bool leafSimilar(TreeNode* root1, TreeNode* root2)
{
    vector<int> leaves1, leaves2;
    addAllLeaves(root1, leaves1);
    addAllLeaves(root2, leaves2);

    if(leaves1.size() != leaves2.size())
        return false;	

    for(int idx = 0; idx < leaves1.size(); idx++)
        if(leaves1[idx] != leaves2[idx])
            return false;
    
    return true;
}

// DAY 10 (2385. Amount of Time for Binary Tree to Be Infected)==========================================================================

// Time Complexity = O(n)
// Space Complexity = O(h)

int numMinutes = 0;
pair<int, bool> distanceFromNode(TreeNode* node, int start)
{
    if(!node) return {0, false};
    
    pair<int, bool> leftDepth = distanceFromNode(node->left, start);
    pair<int, bool> rightDepth = distanceFromNode(node->right, start);

    int currDepth = max(leftDepth.first, rightDepth.first);
    if(node->val == start)
    {
        numMinutes = max(numMinutes, currDepth);
        return {1, true};
    }
    else
    {
        if(leftDepth.second || rightDepth.second)
        {
            numMinutes = max(numMinutes, rightDepth.first + leftDepth.first);
            if(leftDepth.second)
                return {leftDepth.first + 1, true};
            else return {rightDepth.first + 1, true};
        }
    }

    return {currDepth + 1, false};
}

int amountOfTime(TreeNode* root, int start)
{
    distanceFromNode(root, start);
    return numMinutes;
}

// DAY 11 (1026. Maximum Difference Between Node and Ancestor)=========================================================================================

int maxAncestorDiff_DFS(TreeNode* node, int maxAncestorVal, int minAncestorVal)
{
    if(!node)
        return 0;

    int currDiff = max(abs(maxAncestorVal - node->val), abs(minAncestorVal - node->val));

    maxAncestorVal = max(maxAncestorVal, node->val);
    minAncestorVal = min(minAncestorVal, node->val);

    int leftMaxDiff = maxAncestorDiff_DFS(node->left, maxAncestorVal, minAncestorVal);
    int rightMaxDiff = maxAncestorDiff_DFS(node->right, maxAncestorVal, minAncestorVal);

    return max({currDiff, leftMaxDiff, rightMaxDiff});
}

int maxAncestorDiff(TreeNode* root)
{
    return maxAncestorDiff_DFS(root, root->val, root->val);
}

// DAY 12 (1704. Determine if String Halves Are Alike)===============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isVowel(char inputChar)
{
    inputChar = tolower(inputChar);
    return inputChar == 'a' || inputChar == 'e' || inputChar == 'i' || inputChar == 'o' || inputChar == 'u';
}

bool halvesAreAlike(string s)
{
    int aCount = 0, bCount = 0;
    int size = s.size();
    for(int itr = 0; itr < size/2; itr++)
    {
        aCount += isVowel(s[itr]);
        bCount += isVowel(s[size - itr - 1]);
    }

    return aCount == bCount;
}

// DAY 13 (1347. Minimum Number of Steps to Make Two Strings Anagram)====================================================================================

// Time Complexity = O(n + 26)
// Space Complexity = O(26)

int minSteps(string s, string t)
{
    vector<int> sMap(26), tMap(26);
    for(char c : s)
        sMap[c-'a']++;
    for(char c : t)
        tMap[c-'a']++;

    int extraCnt = 0, lessCnt = 0;
    for(int idx = 0; idx < 26; idx++)
    {
        if(tMap[idx] < sMap[idx])
            lessCnt += sMap[idx] - tMap[idx];
        else extraCnt += tMap[idx] - sMap[idx];
    }

    return max(extraCnt, lessCnt);
}

// DAY 14 (1657. Determine if Two Strings Are Close)==============================================================================================

// Time Complexity = O(n + m + 4*26 + 26log(26))
// Space Complexity = O(2*26)

bool closeStrings(string word1, string word2)
{
    int size1 = word1.size(), size2 = word2.size();
    if(size1 != size2) return false;

    vector<int> freq1(26), freq2(26);
    for(char c : word1)
        freq1[c-'a']++;
    for(char c : word2)
        freq2[c-'a']++;

    for(int idx = 0; idx < 26; idx++)
        if((freq1[idx] &&  !freq2[idx]) || (!freq1[idx] &&  freq2[idx]))
            return false;

    sort(freq1.begin(), freq1.end());
    sort(freq2.begin(), freq2.end());

    for(int idx = 0; idx < 26; idx++)
        if(freq1[idx] != freq2[idx])
            return false;

    return true;
}

// DAY 15 (2225. Find Players With Zero or One Losses)==============================================================================================

// Time Complexity = O(n + n*logn)
// Space Complexity = O(n)

vector<vector<int>> findWinners(vector<vector<int>> &matches)
{
    unordered_map<int, int> matchesLost;
    vector<vector<int>> ans(2);
    for(vector<int> &match : matches)
    {
        int winner = match[0];
        int loser = match[1];
        matchesLost[winner] = matchesLost[winner];
        matchesLost[loser]++;
    }

    for(auto playerLosses : matchesLost)
    {
        if(playerLosses.second == 0 || playerLosses.second == 1)
            ans[playerLosses.second].push_back(playerLosses.first);
    }

    sort(ans[0].begin(), ans[0].end());
    sort(ans[1].begin(), ans[1].end());
    return ans;
}

// DAY 16 (380. Insert Delete GetRandom O(1))================================================================================================

class RandomizedSet {
private:
    int size;
    vector<int> nums;
    unordered_map<int, int> numIdx;

public:
    RandomizedSet()
    {
        this->size = 0;
    }

    bool insert(int val)
    {
        if(numIdx.count(val))
            return false;

        nums.push_back(val);
        numIdx[val] = size++;

        return true;
    }

    bool remove(int val)
    {
        if(!numIdx.count(val))
            return false;
        
    int currIdx = numIdx[val];
        int lastIdx = --size;

        numIdx[nums[lastIdx]] = currIdx;
        swap(nums[currIdx], nums[lastIdx]);

        numIdx.erase(val);
        nums.pop_back();
        
        return true;
    }

    int getRandom()
    {
        int randIdx = rand() % size;
        return nums[randIdx];
    }

};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// DAY 17 (1207. Unique Number of Occurrences)====================================================================================

bool uniqueOccurrences(vector<int> &arr)
{
    int size = arr.size();
    unordered_map<int,int> freqMap;
    unordered_set<int> freqSet;
    for(int num : arr)
        freqMap[num]++;
    for(auto pair : freqMap)
    {
        if(freqSet.count(pair.second))
            return false;
        freqSet.insert(pair.second);
    }

    return true;
}

// DAY 18 (70. Climbing Stairs)======================================================================================

// Time Complexity = O(n)
// Time Complexity = O(1)

int climbStairs(int n)
{
    if(n <= 2) return n;

    int prevWays = 2;
    int prevPrevWays = 1;
    int currWays = 0;
    for(int step = 3; step <= n; step++)
    {
        currWays = prevWays + prevPrevWays;
        prevPrevWays = prevWays;
        prevWays = currWays;
    }

    return currWays;
}

// WEEK 3 (1165. Single-Row Keyboard)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(26)

int calculateTime(string keyboard, string word)
{
    vector<int> charPos(26, 0);
    int pos = 0, moves = 0, currPos = 0;
    for(char c : keyboard)
        charPos[c-'a'] = pos++;
    
    for(char c : word)
    {
        moves += abs(charPos[c-'a'] - currPos);
        currPos = charPos[c-'a'];
    }

    return moves;
}

// DAY 19 (931. Minimum Falling Path Sum)==================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n)

const int INF = 1e5;
void solveForMinSum(int size, vector<int> &minSum, vector<vector<int>> &matrix)
{
    for(int row = size-1; row >= 0; row--)
    {
        vector<int> minSumTemp(size, INF);
        for(int col = 0; col < size; col++)
        {
            if(row == size-1)
            {
                minSumTemp[col] = matrix[row][col];
                continue;
            }
            int bottomLeftSum = col? minSum[col-1] : INF;
            int bottomSum = minSum[col];
            int bottomRightSum = size-col-1? minSum[col+1] : INF;

            minSumTemp[col] = min({bottomLeftSum, bottomSum, bottomRightSum}) + matrix[row][col];
        }
        minSum = minSumTemp;
    }
}

int findMinAns(int size, vector<int> &minSum)
{
    int minAns = INF;
    for(int col = 0; col < size; col++)
        minAns = min(minAns, minSum[col]);
    return minAns;
}

int minFallingPathSum(vector<vector<int>> &matrix)
{
    int size = matrix.size();
    vector<int> minSum(size, INF);

    solveForMinSum(size, minSum, matrix);
    int minAns = findMinAns(size, minSum);

    return minAns;
}

// DAY 20 (907. Sum of Subarray Minimums)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int sumSubarrayMins(vector<int> &arr)
{
    int size = arr.size();
    vector<int> leftSmaller(size, -1), rightSmaller(size, size);
    stack<int> idxStack;
    int ans = 0, MOD = 1e9 + 7;
    for(int idx = 0; idx < size; idx++)
    {
        while(!idxStack.empty() && arr[idx] <= arr[idxStack.top()])
        {
            rightSmaller[idxStack.top()] = idx;
            idxStack.pop();
        }
        idxStack.push(idx);
    }
    while(!idxStack.empty())
        idxStack.pop();
    for(int idx = size-1; idx >= 0; idx--)
    {
        while(!idxStack.empty() && arr[idx] < arr[idxStack.top()])
        {
            leftSmaller[idxStack.top()] = idx;
            idxStack.pop();
        }
        idxStack.push(idx);
    }

    for(int idx = 0; idx < size; idx++)
    {
        int leftCount = idx - leftSmaller[idx];
        int rightCount = rightSmaller[idx] - idx;
        int totalCount = leftCount * rightCount;

        ans = ans % MOD + (((long long)totalCount % MOD) * (arr[idx] % MOD)) % MOD;
    }
    return ans;
}

// DAY 21 (198. House Robber)==================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int rob(vector<int> &nums)
{
    int size = nums.size();
    int lastRobbed = 0, lastRobbed2 = 0, maxRobbery = 0;
    for(int idx = 0; idx < size; idx++)
    {
        maxRobbery = max(lastRobbed, lastRobbed2 + nums[idx]);
        lastRobbed2 = lastRobbed;
        lastRobbed = maxRobbery;
    }
    return maxRobbery;
}

// DAY 22 (645. Set Mismatch)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> findErrorNums(vector<int> &nums)
{
    int size = nums.size();
    int missing = 0, extra = 0;
    for(int idx = 0; idx < size; idx++)
    {
        int position = abs(nums[idx]) - 1;
        if(nums[position] < 0)
            extra = position + 1;
        else nums[position] *= -1;
    }

    for(int idx = 0; idx < size; idx++)
        if(nums[idx] > 0)
            missing = idx + 1;

    vector<int> ans = {extra, missing};
    return ans;
}

// DAY 23 (1239. Maximum Length of a Concatenated String with Unique Characters)======================================================

// Time Complexity = O(2^n)
// Space Complexity = O(2^n)

int convertStringToBits(string &str)
{
    int res = 0;
    for(char c : str)
    {
        if(res & (1 << (c - 'a')))
            return 0;
        res |= (1 << (c-'a'));
    }
    return res;
}

int getMaxLen(vector<vector<int>> &arr)
{
    vector<vector<int>> prevStates;
    int maxLen = 0;
    for(int idx = 0; idx < arr.size(); idx++)
    {
        int prevSize = prevStates.size();
        for(int idx2 = 0; idx2 < prevSize; idx2++)
        {
            int state = prevStates[idx2][0];
            int len = prevStates[idx2][1];
            if(state & arr[idx][0]) continue;

            int currState = (state | arr[idx][0]);
            int currLen = len + arr[idx][1];
            maxLen = max(maxLen, currLen);
            prevStates.push_back({currState, currLen});
        }
        maxLen = max(maxLen, arr[idx][1]);
        prevStates.push_back({arr[idx][0], arr[idx][1]});
    }

    return maxLen;
}

int maxLength(vector<string> &arr)
{
    int size = arr.size();
    vector<vector<int>> bitArr;
    for(int idx = 0; idx < size; idx++)
    {
        int bitRes = convertStringToBits(arr[idx]);
        if(bitRes) 
            bitArr.push_back({bitRes, (int)arr[idx].size()});
    }
    return getMaxLen(bitArr);
}

// DAY 24 (1457. Pseudo-Palindromic Paths in a Binary Tree)===================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int totalPaths = 0;
void pseudoPalindromicPathsDFS(int pathMask, TreeNode* root)
{
    if(!root) return;
    int newPathMask = pathMask ^ (1 << root->val);
    if(!root->left && !root->right)
    {
        int isValidPath = (newPathMask == 0) || 
            ((newPathMask & (newPathMask-1)) == 0);
        totalPaths += isValidPath;
        return;
    }

    pseudoPalindromicPathsDFS(newPathMask, root->left);
    pseudoPalindromicPathsDFS(newPathMask, root->right);
}

int pseudoPalindromicPaths(TreeNode* root)
{
    pseudoPalindromicPathsDFS(0, root);
    return totalPaths;
}

// DAY 25 (1143. Longest Common Subsequence)=================================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n)

int longestCommonSubsequence(string text1, string text2)
{
    int size1 = text1.size();
    int size2 = text2.size();

    vector<int> maxLenDP(size2, 0);

    for(int idx1 = size1-1; idx1 >= 0; idx1--)
    {
        vector<int> prevDP = maxLenDP;
        for(int idx2 = size2-1; idx2 >= 0; idx2--)
        {
            int inc1 = size1-idx1-1? prevDP[idx2] : 0;
            int inc2 = size2-idx2-1? maxLenDP[idx2+1] : 0;
            int inc12 = size1-idx1-1 && size2-idx2-1?
                    prevDP[idx2+1] : 0;
            maxLenDP[idx2] = text1[idx1] == text2[idx2]?
                    (inc12 + 1) : max(inc1, inc2);
        }
    }

    return maxLenDP[0];
}

// DAY 26 (576. Out of Boundary Paths)=====================================================================

// Time Complexity = O(n * m * maxMoves)
// Space Complexity = O(n * m * maxMoves)

int MOD = 1e9 + 7;
int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
int findPathsDFS(int currRow, int currCol, int remMoves, int n, int m, vector<vector<vector<int>>> &stateCache)
{
    if(currRow == -1 || currCol == -1 || currRow == n || currCol == m)
        return 1;
    if(remMoves == 0)
        return 0;
    if(stateCache[currRow][currCol][remMoves] != -1)
        return stateCache[currRow][currCol][remMoves];

    int currAns = 0;
    for(int d = 0; d < 4; d++)
        currAns = (currAns % MOD + 
            findPathsDFS(currRow + dir[d][0], currCol+dir[d][1], remMoves-1, n, m, stateCache) % MOD) % MOD;

    return stateCache[currRow][currCol][remMoves] = currAns;
}

int findPaths(int n, int m, int maxMove, int startRow, int startColumn)
{
    vector<vector<vector<int>>> stateCache(n, vector<vector<int>>(m, vector<int>(maxMove+1, -1)));
    return findPathsDFS(startRow, startColumn, maxMove, n, m, stateCache);
}

// DAY 27 (629. K Inverse Pairs Array)=========================================================================================

// APPROACH 1 (Tabulated DP: Traversing at every previous state from 0 to min(n-1, k))

// Time Complexity = O(n * k * min(n, k))
// Space Complexity = O(n * k)

const int MOD = 1e9 + 7;
int kInversePairsDFS(int N, int K, vector<vector<int>> &stateCache)
{
    stateCache[0][0] = 1;
    for(int n = 1; n <= N; n++)
    {
        for(int k = 0; k <= K; k++)
        {
            if(k == 0)
            {
                stateCache[n][k] = 1;
                continue;
            }
            int totalWays = 0;
            stateCache[n][k] = (((stateCache[n][k-1] % MOD
                + stateCache[n-1][k] % MOD) % MOD) + MOD
                - (k-n >= 0? stateCache[n-1][k-n] : 0)) % MOD;
        }
    }
    return stateCache[N][K];
}

int kInversePairs(int n, int k) 
{
    vector<vector<int>> stateCache(n+1, vector<int>(k+1, 0));
    return kInversePairsDFS(n, k, stateCache);
}

// APPROACH 2 (Sliding window + DP: Took sum of last k numbers instead of traversing again and again)

// Time Complexity = O(n * k)
// Space Complexity = O(k)

const int MOD = 1e9 + 7;
int kInversePairsDFS(int N, int K, vector<int> &stateCache)
{
    stateCache[0] = 1;
    for(int n = 1; n <= N; n++)
    {
        vector<int> prevStateCache = stateCache;
        for(int k = 1; k <= K; k++)
            stateCache[k] = (((stateCache[k-1] % MOD
                + prevStateCache[k] % MOD) % MOD) + MOD
                - (k-n >= 0? prevStateCache[k-n] : 0)) % MOD;
    }
    return stateCache[K];
}

int kInversePairs(int n, int k) 
{
    vector<int> stateCache(k+1, 0);
    return kInversePairsDFS(n, k, stateCache);
}

// DAY 28 (1074. Number of Submatrices That Sum to Target)===============================================================================

// Time Complexity = O(n * n * m)
// Space Complexity = O(1)

int numSubmatrixSumTarget(vector<vector<int>> &matrix, int target)
{
    int rows = matrix.size(), cols = matrix[0].size();
    int totalCount = 0;
    for(int row = 1; row < rows; row++)
        for(int col = 0; col < cols; col++)
            matrix[row][col] += matrix[row-1][col];

    for(int border = 0; border < rows; border++)
    {
        for(int row = border; row < rows; row++)
        {
            unordered_map<int,int> sums;
            sums[0] = 1;
            int currSum = 0;
            for(int col = 0; col < cols; col++)
            {
                currSum += matrix[row][col] - (border? matrix[border-1][col] : 0);
                totalCount += sums[currSum - target];
                sums[currSum]++;
            }
        }
    }

    return totalCount;
}
