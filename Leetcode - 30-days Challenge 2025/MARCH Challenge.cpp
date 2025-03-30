
// DAY 1 (2460. Apply Operations to an Array)======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> applyOperations(vector<int>& nums) {
    int size = nums.size();
    for(int idx = 0, first0 = -1; idx < size; idx++) {
        if(nums[idx] == 0 && first0 == -1) {
            first0 = idx;
        }
        if(size-1-idx && nums[idx] && nums[idx] == nums[idx + 1]) {
            nums[idx] *= 2;
            nums[idx + 1] = 0;
        }
        if(nums[idx] && first0 != -1) {
            swap(nums[first0++], nums[idx]);
        }
    }
    return nums;
}

// DAY 2 (2570. Merge Two 2D Arrays by Summing Values)===============================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
    vector<vector<int>> ans;
    int size1 = nums1.size(), size2 = nums2.size();
    for(int idx1 = 0, idx2 = 0; idx1 < size1 || idx2 < size2; ) {
        if(idx1 == size1 || idx2 == size2) {
            if(idx1 == size1) {
                ans.push_back(nums2[idx2++]);
            }
            else {
                ans.push_back(nums1[idx1++]);
            }
        }
        else if(nums1[idx1][0] < nums2[idx2][0]) {
            ans.push_back(nums1[idx1++]);
        }
        else if(nums1[idx1][0] > nums2[idx2][0]) {
            ans.push_back(nums2[idx2++]);
        }
        else {
            ans.push_back({nums1[idx1][0], nums1[idx1++][1] + nums2[idx2++][1]});
        }
    }
    return ans;
}

// DAY 3 (2161. Partition Array According to Given Pivot)=========================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> pivotArray(vector<int>& nums, int pivot) {
    vector<int> smaller, greater;
    for(int num : nums) {
        if(num < pivot) {
            smaller.push_back(num);
        }
        else if(num > pivot) {
            greater.push_back(num);
        }
    }
    int equals = nums.size() - (smaller.size() + greater.size());
    int idx = 0;
    for(int num : smaller) {
        nums[idx++] = num;
    }
    while(equals--) {
        nums[idx++] = pivot;
    }
    for(int num : greater) {
        nums[idx++] = num;
    }
    
    return nums;
}

// DAY 4 (1780. Check if Number is a Sum of Powers of Three)=========================================================

// APPROACH 1 (Recursive)

// Time Complexity = O(2^log3(n)) = O(n)
// Space Complexity = O(log3(n))

bool checkPowersOfThreeDFS(int n, int prod) {
    if(n == 0) {
        return true;
    }
    if(prod > n) {
        return false;
    }
    
    bool includeProd = checkPowersOfThreeDFS(n - prod, prod * 3);
    bool excludeProd = checkPowersOfThreeDFS(n, prod * 3);

    return includeProd || excludeProd;
}

bool checkPowersOfThree(int n) {
    return checkPowersOfThreeDFS(n, 1);
}

// APPROACH 2 (Iterative)

// Time Complexity = O(log3(n))
// Space Complexity = O(1)

bool checkPowersOfThree(int n) {
    int prod = 1;
    while(prod * 3 <= n) {
        prod *= 3;
    }
    while(prod) {
        if(n / prod) {
            n -= prod;
        }
        if(n / prod) {
            return false;
        }
        prod /= 3;
    }
    return true;
}

// APPROACH 3 (Iterative - Ternary Representation) --> [OPTIMIZED]

// Time Complexity = O(log3(n))
// Space Complexity = O(1)

bool checkPowersOfThree(int n) {
    while(n) {
        if(n % 3 == 2) {
            return false;
        }
        n /= 3;
    }
    return true;
}

// DAY 5 (2579. Count Total Number of Colored Cells)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long coloredCells(int n) {
    long long totalCells = 1;
    while(--n) {
        totalCells += 4ll * n;
    }
    return totalCells;
}

// DAY 6 (2965. Find Missing and Repeated Values)=================================================================================

// Time Complexity = O(n*n)
// Space Complexity = O(1)

