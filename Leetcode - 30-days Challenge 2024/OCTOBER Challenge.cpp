// DAY 1 (1497. Check If Array Pairs Are Divisible by k)====================================================================

// Time Complexity = O(n + k)
// Space Complexity = O(k)

bool canArrange(vector<int>& arr, int k)
{
    vector<int> divs(k, 0);
    for(int num : arr)
        divs[((num % k) + k) % k]++;
    if(divs[0] & 1)
        return false;
    for(int i = 1; i < k; i++)
        if(divs[i] != divs[k - i])
            return false;
    return true;
}

// DAY 2 (1331. Rank Transform of an Array)===========================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<int> arrayRankTransform(vector<int>& arr)
{
    int size = arr.size();
    vector<pair<int,int>> arrIdx(size);
    vector<int> rank(size);
    int currRank = 1;
    for(int idx = 0; idx < size; idx++)
        arrIdx[idx] = {arr[idx], idx};
    sort(arrIdx.begin(), arrIdx.end());

    for(int idx = 0; idx < size; idx++)
        rank[arrIdx[idx].second] = idx && arrIdx[idx].first == arrIdx[idx-1].first? rank[arrIdx[idx-1].second] : currRank++;
    
    return rank;
}

// DAY 3 (1590. Make Sum Divisible by P)===========================================================

// Time Complexity = O(n)
// Space Complexity = O(min(n, k))

int minSubarray(vector<int>& nums, int p)
{
    long totalSum = accumulate(nums.begin(), nums.end(), 0l);
    long currSum = 0;
    int extra = totalSum % p;
    if(extra == 0)
        return 0;
    unordered_map<int,int> lastIdx;
    int minLen = nums.size();
    lastIdx[0] = -1;
    for(int idx = 0; idx < nums.size(); idx++)
    {
        currSum += nums[idx];
        int currMod = currSum % p;
        int targetMod = (currMod - extra + p) % p;
        if(lastIdx.find(targetMod) != lastIdx.end())
            minLen = min(minLen, idx - lastIdx[targetMod]);
        lastIdx[currMod] = idx;
    }
    return minLen == nums.size()? -1 : minLen;
}

// DAY 4 (2491. Divide Players Into Teams of Equal Skill)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

long long dividePlayers(vector<int>& skill)
{
    int size = skill.size();
    int sum = accumulate(skill.begin(), skill.end(), 0);
    if((sum * 2) % size)
        return -1;
    int teamSkill = (sum * 2) / size;

    unordered_map<int,int> skillCnt;
    long long chemistrySum = 0;
    for(int skl : skill)
        skillCnt[skl]++;
    for(int skl : skill)
    {
        int sklPair = teamSkill - skl;
        if(skillCnt[skl]-- <= 0)
            continue;
        if(skillCnt[sklPair]-- <= 0)
            return -1;
        
        int chemistry = skl * sklPair;
        chemistrySum += chemistry;
    }
    return chemistrySum;
}

// DAY 5 (567. Permutation in String)========================================================================================

// Time Complexity = O(n + m*26)
// Space Complexity = O(1)

bool checkInclusion(string s1, string s2)
{
    int size1 = s1.size(), size2 = s2.size();
    vector<int> charMap1(26, 0), charMap2(26, 0);
    for(char c : s1)
        charMap1[c-'a']++;

    for(int idx = 0; idx < size2; idx++)
    {
        charMap2[s2[idx]-'a']++;
        if(idx - size1 >= 0)
            charMap2[s2[idx - size1]-'a']--;
        if(charMap2 == charMap1)
            return true;
    }

    return false;
}

// DAY 6 (1813. Sentence Similarity III)===================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

bool areSentencesSimilar(string sentence1, string sentence2)
{
    deque<string> senArr1, senArr2;
    stringstream ss1(sentence1), ss2(sentence2);
    string token;
    while(getline(ss1, token, ' '))
        senArr1.push_back(token);
    while(getline(ss2, token, ' '))
        senArr2.push_back(token);

    int size1 = senArr1.size(), size2 = senArr2.size();
    if(size2 > size1)
    {
        swap(size1, size2);
        swap(senArr1, senArr2);
    }

    int itr1 = 0, itr2 = 0;
    int gaps = 0, noneq = 0;
    while(!senArr2.empty())
    {
        if(senArr1.front() == senArr2.front()) {
            senArr1.pop_front();
            senArr2.pop_front();
        }
        else if(senArr1.back() == senArr2.back()) {
            senArr1.pop_back();
            senArr2.pop_back();
        }
        else return false;
    }
    return true;
}

