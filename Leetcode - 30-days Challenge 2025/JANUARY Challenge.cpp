
// DAY 1 (1422. Maximum Score After Splitting a String)=====================================================

// Time Complexcity = O(n)
// Space Complexcity = O(1)

int maxScore(string s) {
    int totalOnes = 0;
    for(char c : s) {
        totalOnes += c - '0';
    }

    s.pop_back();
    int maxScore = 0;
    int leftZeros = 0;
    int rightOnes = totalOnes;
    for(char c : s) {
        leftZeros += c == '0';
        rightOnes -= c == '1';
        maxScore = max(maxScore, leftZeros + rightOnes);
    }

    return maxScore;
}

// DAY 2 (2559. Count Vowel Strings in Ranges)=================================================================

// Time Complexity = O(n + q)
// Space Complexity = O(n + q)

bool isVowel(char c) {
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
        return true;
    }
    return false;
}

vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
    int wsize = words.size();
    int qsize = queries.size();
    vector<int> prefCount(wsize, 0);
    vector<int> ans(qsize);
    for(int idx = 0; idx < wsize; idx++) {
        prefCount[idx] = (isVowel(words[idx][0]) && isVowel(words[idx].back())) + (idx? prefCount[idx-1] : 0);
    }

    for(int idx = 0; idx < qsize; idx++) {
        int left = queries[idx][0];
        int right = queries[idx][1];
        ans[idx] = prefCount[right] - (left? prefCount[left-1] : 0);
    }

    return ans;
}

// DAY 3 (2270. Number of Ways to Split Array)==============================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int waysToSplitArray(vector<int>& nums) {
    int size = nums.size();
    vector<long long> prefixSum(size, 0);
    for(int idx = 0; idx < size; idx++) {
        prefixSum[idx] = (idx? prefixSum[idx-1] : 0) + nums[idx];
    }
    long long postfixSum = 0, totalSplits = 0;
    for(int idx = size-1; idx >= 1; idx--) {
        postfixSum += nums[idx];
        if(postfixSum <= prefixSum[idx-1]) {
            totalSplits++;
        }
    }

    return totalSplits;
}

// DAY 4 (1930. Unique Length-3 Palindromic Subsequences)==========================================================

// Time Complexity = O(n + 26*26)
// Space Complexity = O(n*26)

int getTotalUniqueCharactersBetween(int start, int end, vector<vector<int>> &arr) {
    int uniqueChars = 0;
    for(int idx = 0; idx < 26; idx++) {
        uniqueChars += (arr[end - 1][idx] - arr[start][idx]) > 0;
    }
    return uniqueChars;
}

int countPalindromicSubsequence(string s) {
    int size = s.size();
    vector<vector<int>> firstLastPos(26, vector<int>(2, -1));
    vector<int> charMap(26, 0);
    vector<vector<int>> prefixUniqueCount(size, vector<int>(26, 0));
    int totalCount = 0;
    for(int idx = 0; idx < size; idx++) {
        if(firstLastPos[s[idx]-'a'][0] == -1) {
            firstLastPos[s[idx]-'a'][0] = idx;
        }
        else {
            firstLastPos[s[idx]-'a'][1] = idx;
        }
        ++charMap[s[idx]-'a'];
        prefixUniqueCount[idx] = charMap;
    }

    for(vector<int> &pair : firstLastPos) {
        int firstPos = pair[0];
        int lastPos = pair[1];
        if(lastPos != -1) {
            totalCount += getTotalUniqueCharactersBetween(firstPos, lastPos, prefixUniqueCount);
        }
    }

    return totalCount;
}

// DAY 5 (2381. Shifting Letters II)=================================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(n)

string shiftingLetters(string s, vector<vector<int>>& shifts) {
    int size = s.size();
    vector<int> netShift(size+1, 0);
    for(vector<int> &shift : shifts) {
        int start = shift[0];
        int end = shift[1];
        int dir = shift[2]? 1 : -1;
        netShift[start] += dir;
        netShift[end+1] += -1 * dir;
    }
    for(int idx = 0; idx < size; idx++) {
        netShift[idx] += idx? netShift[idx-1] : 0;
        netShift[idx] = (netShift[idx] % 26 + 26) % 26;

        s[idx] = char((((s[idx] - 'a') + netShift[idx]) % 26) + 'a');
    }

    return s;
}