vector<int> findMissingAndRepeatedValues(vector<vector<int>>& grid) {
    int n = grid[0].size();
    long long total = n*n;
    long long sum = 0, sumSq = 0;
    for(int row = 0; row < n; row++) {
        for(int col = 0; col < n; col++) {
            sum += grid[row][col];
            sumSq += grid[row][col] * grid[row][col];
        }
    }
    long long sumDiff = sum - (total * (total + 1) / 2);
    long long sumSqDiff = sumSq - (total * (total + 1) * (2 * total + 1) / 6);
    int repeatedNum = ((sumSqDiff / sumDiff) + sumDiff) / 2;
    int missingNum = ((sumSqDiff / sumDiff) - sumDiff) / 2;
    return {repeatedNum, missingNum};
}

// DAY 7 (2523. Closest Prime Numbers in Range)==============================================================================

// Time Complexity = O(n * log(logn))
// Time Complexity = O(n)

vector<int> closestPrimes(int left, int right) {
    vector<bool> isPrime(right + 1, true);
    isPrime[0] = isPrime[1] = false;
    int tempNum1 = -1, tempNum2 = -1, num1 = -1, num2 = -1, minDiff = INT_MAX;
    for(int num = 2; num <= right; num++) {
        if(!isPrime[num]) {
            continue;
        }
        for(long long nextNum = 1ll * num * num; nextNum <= right; nextNum += num) {
            isPrime[nextNum] = false;
        }
    }

    for(int num = left; num <= right; num++) {
        if(!isPrime[num]) {
            continue;
        }
        if(tempNum1 == -1) {
            tempNum1 = num;
        }
        else if(tempNum2 == -1) {
            tempNum2 = num;
        }
        else {
            tempNum1 = tempNum2;
            tempNum2 = num;
        }
        if(tempNum1 != -1 && tempNum2 != -1) {
            if(tempNum2 - tempNum1 < minDiff) {
                num1 = tempNum1;
                num2 = tempNum2;
                minDiff = tempNum2 - tempNum1;
            }
        }
    }
    return {num1, num2};
}

// DAY 8 (2379. Minimum Recolors to Get K Consecutive Black Blocks)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumRecolors(string blocks, int k) {
    int currWhiteCount = 0, minOperations = k;
    for(int idx = 0; idx < blocks.size(); idx++) {
        currWhiteCount += blocks[idx] == 'W';
        if(idx >= k - 1) {
            if(idx >= k) {
                currWhiteCount -= blocks[idx - k] == 'W';
            }
            minOperations = min(minOperations, currWhiteCount);
        }
    }
    return minOperations;
}

// DAY 9 (3208. Alternating Groups II)================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfAlternatingGroups(vector<int>& colors, int k) {
    int size = colors.size(), groups = 0;
    for(int left = 0, right = 0; right < size + k - 1; right++) {
        if(right && colors[right % size] == colors[(right - 1) % size]) {
            left = right;
        }
        if(right - left + 1 >= k) {
            groups++;
        }
    }
    return groups;
}

// DAY 10 (1358. Number of Substrings Containing All Three Characters)====================================================

// APPROACH 1 (Storing the counts of a, b, c)

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfSubstrings(string s) {
    int size = s.size();
    int totalSubstrs = 0;
    vector<int> charCount(3, 0);
    for(int left = 0, right = 0; right < size; right++) {
        charCount[s[right]-'a']++;
        while(charCount[0] && charCount[1] && charCount[2]) {
            totalSubstrs += size - right;
            charCount[s[left++]-'a']--;
        }
    }
    return totalSubstrs;
}

// APPROACH 2 (Storing the next positions of a, b, c) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfSubstrings(string s) {
    int size = s.size();
    int totalSubstrs = 0;
    vector<int> nextPos(3, -1);
    for(int idx = 0; idx < size; idx++) {
        nextPos[s[idx]-'a'] = idx;
        if(nextPos[0] != -1 && nextPos[1] != -1 && nextPos[2] != -1) {
            totalSubstrs += min({nextPos[0], nextPos[1], nextPos[2]}) + 1;
        }
    }
    return totalSubstrs;
}

// DAY 12 (2529. Maximum Count of Positive Integer and Negative Integer)===================================================================

// Time Complexity = O(logn)
// Space Complexity = O(1)

int lowerBound(int num, vector<int> &nums) {
    int st = 0, end = nums.size();
    while(st < end) {
        int mid = st + ((end - st) >> 1);
        if(nums[mid] >= num) {
            end = mid;
        }
        else {
            st = mid + 1;
        }
    }
    return st;
}

int maximumCount(vector<int>& nums) {
    int posCount = lowerBound(0, nums);
    int negCount = nums.size() - lowerBound(1, nums);
    return max(posCount, negCount);
}