// DAY 7 (2696. Minimum String Length After Removing Substrings)============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int minLength(string s) {
    stack<char> st;
    for(char c : s)
    {
        if(!st.empty() && ((c == 'B' && st.top() == 'A') || (c == 'D' && st.top() == 'C')))
            st.pop();
        else st.push(c);
    }
    return st.size();
}

// DAY 8 (1963. Minimum Number of Swaps to Make the String Balanced)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minSwaps(string s)
{
    int closingBrace = 0, incorrectPairs = 0;
    for(char c : s)
    {
        closingBrace += c == ']'? 1 : -1;
        incorrectPairs = max(incorrectPairs, closingBrace);
    }
    return (incorrectPairs + 1) >> 1;
}

// DAY 9 (921. Minimum Add to Make Parentheses Valid)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minAddToMakeValid(string s) {
    int openBrackets = 0, extraClosingBrackets = 0;
    for(char c : s) {
        if(c == '(')
            openBrackets++;
        else if(openBrackets) openBrackets--;
        else extraClosingBrackets++;
    }
    return openBrackets + extraClosingBrackets;
}

// DAY 10 (962. Maximum Width Ramp)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int maxWidthRamp(vector<int>& nums) {
    stack<int> numSt;
    int size = nums.size();
    int maxRamp = 0;
    for(int idx = 0; idx < size; idx++) {
        if(numSt.empty() || nums[idx] < nums[numSt.top()]) {
            numSt.push(idx);
        }
    }
    for(int idx = size-1; idx >= 0; idx--) {
        while(!numSt.empty() && nums[idx] >= nums[numSt.top()]) {
            maxRamp = max(maxRamp, idx - numSt.top());
            numSt.pop();
        }
    }

    return maxRamp;
}

// DAY 11 (1942. The Number of the Smallest Unoccupied Chair)========================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int smallestChair(vector<vector<int>>& times, int targetFriend) {
    int friends = times.size();
    vector<vector<int>> friendTimes(friends);
    for(int friend_ = 0; friend_ < friends; friend_++) {
        friendTimes[friend_] = {times[friend_][0], times[friend_][1], friend_};
    }
    sort(friendTimes.begin(), friendTimes.end());

    priority_queue<int, vector<int>, greater<int>> availableSeatsPq;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> endTimesPq;
    for(int seat = 0; seat < friends; seat++)
        availableSeatsPq.push(seat);

    for(int idx = 0; idx < friends; idx++) {
        while(!endTimesPq.empty() && endTimesPq.top().first <= friendTimes[idx][0]) {
                availableSeatsPq.push(endTimesPq.top().second);
                endTimesPq.pop();
        }
        endTimesPq.push({friendTimes[idx][1], availableSeatsPq.top()});
        if(friendTimes[idx][2] == targetFriend)
            return availableSeatsPq.top();
        availableSeatsPq.pop();
    }

    return friends;
}

// DAY 12 (2406. Divide Intervals Into Minimum Number of Groups)==============================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int minGroups(vector<vector<int>>& intervals) {
    priority_queue<int, vector<int>, greater<int>> minEndPq;
    int minGroups = 0;

    sort(intervals.begin(), intervals.end());
    for(vector<int> &interval : intervals) {
        int start = interval[0], end = interval[1];
        while(!minEndPq.empty() && minEndPq.top() < start) {
            minEndPq.pop();
        }
        minEndPq.push(end);

        minGroups = max(minGroups, (int) minEndPq.size());
    }

    return minGroups;
}

// DAY 14 (2530. Maximal Score After Applying K Operations)=================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

long long maxKelements(vector<int>& nums, int k) {
    priority_queue<int> maxPq;
    long long ans = 0;
    for(int num : nums)
        maxPq.push(num);
    while(k--) {
        int top = maxPq.top();
        maxPq.pop();
        int val = (top + 2) / 3;
        ans += top;
        maxPq.push(val);
    }
    return ans;
}