// DAY 6 (1769. Minimum Number of Operations to Move All Balls to Each Box)====================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> minOperations(string boxes) {
    int size = boxes.size();
    int leftOnes = 0, leftJumps = 0, rightOnes = 0, rightJumps = 0;
    vector<int> answer(size, 0);
    for(int left = 0, right = size-1; left < size; left++, right--) {
        answer[left] += leftJumps;
        answer[right] += rightJumps;

        leftOnes += boxes[left] == '1';
        rightOnes += boxes[right] == '1';

        leftJumps += leftOnes;
        rightJumps += rightOnes;
    }

    return answer;
}

// DAY 7 (1408. String Matching in an Array)========================================================================

// Time Complexity = O()
// Space Complexity = O(n^2*m^2)

bool isSubstring(string &word1, string &word2) {
    if(word2.size() <= word1.size()) {
        return false;
    }

    for(int idx = 0; idx <= word2.size()-word1.size(); idx++) {
        if(word1 == word2.substr(idx, word1.size())) {
            return true;
        }
    }

    return false;
}

vector<string> stringMatching(vector<string>& words) {
    int size = words.size();
    vector<string> ans;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = 0; idx2 < size; idx2++) {
            if(isSubstring(words[idx1], words[idx2])) {
                ans.push_back(words[idx1]);
                break;
            }
        }
    }
    return ans;
}

// DAY 8 (3042. Count Prefix and Suffix Pairs I)==============================================================

// Time Complexity = O(n^2 * m1)
// Space Complexity = O(1)

bool isPrefixAndSuffix(string &word1, string &word2) {
    int size1 = word1.size(), size2 = word2.size();
    if(size2 < size1) {
        return false;
    }
    return word1 == word2.substr(0, size1) && word1 == word2.substr(size2-size1);
}

int countPrefixSuffixPairs(vector<string>& words) {
    int size = words.size();
    int pairs = 0;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1+1; idx2 < size; idx2++) {
            if(isPrefixAndSuffix(words[idx1], words[idx2])) {
                pairs++;
            }
        }
    }
    return pairs;
}

// DAY 9 (2185. Counting Words With a Given Prefix)===========================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

int prefixCount(vector<string>& words, string pref) {
    int totalWords = 0;
    for(string word : words) {
        totalWords += word.size() >= pref.size() && word.substr(0, pref.size()) == pref;
    }
    return totalWords;
}

// DAY 10 (916. Word Subsets)================================================================================

// Time Complexity = O(n*m*26)
// Space Complexity = O(26)

vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
    vector<string> ans;
    vector<int> freqMap2(26, 0);
    for(string word : words2) {
        vector<int> tempFreq(26, 0);
        for(char c : word) {
            freqMap2[c-'a'] = max(freqMap2[c-'a'], ++tempFreq[c-'a']);
        }
    }
    for(string word : words1) {
        vector<int> freqMap1(26, 0);
        bool isUniversal = true;
        for(char c : word) {
            freqMap1[c-'a']++;
        }
        for(int c = 0; c < 26; c++) {
            if(freqMap1[c] < freqMap2[c]) {
                isUniversal = false;
                break;
            }
        }
        if(isUniversal) {
            ans.push_back(word);
        }
    }
    return ans;
}

// DAY 11 (1400. Construct K Palindrome Strings)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool canConstruct(string s, int k) {
    int size = s.size();
    if(size < k) {
        return false;
    }
    int freqMask = 0;
    for(char c : s) {
        freqMask ^= (1 << (c-'a'));
    }

    int oddChars = __builtin_popcount(freqMask);
    if(oddChars > k) {
        return false;
    }
    return true;
}

// DAY 12 (2116. Check if a Parentheses String Can Be Valid)=====================================================================

// Time Complexioty = O(n)
// Space Complexioty = O(1)

bool canBeValid(string s, string locked) {
    if(s.size() & 1) {
        return false;
    }
    int open = 0, close = 0;
    for(int idx = 0; idx < s.size(); idx++) {
        if(locked[idx] == '0' || s[idx] == '(') {
            open++;
        }
        else if(open) {
            open--;
        }
        else {
            return false;
        }
    }
    for(int idx = s.size()-1; idx >= 0; idx--) {
        if(locked[idx] == '0' || s[idx] == ')') {
            close++;
        }
        else if(close) {
            close--;
        }
        else {
            return false;
        }
    }

    return true;
}