// DAY 13 (3356. Zero Array Transformation II)=============================================================================

// Time Complexity = O(q * log (n + q))
// Space Complexity = O(n)

bool canMakeZeroAt(int idx, vector<vector<int>>& queries, int size, vector<int>& nums) {
    vector<long> prefSum(size+1, 0);
    for(int itr = 0; itr <= idx; itr++) {
        prefSum[queries[itr][0]] += queries[itr][2];
        prefSum[queries[itr][1] + 1] -= queries[itr][2];
    }
    for(int itr = 0; itr < size; itr++) {
        prefSum[itr] += itr? prefSum[itr-1] : 0;
        if(nums[itr] - prefSum[itr] > 0) {
            return false;
        }
    }
    return true;
}

int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
    long totalSum = accumulate(nums.begin(), nums.end(), 0ll);
    if(totalSum == 0) {
        return 0;
    }
    int qsize = queries.size(), size = nums.size();
    int lo = 0, hi = queries.size();
    while(lo < hi) {
        int mid = lo + ((hi - lo) >> 1);
        if(canMakeZeroAt(mid, queries, size, nums)) {
            hi = mid;
        }
        else {
            lo = mid + 1;
        }
    }
    int totalQueries = lo + 1;
    return totalQueries == qsize + 1? -1 : totalQueries;
}

// DAY 15 (2560. House Robber IV)==================================================================================

// Time Complexity = O(n * log(MX))
// Time Complexity = O(1)

bool canSteal(int cap, int k, vector<int> &nums) {
    int lastStolen = -2, totalStolen = 0;
    for(int idx = 0; idx < nums.size(); idx++) {
        if(nums[idx] > cap) {
            continue;
        }
        if(idx - lastStolen != 1) {
            lastStolen = idx;
            if(++totalStolen >= k) {
                return true;
            }
        }
    }
    return false;
}

int minCapability(vector<int>& nums, int k) {
    int lo = *min_element(nums.begin(), nums.end());
    int hi = *max_element(nums.begin(), nums.end());
    while(lo < hi) {
        int cap = lo + ((hi - lo) >> 1);
        if(canSteal(cap, k, nums)) {
            hi = cap;
        }
        else {
            lo = cap + 1;
        }
    }
    return lo;
}

// DAY 16 (2594. Minimum Time to Repair Cars)=============================================================================

// Time Complexity = O(n * (log(MN) + log(cars)))
// Time Complexity = O(1)

#define ll long long

bool canRepairCars(ll time, int cars, vector<int> &ranks) {
    ll carsRepaired = 0;
    for(int rank : ranks) {
        carsRepaired += sqrt(time / rank);
    }
    return carsRepaired >= cars;
}

long long repairCars(vector<int>& ranks, int cars) {
    ll loTime = 1, hiTime = 1ll * *min_element(ranks.begin(), ranks.end()) * cars * cars;
    while(loTime < hiTime) {
        ll time = loTime + ((hiTime - loTime) >> 1);
        if(canRepairCars(time, cars, ranks)) {
            hiTime = time;
        }
        else {
            loTime = time + 1;
        }
    }
    return loTime;
}

// DAY 17 (2206. Divide Array Into Equal Pairs)==========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool divideArray(vector<int>& nums) {
    vector<int> freqMap(*max_element(nums.begin(), nums.end()) + 1, 0);
    for(int num : nums) {
        freqMap[num]++;
    }
    for(int freq : freqMap) {
        if(freq & 1) {
            return false;
        }
    }
    return true;
}

// DAY 18 (2401. Longest Nice Subarray)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int longestNiceSubarray(vector<int>& nums) {
    int maxSubarrayLen = 0;
    for(int curr = 0, prev = 0, currMask = 0; curr < nums.size(); curr++) {
        while(currMask & nums[curr]) {
            currMask ^= nums[prev++];
        }
        currMask |= nums[curr];
        maxSubarrayLen = max(maxSubarrayLen, curr - prev + 1);
    }
    return maxSubarrayLen;
}