// DAY 15 (2938. Separate Black and White Balls)===========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long minimumSteps(string s) {
    long long steps = 0, lastOnes = 0;
    for(int idx = 0; idx < s.size(); idx++) {
        if(s[idx] == '0') {
            steps += lastOnes;
        } else {
            lastOnes++;
        }
    }
    return steps;
}

// DAY 16 (1405. Longest Happy String)=============================================================================

// Time Complexity = O(a + b + c)
// Space Complexity = O(1)

string longestDiverseString(int a, int b, int c) {
    string ans = "";
    priority_queue<pair<int,char>> maxPq;
    if(a) maxPq.push({a, 'a'});
    if(b) maxPq.push({b, 'b'});
    if(c) maxPq.push({c, 'c'});

    while(!maxPq.empty()) {
        int currFreq = maxPq.top().first;
        char currChar = maxPq.top().second;
        maxPq.pop();

        if(ans.size() >= 2 && currChar == ans[ans.size()-1] && currChar == ans[ans.size()-2]) {
            if(maxPq.empty()) break;

            int nextFreq = maxPq.top().first;
            char nextChar = maxPq.top().second;
            maxPq.pop();

            ans += nextChar;
            nextFreq--;

            if(nextFreq)
                maxPq.push({nextFreq, nextChar});
            maxPq.push({currFreq, currChar});
        }
        else {
            ans += currChar;
            currFreq--;
            if(currFreq)
                maxPq.push({currFreq, currChar});
        }
    }

    return ans;
}

// DAY 17 (670. Maximum Swap=========================================================================

// Time Complexity = O(nums.size()^2)
// Space Complexity = O(nums.size())

int maximumSwap(int num) {
    string numStr = to_string(num);
    for(int pos1 = 0; pos1 < numStr.size(); pos1++) {
        int maxNumPos = pos1;
        for(int pos2 = pos1+1; pos2 < numStr.size(); pos2++) {
            if((numStr[pos2] > numStr[maxNumPos]) || (numStr[pos2] == numStr[maxNumPos] && maxNumPos != pos1)) {
                maxNumPos = pos2;
            }
        }
        if(maxNumPos != pos1) {
            swap(numStr[pos1], numStr[maxNumPos]);
            break;
        }
    }
    return stoi(numStr);
}

// DAY 18 (2044. Count Number of Maximum Bitwise-OR Subsets)=================================================================

// Time Complexity = O(2^n * n)
// Space Complexity = O(1)

int countMaxOrSubsets(vector<int>& nums) {
    int maxOr = 0, ans = 0;
    for(int num : nums) {
        maxOr |= num;
    }
    
    for(int mask = 0; mask < (1 << nums.size()); mask++) {
        int currOr = 0;
        for(int idx = 0; idx < nums.size(); idx++) {
            if(mask & (1 << idx)) {
                currOr |= nums[idx];
            }
        }
        if(currOr == maxOr)
            ans++;
    }

    return ans;
}

// DAY 19 (1545. Find Kth Bit in Nth Binary String)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

char findKthBit(int n, int k) {
    if(n == 1) {
        return '0';
    }
    int len = (1 << n) - 1;
    if(k == len/2 + 1) {
        return '1';
    }
    return (k <= len/2)
        ? findKthBit(n-1, k)
        : (findKthBit(n-1, len - k + 1) == '0'? '1' : '0');
}

// DAY 21 (1593. Split a String Into the Max Number of Unique Substrings)=======================================================

// Time Complexity = O(2^n * n)
// Space Complexity = O(2^n * n)

int dfs(int i, string &s, string &curr, unordered_set<string> &vis) {
    if(i == s.size())
        return 0;
    
    int ans = 0;
    curr += s[i];
    if(!vis.count(curr)) {
        vis.insert(curr);
        string nxt = "";
        ans = max(ans, dfs(i+1, s, nxt, vis) + 1);
        vis.erase(curr);
    }
    ans = max(ans, dfs(i+1, s, curr, vis));

    return ans;
}

int maxUniqueSplit(string s) {
    unordered_set<string> vis;
    string curr = "";
    return dfs(0, s, curr, vis);
}