// DAY 13 (3223. Minimum Length of String After Operations)===================================================================================

// Time Complexity = O(n + 26)
// Space Complexity = O(26)

int minimumLength(string s) {
    vector<int> freq(26, 0);
    int minLen = 0;
    for(char c : s) {
        freq[c-'a']++;
    }

    for(int c = 0; c < 26; c++) {
        minLen += freq[c] == 0? 0 : ((freq[c] & 1)? 1 : 2);
    }

    return minLen;
}

// DAY 15 (2657. Find the Prefix Common Array of Two Arrays)=============================================================================

// Time Complexity = O(n*logx)
// Space Complexity = O(n)

int countSetBits(long long mask) {
    int setBits = 0;
    while(mask) {
        mask &= mask - 1;
        setBits++;
    }
    return setBits;
}

vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
    unsigned long long maska = 0, maskb = 0;
    vector<int> perfixCommonArr(A.size());
    for(int idx = 0; idx < A.size(); idx++) {
        maska |= (1ull << A[idx]);
        maskb |= (1ull << B[idx]);
        unsigned long long commonMask = maska & maskb;
        int commonCount = countSetBits(commonMask);
        perfixCommonArr[idx] = commonCount;
    }
    return perfixCommonArr;
}

// DAY 15 (2429. Minimize XOR)==============================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

int minimizeXor(int num1, int num2) {
    int setBitsIn2 = __builtin_popcount(num2);
    int x = 0;
    for(int bit = 31; bit >= 0 && setBitsIn2; bit--) {
        if(num1 & (1 << bit)) {
            x ^= (1 << bit);
            setBitsIn2--;
        }
    }
    for(int bit = 0; bit < 32 && setBitsIn2; bit++) {
        if(!(x & (1 << bit))) {
            x |= (1 << bit);
            setBitsIn2--;
        }
    }
    return x;
}

// DAY 16 (2425. Bitwise XOR of All Pairings)=================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int findAllXor(vector<int> &nums) {
    int xorAns = 0;
    for(int num : nums) {
        xorAns ^= num;
    }
    return xorAns;
}

int xorAllNums(vector<int>& nums1, vector<int>& nums2) {
    int size1 = nums1.size(), size2 = nums2.size();
    int xor1 = findAllXor(nums1);
    int xor2 = findAllXor(nums2);

    if((size1 & 1) && (size2 & 1)) {
        return xor1 ^ xor2;
    }
    if(size1 & 1) {
        return xor2;
    }
    if(size2 & 1) {
        return xor1;
    }
    return 0;
}

// DAY 17 (2683. Neighboring Bitwise XOR)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool doesValidArrayExist(vector<int>& derived) {
    int currNum = 0;
    for(int idx = 0; idx < derived.size(); idx++) {
        currNum ^= derived[idx];
    }
    return currNum == 0;
}

// DAY 18 (1368. Minimum Cost to Make at Least One Valid Path in a Grid)=======================================================================

// Time Complexity = O(n*m * log(n*m))
// Space Complexity = O(n*m)

int minCost(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minPq;
    vector<vector<int>> minCost(rows, vector<int>(cols, rows*cols));
    int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
    minPq.push({0, 0, 0});
    minCost[0][0] = 0;

    while(!minPq.empty()) {
        int row = minPq.top()[0];
        int col = minPq.top()[1];
        int costsf = minPq.top()[2];
        minPq.pop();

        if(row == rows-1 && col == cols-1) {
            return costsf;
        }

        for(int d = 0; d < 4; d++) {
            int nrow = row + dir[d][0];
            int ncol = col + dir[d][1];
            int ncost = costsf + (grid[row][col] != (d+1));

            if(nrow == -1 || ncol == -1 || nrow == rows || ncol == cols || minCost[nrow][ncol] <= ncost) {
                continue;
            }

            minPq.push({nrow, ncol, ncost});
            minCost[nrow][ncol] = ncost;
        }
    }
    return -1;
}

// DAY 19 (407. Trapping Rain Water II)==============================================================================

// Time Complexity = O(n*m log(n*m))
// Space Complexity = O(n*m)