// DAY 19 (3191. Minimum Operations to Make Binary Array Elements Equal to One I)===================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minOperations(vector<int>& nums) {
    int size = nums.size();
    int flips = 0;
    for(int idx = 0; idx < size - 2; idx++) {
        if(nums[idx] == 0) {
            nums[idx] ^= 1;
            if(idx + 1 < size) {
                nums[idx + 1] ^= 1;
            }
            if(idx + 2 < size) {
                nums[idx + 2] ^= 1;
            }
            flips++;
        }
    }
    return nums[size-1] == 0 || nums[size-2] == 0? -1 : flips;
}

// DAY 21 (2115. Find All Possible Recipes from Given Supplies)=======================================================

// Time Complexity = O(V + E)
// Space Complexity = O(V + E)

bool canCreate(string recipe, unordered_set<string> &supplySet, unordered_map<string,vector<string>> &graph, unordered_set<string> &vis) {
    if(supplySet.count(recipe)) {
        return true;
    }
    if(vis.count(recipe)) {
        return false;
    }
    if(graph[recipe].empty()) {
        return false;
    }

    vis.insert(recipe);

    for(string ingredient : graph[recipe]) {
        if(!canCreate(ingredient, supplySet, graph, vis)) {
            return false;
        }
    }

    vis.erase(recipe);

    supplySet.insert(recipe);

    return true;
}

vector<string> findAllRecipes(vector<string>& recipes, vector<vector<string>>& ingredients, vector<string>& supplies) {
    unordered_set<string> supplySet;
    unordered_map<string,vector<string>> graph;
    vector<string> finalRecipes;
    for(int idx = 0; idx < recipes.size(); idx++) {
        for(string ingredient : ingredients[idx]) {
            graph[recipes[idx]].push_back(ingredient);
        }
    }
    for(string supply : supplies) {
        supplySet.insert(supply);
    }

    for(string recipe : recipes) {
        unordered_set<string> vis;
        if(canCreate(recipe, supplySet, graph, vis)) {
            finalRecipes.push_back(recipe);
        }
    }

    return finalRecipes;
}

// DAY 22 (2685. Count the Number of Complete Components)===================================================================

// Time Complexity = O(V + E)
// Space Complexity = O(V)

class DSU {
    private:
    int size;
    vector<int> par;
    vector<int> parNodes;
    vector<int> parEdges;

    public:
    DSU(int size) {
        this->size = size;
        this->par.resize(size);
        this->parNodes.assign(size, 1);
        this->parEdges.assign(size, 0);
        for(int node = 0; node < size; node++) {
            par[node] = node;
        }
    }

    int getParEdges(int par) {
        return parEdges[par];
    }

    int getParNodes(int par) {
        return parNodes[par];
    }

    int findPar(int node) {
        return par[node] = par[node] == node? node : findPar(par[node]);
    }

    void merge(int u, int v) {
        int paru = findPar(u);
        int parv = findPar(v);

        if(parNodes[parv] > parNodes[paru]) {
            swap(paru, parv);
        }

        parEdges[paru]++;

        if(paru == parv) {
            return;
        }

        par[parv] = paru;
        parNodes[paru] += parNodes[parv];
        parEdges[paru] += parEdges[parv];
    }
};

int countCompleteComponents(int n, vector<vector<int>>& edges) {
    DSU dsu(n);
    unordered_set<int> ansPars;
    for(vector<int> &edge : edges) {
        int u = edge[0], v = edge[1];
        dsu.merge(u, v);
    }

    for(int node = 0; node < n; node++) {
        int par = dsu.findPar(node);
        int parEdges = dsu.getParEdges(par);
        int parNodes = dsu.getParNodes(par);
        if(parEdges == (parNodes * (parNodes - 1)) / 2) {
            ansPars.insert(par);
        }
    }

    return ansPars.size();
}

// DAY 23 (1976. Number of Ways to Arrive at Destination)==================================================================

// Time Complexity = O(E * logV)
// Space Complexity = O(E + V)