// DAY 22 (2583. Kth Largest Sum in a Binary Tree)===================================================================

// Time Complexiity = O(n*logn)
// Space Complexiity = O(n)

#define ll long long
long long kthLargestLevelSum(TreeNode* root, int k) {
    priority_queue<ll, vector<ll>, greater<ll>> minPq;
    queue<TreeNode*> que;
    que.push(root);

    while(!que.empty()) {
        int size = que.size();
        ll currSum = 0;
        while(size--) {
            TreeNode* node = que.front();
            currSum += node->val;
            que.pop();

            if(node->left) {
                que.push(node->left);
            }
            if(node->right) {
                que.push(node->right);
            }
        }

        minPq.push(currSum);
        if(minPq.size() > k) {
            minPq.pop();
        }
    }

    return minPq.size() < k? -1 : minPq.top();
}

// DAY 23 (2641. Cousins in Binary Tree II)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

TreeNode* replaceValueInTree(TreeNode* root) {
    queue<pair<TreeNode*, int>> que;
    que.push({root, root->val});
    int levelSum = root->val;
    while(!que.empty()) {
        int size = que.size();
        int nextLevelSum = 0;
        while(size--) {
            TreeNode* node = que.front().first;
            int sibblingSum = que.front().second;
            que.pop();
            node->val = levelSum - sibblingSum;

            int childrenSum = (node->left? node->left->val : 0) + (node->right? node->right->val : 0);

            if(node->left) {
                nextLevelSum += node->left->val;
                que.push({node->left, childrenSum});
            }
            if(node->right) {
                nextLevelSum += node->right->val;
                que.push({node->right, childrenSum});
            }
        }
        levelSum = nextLevelSum;
    }

    return root;
}

// DAY 24 (951. Flip Equivalent Binary Trees)=======================================================================

// APPROACH 1 (Sorting)

// Time Complexity = O(logn*n*logn)
// Space Complexity = O(n)

bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    queue<pair<TreeNode*, TreeNode*>> que1, que2;
    if(root1)
        que1.push({nullptr, root1});
    if(root2)
        que2.push({nullptr, root2});

    while(!que1.empty() || !que2.empty()) {
        int size1 = que1.size(), size2 = que2.size();
        vector<pair<int,int>> levelNodes1, levelNodes2;
        while(size1--) {
            TreeNode* nodePar = que1.front().first;
            TreeNode* node = que1.front().second;
            que1.pop();
            levelNodes1.push_back({nodePar? nodePar->val : -1, node->val});

            if(node->left)
                que1.push({node, node->left});
            if(node->right)
                que1.push({node, node->right});
        }
        while(size2--) {
            TreeNode* nodePar = que2.front().first;
            TreeNode* node = que2.front().second;
            que2.pop();
            levelNodes2.push_back({nodePar? nodePar->val : -1, node->val});

            if(node->left)
                que2.push({node, node->left});
            if(node->right)
                que2.push({node, node->right});
        }

        sort(levelNodes1.begin(), levelNodes1.end());
        sort(levelNodes2.begin(), levelNodes2.end());

        if(levelNodes1 != levelNodes2)
            return false;
    }
    return true;
}

// APPROACH 2 (Recursive - Checking with swap and no swap calls)

// Time Complexity = O(n)
// Space Complexity = O(n)

bool flipEquiv(TreeNode* root1, TreeNode* root2) {
    if(!root1 && !root2)
        return true;
    if(!root1 || !root2)
        return false;
    if(root1->val != root2->val)
        return false;

    bool noSwapRes = flipEquiv(root1->left, root2->left) && 
                    flipEquiv(root1->right, root2->right);
    bool swapRes = flipEquiv(root1->left, root2->right) && 
                    flipEquiv(root1->right, root2->left);

    return swapRes || noSwapRes;
}

// DAY 26 (2458. Height of Binary Tree After Subtree Removal Queries)=============================================================================

// Time Complexity = O(n + q)
// Space Complexity = O(n + q)