int trapRainWater(vector<vector<int>>& heightMap) {
    int rows = heightMap.size(), cols = heightMap[0].size();
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minPq;
    vector<vector<bool>> isVis(rows, vector<bool>(cols, false));
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int waterTrapped = 0;

    for(int row = 0; row < rows; row++) {
        minPq.push({heightMap[row][0], row, 0});
        minPq.push({heightMap[row][cols-1], row, cols-1});
        isVis[row][0] = true;
        isVis[row][cols-1] = true;
    }
    for(int col = 0; col < cols; col++) {
        minPq.push({heightMap[0][col], 0, col});
        minPq.push({heightMap[rows-1][col], rows-1, col});
        isVis[0][col] = true;
        isVis[rows-1][col] = true;
    }

    while(!minPq.empty()) {
        int currHeight = minPq.top()[0];
        int currRow = minPq.top()[1];
        int currCol = minPq.top()[2];
        minPq.pop();

        for(int d = 0; d < 4; d++) {
            int nextRow = currRow + dir[d][0];
            int nextCol = currCol + dir[d][1];
            if(nextRow == -1 || nextRow == rows || nextCol == -1 || nextCol == cols || isVis[nextRow][nextCol]) {
                continue;
            }

            int nextHeight = heightMap[nextRow][nextCol];
            if(nextHeight < currHeight) {
                waterTrapped += currHeight - nextHeight;
                nextHeight = currHeight;
            }
            minPq.push({nextHeight, nextRow, nextCol});
            isVis[nextRow][nextCol] = true;
        }
    }

    return waterTrapped;
}

// DAY 20 (2661. First Completely Painted Row or Column)=================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
    int rows = mat.size(), cols = mat[0].size();
    vector<int> rowCount(cols, 0);
    vector<int> colCount(rows, 0);
    vector<pair<int,int>> numPos(rows*cols+1, {-1, -1});
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            numPos[mat[row][col]] = {row, col};
        }
    }

    for(int i = 0; i < arr.size(); i++) {
        int row = numPos[arr[i]].first;
        int col = numPos[arr[i]].second;

        if(++rowCount[col] == rows || ++colCount[row] == cols) {
            return i;
        }
    }

    return -1;
}

// DAY 23 (1267. Count Servers that Communicate)==============================================================================

// Time Complexity = O(n * m * (n + m))
// Space Complexity = O(n * m)

int countServersDFS(int startRow, int startCol, int rows, int cols, vector<vector<int>> &grid, vector<vector<bool>> &vis) {
    int connections = 0;
    vis[startRow][startCol] = true;
    for(int row = 0; row < rows; row++) {
        if(grid[row][startCol] && !vis[row][startCol]) {
            connections += countServersDFS(row, startCol, rows, cols, grid, vis);
        }
    }
    for(int col = 0; col < cols; col++) {
        if(grid[startRow][col] && !vis[startRow][col]) {
            connections += countServersDFS(startRow, col, rows, cols, grid, vis);
        }
    }

    return connections + 1;
}

int countServers(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<bool>> vis(rows, vector<bool>(cols, false));
    int connections = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            if(grid[row][col] && !vis[row][col]) {
                int servers = countServersDFS(row, col, rows, cols, grid, vis);
                connections += servers > 1? servers : 0;
            }
        }
    }
    return connections;
}

// DAY 24 (802. Find Eventual Safe States)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool eventualSafeNodesDFS(int node, vector<bool> &isVis, vector<bool> &isSafe, vector<vector<int>> &graph) {
    if(isSafe[node]) {
        return true;
    }
    if(isVis[node]) {
        return false;
    }
    isVis[node] = true;

    bool safeFlag = true;
    for(int nextNode : graph[node]) {
        safeFlag &= eventualSafeNodesDFS(nextNode, isVis, isSafe, graph);
    }
    if(safeFlag) {
        isSafe[node] = true;
        return true;
    }
    return false;
}

vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
    int nodes = graph.size();
    vector<bool> isVis(nodes, false), isSafe(nodes, false);
    vector<int> safeNodes;
    for(int node = 0; node < nodes; node++) {
        if(!isVis[node]) {
            eventualSafeNodesDFS(node, isVis, isSafe, graph);
        }
    }
    for(int node = 0; node < nodes; node++) {
        if(isSafe[node]) {
            safeNodes.push_back(node);
        }
    }
    return safeNodes;
}