#define ll long long
const int MOD = 1e9 + 7;
int countPaths(int n, vector<vector<int>>& roads) {
    vector<ll> waysCount(n, 0);
    vector<ll> minTime(n, LLONG_MAX);
    vector<vector<vector<int>>> graph(n);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> minPq;
    minPq.push({0, 0}); // {wt, node}
    minTime[0] = 0;
    waysCount[0] = 1;

    for(vector<int> &road : roads) {
        int u = road[0];
        int v = road[1];
        int t = road[2];
        graph[u].push_back({v, t});
        graph[v].push_back({u, t});
    }

    while(!minPq.empty()) {
        ll parTime = minPq.top().first;
        int u = minPq.top().second;
        minPq.pop();
        if(u == n-1) {
            continue;
        }

        for(vector<int> &vt : graph[u]) {
            int v = vt[0];
            int childTime = vt[1];
            ll newTime = parTime + childTime;
            if(newTime <= minTime[v]) {
                if(newTime < minTime[v]) {
                    minTime[v] = newTime;
                    waysCount[v] = waysCount[u];
                    minPq.push({newTime, v});
                }
                else {
                    waysCount[v] = (waysCount[v] % MOD + waysCount[u] % MOD) % MOD;
                }
            }
        }
    }

    return waysCount[n-1];
}

// DAY 24 (3169. Count Days Without Meetings)=================================================================================

// Time Complexity = O(n * logn)
// Space Complexity = O(1)

int countDays(int days, vector<vector<int>>& meetings) {
    sort(meetings.begin(), meetings.end());
    int noMeetingDays = meetings[0][0] - 1;
    int maxEnd = meetings[0][1];
    for(int idx = 1; idx < meetings.size() && days > meetings[idx-1][1]; idx++) {
        noMeetingDays += max(0, min(meetings[idx][0], days) - maxEnd - 1);
        maxEnd = max(maxEnd, meetings[idx][1]);
    }
    noMeetingDays += max(0, days - maxEnd);
    return noMeetingDays;
}

// DAY 25 (3394. Check if Grid can be Cut into Sections)======================================================================

// Time Complexity = O(n * logn)
// Space Complexity = O(1)

bool checkValidCutsForAxis(int initIdx, vector<vector<int>>& rectangles) {
    sort(rectangles.begin(), rectangles.end(), [initIdx](auto const &arr1, auto const &arr2) {
        return arr1[initIdx] < arr2[initIdx];
    });
    int size = rectangles.size();
    int rectCount = 0;
    for(int curr = 0; curr < size; ) {
        int next = curr, maxEnd = rectangles[curr][initIdx + 2];
        while(next < size && rectangles[next][initIdx] < maxEnd) {
            maxEnd = max(maxEnd, rectangles[next++][initIdx + 2]);
        }
        rectCount++;
        curr = next;
    }
    return rectCount >= 3;
}

bool checkValidCuts(int n, vector<vector<int>>& rectangles) {
    return checkValidCutsForAxis(0, rectangles) || checkValidCutsForAxis(1, rectangles);
}

// DAY 26 (2033. Minimum Operations to Make a Uni-Value Grid)===============================================================

// APPROACH 1 (Using Sorting)

// Time Complexity = O(n * m * log(n * m))
// Space Complexity = O(n * m)

int minOperations(vector<vector<int>>& grid, int x) {
    vector<int> nums;
    int rows = grid.size(), cols = grid[0].size();
    int operations = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            nums.push_back(grid[row][col]);
        }
    }
    sort(nums.begin(), nums.end());

    int median = nums[nums.size() / 2];
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            int diff = abs(grid[row][col] - median);
            if(diff % x) {
                return -1;
            }
            operations += diff / x;
        }
    }
    return operations;
}

// APPROACH 2 (Using nth_element) --> [OPTIMIZED]

// Time Complexity = O(n * m)
// Space Complexity = O(n * m)

int minOperations(vector<vector<int>>& grid, int x) {
    vector<int> nums;
    int rows = grid.size(), cols = grid[0].size();
    int operations = 0;
    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            nums.push_back(grid[row][col]);
        }
    }
    nth_element(nums.begin(), (nums.begin() + (rows * cols) / 2), (nums.begin() + (rows * cols)));
    int median = nums[nums.size() / 2];

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            int diff = abs(grid[row][col] - median);
            if(diff % x) {
                return -1;
            }
            operations += diff / x;
        }
    }
    return operations;
}

// DAY 27 (2780. Minimum Index of a Valid Split)==========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumIndex(vector<int>& nums) {
    int size = nums.size();
    int countDom = 0, dom = -1;
    for(int num : nums) {
        if(dom == -1) {
            dom = num;
            countDom = 1;
        }
        else {
            countDom += num == dom? 1 : -1;
            if(countDom == 0) {
                dom = -1;
            }
        }
    }
    countDom = 0;
    for(int num : nums) {
        if(num == dom) {
            countDom++;
        }
    }

    int countDomLeft = 0, countDomRight = countDom;
    for(int idx = 0; idx < size - 1; idx++) {
        int countLeft = idx + 1;
        int countRight = size - idx - 1;
        countDomLeft += nums[idx] == dom;
        countDomRight -= nums[idx] == dom;
        if(countDomLeft > countLeft / 2 && countDomRight > countRight / 2) {
            return idx;
        }
    }
    return -1;
}