void findMaxHeights(TreeNode* node, int currHeight, int &maxHeightSf, unordered_map<int,int> &maxNewHeight, bool isL2R) {
    if(!node) return;

    maxNewHeight[node->val] = max(maxNewHeight[node->val], maxHeightSf);
    maxHeightSf = max(maxHeightSf, currHeight);

    TreeNode* newNode1 = isL2R? node->left : node->right;
    TreeNode* newNode2 = isL2R? node->right : node->left;
    findMaxHeights(newNode1, currHeight + 1, maxHeightSf, maxNewHeight, isL2R);
    findMaxHeights(newNode2, currHeight + 1, maxHeightSf, maxNewHeight, isL2R);
}

vector<int> treeQueries(TreeNode* root, vector<int>& queries) {
    unordered_map<int,int> maxNewHeight;
    int maxHeightSf = 0;
    vector<int> ans;
    findMaxHeights(root, 0, maxHeightSf, maxNewHeight, true);
    maxHeightSf = 0;
    findMaxHeights(root, 0, maxHeightSf, maxNewHeight, false);

    for(int removedRoot : queries) {
        ans.push_back(maxNewHeight[removedRoot]);
    }

    return ans;
}

// DAY 27 (1277. Count Square Submatrices with All Ones)============================================================================

// APPROACH 1 (Traversing through diagonals and finding submatrices of every size)

// Time Complexity = O(n^3)
// Space Complexity = O(1)

int countSquares(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            int upVal = row? matrix[row-1][col] : 0;
            int leftVal = col? matrix[row][col-1] : 0;
            int upLeftVal = row && col? matrix[row-1][col-1] : 0;
            matrix[row][col] += upVal + leftVal - upLeftVal;
        }
    }
    int ans = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            for(int diag = 0; row + diag < rows && col + diag < cols; diag++) {
                int topRightOnes = row? matrix[row - 1][col + diag] : 0;
                int bottomLeftOnes = col? matrix[row + diag][col - 1] : 0;
                int extraOnes = row && col? matrix[row - 1][col - 1] : 0;

                int totalOnes = matrix[row + diag][col + diag] - 
                    (topRightOnes + bottomLeftOnes - extraOnes);
                if(totalOnes == (diag+1) * (diag+1))
                    ans++;
                else break;
            }
        }
    }

    return ans;
}

// APPROACH 2 (DP)

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int countSquares(vector<vector<int>>& matrix) {
    int rows = matrix.size(), cols = matrix[0].size();
    vector<vector<int>> cache(rows, vector<int>(cols, 0));
    int ans = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(!matrix[row][col])
                continue;
            
            if(row == 0 || col == 0)
                cache[row][col] = 1;
            else cache[row][col] = min({cache[row - 1][col], 
                                        cache[row][col - 1], 
                                        cache[row - 1][col - 1]})
                                    + 1;
            ans += cache[row][col];
        }
    }
    return ans;
}

// DAY 28 (2501. Longest Square Streak in an Array)===================================================================================

// APPROACH 1 (Reverse Sorting and DP)

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int longestSquareStreak(vector<int>& nums) {
    sort(nums.rbegin(), nums.rend());
    unordered_map<int,int> seqLengthCache;
    int maxLen = -1;
    for(int num : nums) {
        long long numSquared = 1ll * num * num;
        if(seqLengthCache.count(numSquared)) {
            seqLengthCache[num] = seqLengthCache[numSquared] + 1;
            maxLen = max(maxLen, seqLengthCache[num]);
        }
        else seqLengthCache[num] = 1;
    }
    return maxLen;
}

// APPROACH 2 (By checking the sqrt)

// Time Complexity = O(M*sqrt(M))
// Space Complexity = O(M)

int longestSquareStreak(vector<int>& nums) {
    int maxNum = 0;
    int maxLen = 1;
    vector<int> seqLengthCache(1e5 + 5, 0);
    for(int num : nums) {
        maxNum = max(maxNum, num);
        seqLengthCache[num] = 1;
    }
    for(int num = 4; num <= maxNum; num++) {
        int numRoot = sqrt(num);
        if(seqLengthCache[num] && numRoot * numRoot == num) {
            seqLengthCache[num] = seqLengthCache[numRoot] + 1;
            maxLen = max(maxLen, seqLengthCache[num]);
        }
    }
    return maxLen == 1? -1 : maxLen;
}