// DAY 25 (2948. Make Lexicographically Smallest Array by Swapping Elements)=================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
    int size = nums.size();
    vector<int> res(size);
    vector<pair<int,int>> numIdx(size);
    for(int idx = 0; idx < size; idx++) {
        numIdx[idx] = {nums[idx], idx};
    }
    sort(numIdx.begin(), numIdx.end());

    for(int idx = 0; idx < size; ) {
        int tempIdx = idx;
        vector<int> sortedIdx;
        sortedIdx.push_back(numIdx[tempIdx++].second);
        while(tempIdx < size && numIdx[tempIdx].first - numIdx[tempIdx-1].first <= limit) {
            sortedIdx.push_back(numIdx[tempIdx++].second);
        }
        sort(sortedIdx.begin(), sortedIdx.end());
        for(int itr = 0; itr < sortedIdx.size(); itr++) {
            res[sortedIdx[itr]] = numIdx[idx + itr].first;
        }
        
        idx = tempIdx;
    }

    return res;
}

// DAY 26 (2127. Maximum Employees to Be Invited to a Meeting)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getChainLen(int node, vector<vector<int>> &graph, vector<bool> &isVis) {
    isVis[node] = true;
    int len = 0;
    for(int nextNode : graph[node]) {
        len = max(len, getChainLen(nextNode, graph, isVis));
    }
    return len + 1;
}

int getTotalChainLen(int n, vector<int> &favorite, vector<bool> &isVis) {
    vector<vector<int>> favoriteRev(n);
    int totalChainLen = 0;
    for(int node = 0; node < n; node++) {
        if(favorite[favorite[node]] != node) {
            favoriteRev[favorite[node]].push_back(node);
        }
    }
    
    for(int node = 0; node < n; node++) {
        if(isVis[node]) {
            continue;
        }
        if(favorite[favorite[node]] == node) {
            isVis[node] = true;
            isVis[favorite[node]] = true;
            int chainLenWithNode1 = getChainLen(node, favoriteRev, isVis);
            int chainLenWithNode2 = getChainLen(favorite[node], favoriteRev, isVis);
            totalChainLen += chainLenWithNode1 + chainLenWithNode2;
        }
    }

    return totalChainLen;
}

int getMaxCycleLen(int n, vector<int> &favorite, vector<bool> &isVis) {
    vector<pair<int,int>> tailLen(n, {-1, -1}); // {length, discoveryTime}
    int maxCycleLen = 0, discoveryTime = 0;
    for(int node = 0; node < n; node++) {
        if(isVis[node]) {
            continue;
        }
        int cycleLen = 0, tempNode = node;
        while(tailLen[tempNode].first == -1) {
            tailLen[tempNode].first = cycleLen++;
            tailLen[tempNode].second = discoveryTime;
            isVis[tempNode] = true;
            tempNode = favorite[tempNode];
        }
        cycleLen -= tailLen[tempNode].second == discoveryTime? tailLen[tempNode].first : cycleLen;
        discoveryTime++;
        maxCycleLen = max(maxCycleLen, cycleLen);
    }
    return maxCycleLen;
}

int maximumInvitations(vector<int>& favorite) {
    int n = favorite.size();
    vector<bool> isVis(n, false);
    int totalChainLen = getTotalChainLen(n, favorite, isVis);
    int maxCycleLen = getMaxCycleLen(n, favorite, isVis);

    return max(totalChainLen, maxCycleLen);
}

// DAY 27 (1462. Course Schedule IV)===========================================================================

// Time Complexity = O(n^3 + q)
// Space Complexity = O(n^2 + q)

void reachReachables(int parentCourse, int course, vector<vector<int>> &graph, vector<vector<bool>> &isReachable) {
    if(isReachable[parentCourse][course]) {
        return;
    }
    isReachable[parentCourse][course] = true;
    for(int nextCourse : graph[course]) {
        reachReachables(parentCourse, nextCourse, graph, isReachable);
    }
}

vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries) {
    vector<vector<bool>> isReachable(numCourses, vector<bool>(numCourses, false));
    vector<vector<int>> graph(numCourses);
    vector<bool> ans;
    for(vector<int> &prerequisite : prerequisites) {
        graph[prerequisite[1]].push_back(prerequisite[0]);
    }
    for(int course = 0; course < numCourses; course++) {
        reachReachables(course, course, graph, isReachable);
    }

    for(vector<int> &query : queries) {
        ans.push_back(isReachable[query[1]][query[0]]);
    }

    return ans;
}

// DAY 28 (2658. Maximum Number of Fish in a Grid)======================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(1)