// DAY 28 (2503. Maximum Number of Points From Grid Queries)=================================================================================

// APPROACH 1 (Using Queue)

// Time Complexity = O((k * logk) + (k * (rows * cols)))
// Space Complexity = O((rows * cols) + k)

vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
    int rows = grid.size(), cols = grid[0].size(), k = queries.size();
    vector<int> ans(k);
    vector<vector<int>> queriesIdx(k);
    vector<vector<bool>> vis(rows, vector<bool>(cols, false));
    queue<pair<int,int>> nextQue, que;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int count = 0, lastQuery = -1;
    nextQue.push({0, 0});
    vis[0][0] = true;
    for(int idx = 0; idx < k; idx++) {
        queriesIdx[idx] = {queries[idx], idx};
    }
    sort(queriesIdx.begin(), queriesIdx.end());

    for(auto &queryPair : queriesIdx) {
        int query = queryPair[0];
        int idx = queryPair[1];
        if(lastQuery != query) {
            que = nextQue;
            nextQue = {};
            while(!que.empty()) {
                int row = que.front().first;
                int col = que.front().second;
                que.pop();

                if(grid[row][col] >= query) {
                    nextQue.push({row, col});
                }
                else {
                    count++;
                    for(int d = 0; d < 4; d++) {
                        int nrow = row + dir[d][0];
                        int ncol = col + dir[d][1];
                        if(nrow > -1 && nrow < rows && ncol > -1 && ncol < cols && !vis[nrow][ncol]) {
                            vis[nrow][ncol] = true;
                            if(grid[nrow][ncol] >= query) {
                                nextQue.push({nrow, ncol});
                            }
                            else {
                                que.push({nrow, ncol});
                            }
                        }
                    }
                }
            }
        }
        lastQuery = query;
        ans[idx] = count;
    }

    return ans;
}

// APPROACH 2 (Using Priority Queue) -> [OPTIMIZED]

// Time Complexity = O((k * logk) + ((rows * cols) + (k * log(rows * cols))))
// Space Complexity = O((rows * cols) + k)

vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries) {
    int rows = grid.size(), cols = grid[0].size(), k = queries.size();
    vector<int> ans(k);
    vector<vector<int>> queriesIdx(k);
    vector<vector<bool>> vis(rows, vector<bool>(cols, false));
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minPq;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    int count = 0;
    minPq.push({grid[0][0], 0, 0});
    vis[0][0] = true;
    for(int idx = 0; idx < k; idx++) {
        queriesIdx[idx] = {queries[idx], idx};
    }
    sort(queriesIdx.begin(), queriesIdx.end());

    for(auto &queryPair : queriesIdx) {
        int query = queryPair[0];
        int idx = queryPair[1];
        while(!minPq.empty() && minPq.top()[0] < query) {
            int row = minPq.top()[1];
            int col = minPq.top()[2];
            minPq.pop();
            count++;
            for(int d = 0; d < 4; d++) {
                int nrow = row + dir[d][0];
                int ncol = col + dir[d][1];
                if(nrow > -1 && nrow < rows && ncol > -1 && ncol < cols && !vis[nrow][ncol]) {
                    vis[nrow][ncol] = true;
                    minPq.push({grid[nrow][ncol], nrow, ncol});
                }
            }
        }
        ans[idx] = count;
    }

    return ans;
}

// DAY 30 (763. Partition Labels)=================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> partitionLabels(string s) {
    int size = s.size();
    int currIntEnd = 0;
    vector<int> lastOcc(26, -1);
    vector<int> lens;
    for(int idx = 0; idx < size; idx++) {
        lastOcc[s[idx]-'a'] = idx;
    }
    for(int idx = 0; idx < size; ) {
        int currIdx = idx;
        while(currIdx <= currIntEnd) {
            currIntEnd = max(currIntEnd, lastOcc[s[currIdx++]-'a']);
        }
        lens.push_back(currIdx - idx);
        idx = currIdx;
        currIntEnd = currIdx;
    }
    return lens;
}