int catchAllFishes(int row, int col, int rows, int cols, vector<vector<int>> &grid) {
    if(row == -1 || col == -1 || row == rows || col == cols || grid[row][col] == 0) {
        return 0;
    }
    int fishes = grid[row][col];
    grid[row][col] = 0;

    return fishes + catchAllFishes(row + 1, col, rows, cols, grid)
        + catchAllFishes(row, col + 1, rows, cols, grid)
        + catchAllFishes(row - 1, col, rows, cols, grid)
        + catchAllFishes(row, col - 1, rows, cols, grid);
}

int findMaxFish(vector<vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    int maxFishes = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            maxFishes = max(maxFishes, catchAllFishes(row, col, rows, cols, grid));
        }
    }
    return maxFishes;
}

// DAY 29 (684. Redundant Connection)===================================================================================

// Time Complexity = O(E)
// Space Complexity = O(E)

class DSU {
    public:
    int size;
    vector<int> parSize, par;
    DSU(int size) {
        this->size = size;
        parSize.assign(size, 1);
        par.resize(size);
        for(int node = 0; node < size; node++) {
            par[node] = node;
        }
    }
    int findPar(int node) {
        return par[node] = (par[node] == node)? node : findPar(par[node]);
    }

    bool canMergeThenMergeNodes(int node1, int node2) {
        int par1 = findPar(node1);
        int par2 = findPar(node2);
        if(par1 == par2) {
            return false;
        }

        if(parSize[par2] >= parSize[par1]) {
            swap(par1, par2);
        }
        parSize[par1] += parSize[par2];
        par[par2] = par1;

        return true;
    }
};

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int totalEdges = edges.size();
    DSU dsu(totalEdges+1);
    for(vector<int> &edge : edges) {
        if(!dsu.canMergeThenMergeNodes(edge[0], edge[1])) {
            return edge;
        }
    }
    return {-1, -1};
}

// DAY 30 (2493. Divide Nodes Into the Maximum Number of Groups)============================================================================

// Time Complexity = O(V * (V+E))
// Space Complexity = O(V + E)

bool isBipartite(int src, int currColor, vector<int> &color, vector<vector<int>> &graph) {
    if(color[src] != -1) {
        return color[src] == currColor;
    }
    color[src] = currColor;
    for(int dest : graph[src]) {
        if(!isBipartite(dest, currColor ^ 1, color, graph)) {
            return false;
        }
    }
    return true;
}

int getMaximumDepthWithNode(int node, int n, vector<vector<int>> &graph) {
    queue<int> que;
    vector<bool> isVisited(n, false);
    int depth = 0;
    que.push(node);
    isVisited[node] = true;
    while(!que.empty()) {
        int size = que.size();
        while(size--) {
            int src = que.front();
            que.pop();

            for(int dest : graph[src]) {
                if(!isVisited[dest]) {
                    isVisited[dest] = true;
                    que.push(dest);
                }
            }
        }
        depth++;
    }
    return depth;
}

int getMaximumGroupsWithComponent(int src, vector<bool> &isVisited, vector<int> &depth, vector<vector<int>> &graph) {
    int maxGroups = depth[src];
    isVisited[src] = true;
    for(int dest : graph[src]) {
        if(!isVisited[dest]) {
            maxGroups = max(maxGroups, getMaximumGroupsWithComponent(dest, isVisited, depth, graph));
        }
    }
    return maxGroups;
}

int magnificentSets(int n, vector<vector<int>>& edges) {
    vector<vector<int>> graph(n);
    vector<int> color(n, -1), depth(n, 0);
    vector<bool> isVisited(n, false);
    int maxGroups = 0;
    for(vector<int> &edge : edges) {
        graph[edge[0]-1].push_back(edge[1]-1);
        graph[edge[1]-1].push_back(edge[0]-1);
    }

    for(int node = 0; node < n; node++) {
        if(color[node] != -1) {
            continue;
        }
        if(!isBipartite(node, 0, color, graph)) {
            return -1;
        }
    }

    for(int node = 0; node < n; node++) {
        depth[node] = getMaximumDepthWithNode(node, n, graph);
    }

    for(int node = 0; node < n; node++) {
        if(isVisited[node]) {
            continue;
        }
        maxGroups += getMaximumGroupsWithComponent(node, isVisited, depth, graph);
    }

    return maxGroups;
}
