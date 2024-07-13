
// WEEK 1 (1940. Longest Common Subsequence Between Sorted Arrays)=========================================

// Time Complexity = O(n)
// Space Complexity = O(n*m)

vector<int> longestCommonSubsequence(vector<vector<int>>& arrays)
{
    int size = arrays.size();
    vector<int> itrs(size, 0);
    vector<int> commons;
    while(true)
    {
        int maxEle = INT_MIN, maxEle2 = INT_MIN;
        for(int idx = 0; idx < size; idx++)
        {
            if(arrays[idx][itrs[idx]] > maxEle)
            {
                maxEle2 = maxEle;
                maxEle = arrays[idx][itrs[idx]];
            }
            else if(arrays[idx][itrs[idx]] < maxEle)
                maxEle2 = max(maxEle2, arrays[idx][itrs[idx]]);
        }
        if(maxEle2 == INT_MIN)
            commons.push_back(maxEle);
        for(int idx = 0; idx < size; idx++)
            if(maxEle2 == INT_MIN || arrays[idx][itrs[idx]] < maxEle)
                if(++itrs[idx] == arrays[idx].size())
                    return commons;
    }

    return commons;
}

// DAY 1 (3110. Score of a String)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int scoreOfString(string s) 
{
    int score = 0;
    for(int idx = 1; idx < s.size(); idx++)
        score += abss[idx] - s[idx-1];
    return score;
}

// DAY 2 (344. Reverse String)===============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void reverseString(vector<char>& s) 
{
    int start = 0, end = s.size()-1;
    while(start < end)
        swap(s[start++], s[end--]);
}

// DAY 3 (2486. Append Characters to String to Make Subsequence)====================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int appendCharacters(string s, string t)
{
    int sSize = s.size(), tSize = t.size();
    int idx1 = 0, idx2 = 0;
    while(idx1 < sSize && idx2 < tSize)
    {
        if(s[idx1] == t[idx2])
            idx2++;
        idx1++;
    }
    return tSize - idx2;
}

// DAY 4 (409. Longest Palindrome)=====================================================================================

// Time Complexity = O(n + c)
// Space Complexity = O(c)

int longestPalindrome(string s) 
{
    map<char,int> cntMap;
    int maxLen = 0, totalOdds = 0, totalOddLen = 0;
    for(char c : s)
        cntMap[c]++;
    
    for(auto pair : cntMap)
    {
        int count = pair.second;
        if(count & 1 ^ 1)
            maxLen += count;
        else
        {
            totalOdds++;
            totalOddLen += count;
        }
    }
    return maxLen + (totalOdds? (totalOddLen - totalOdds + 1) : 0);
}

// DAY 5 (1002. Find Common Characters)===================================================================================

// Time Complexity = O(n * (m + 26))
// Space Complexity = O(n*m + 26)

vector<string> commonChars(vector<string>& words) 
{
    vector<int> commonOcc(26, INT_MAX);
    vector<string> ans;
    for(string word : words)
    {
        vector<int> currOcc(26, 0);
        for(char c : word)
            currOcc[c-'a']++;
        for(int ch = 0; ch < 26; ch++)
            commonOcc[ch] = min(commonOcc[ch], currOcc[ch]);
    }
    for(int ch = 0; ch < 26; ch++)
        while(commonOcc[ch]--)
            ans.push_back(string(1, char(ch + 'a')));
    
    return ans;
}

// DAY 6 (846. Hand of Straights)============================================================================================

// Time Complexity = O(n*logn + n)
// Space Complexity = O(n)

bool isNStraightHand(vector<int>& hand, int groupSize) 
{
    int handSize = hand.size();
    unordered_map<int,int> cardCnt;
    sort(hand.begin(), hand.end());
    for(int card : hand)
        cardCnt[card]++;
    for(int card : hand)
    {
        if(cardCnt[card] == 0)
            continue;
        int size = 0, currCard = card;
        while(size < groupSize && cardCnt.count(currCard))
        {
            size++;
            if(--cardCnt[currCard] == 0)
                cardCnt.erase(currCard);
            currCard++;
        }
        if(size < groupSize)
            return false;
    }

    return true;
}

// DAY 7 (648. Replace Words)=====================================================================================================

// APPROACH 1 (Using Set to store roots)

// [n = dictionary.size(), n1 = average root size, m = sentence.size()]

// Time Complexity = >O(n*n1 + m)
// Space Complexity = O(n*n1 + m)

string replaceWords(vector<string>& dictionary, string sentence) 
{
    int size = sentence.size();
    unordered_set<string> roots;
    string ans = "";
    for(string root : dictionary)
        roots.insert(root);
    string currWord = "";
    bool foundRoot = false;
    for(int idx = 0; idx <= size; idx++)
    {
        if(idx == size || sentence[idx] == ' ' || foundRoot)
        {
            if(!foundRoot)
                ans += currWord + " ";
            else if(idx < size && sentence[idx] == ' ')
                foundRoot = false;
            currWord = "";
            continue;
        }
        currWord += sentence[idx];
        if(roots.count(currWord))
        {
            foundRoot = true;
            ans += currWord + " ";
        }
    }
    if(!ans.empty())
        ans.pop_back();
    return ans;
}

// APPROACH 2 (Using Trie) [OPTIMIZED]

// Time Complexity = O(n*n1 + m)
// Space Complexity = O(n*n1 + m)

class Trie
{
    public:
    int size;
    vector<Trie*> children;
    bool wordEnd;
    Trie(int size)
    {
        this->size = size;
        this->children.assign(size, nullptr);
        this->wordEnd = false;
    }

    void insert(string word)
    {
        Trie* itr = this;
        for(char c : word)
        {
            if(!itr->children[c-'a'])
                itr->children[c-'a'] = new Trie(this->size);
            itr = itr->children[c-'a'];
        }
        itr->wordEnd = true;
    }
};

string replaceWords(vector<string>& dictionary, string sentence) 
{
    int size = sentence.size();
    string ans = "";
    Trie* trieRoot = new Trie(26);
    for(string root : dictionary)
        trieRoot->insert(root);
    
    Trie* itr = trieRoot;
    string currWord = "";
    bool foundRoot = false;
    for(int idx = 0; idx <= size; idx++)
    {
        char currChar = sentence[idx];
        if(idx == size || currChar == ' ' || foundRoot)
        {
            if(!foundRoot)
                ans += currWord + " ";
            else if(idx < size && currChar == ' ')
                foundRoot = false;
            currWord = "";
            itr = trieRoot;
            continue;
        }
        currWord += currChar;
        if(itr)
            itr = itr->children[currChar-'a'];
        if(itr && itr->wordEnd)
        {
            foundRoot = true;
            ans += currWord + " ";
        }
    }
    if(!ans.empty())
        ans.pop_back();
    return ans;
}

// DAY 8 (523. Continuous Subarray Sum)========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(k)

bool checkSubarraySum(vector<int>& nums, int k) 
{
    unordered_map<int, int> subArraySumCnt;
    int sum = 0;
    subArraySumCnt[sum % k] = -1;
    for(int idx = 0; idx < nums.size(); idx++)
    {
        sum += nums[idx];
        if(subArraySumCnt.count(sum % k) && idx - subArraySumCnt[sum % k] > 1)
            return true;
        if(!subArraySumCnt.count(sum % k))
            subArraySumCnt[sum % k] = idx;
    }
    return false;
}

// DAY 9 (974. Subarray Sums Divisible by K)====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(k)

int subarraysDivByK(vector<int>& nums, int k)
{
    int subArrayCount = 0;
    vector<int> divs(k, 0);
    int sum = 0;
    divs[sum] = 1;
    for(int num : nums)
    {
        sum += num;
        subArrayCount += divs[(sum % k + k) % k]++;
    }
    return subArrayCount;
}

// DAY 10 (1051. Height Checker)===================================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int heightChecker(vector<int>& heights)
{
    int n = heights.size();
    int mismatchCount = 0;
    vector<int> expected = heights;
    sort(expected.begin(), expected.end());
    for(int idx = 0; idx < n; idx++)
        if(heights[idx] != expected[idx])
            mismatchCount++;
    return mismatchCount;
}

// DAY 11 (1122. Relative Sort Array)==============================================================================

// Time Complexity = O(n + m + mx1)
// Space Complexity = O(mx1)

vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2)
{
    int size1 = arr1.size(), size2 = arr2.size();
    int maxEle = *max_element(arr1.begin(), arr1.end());
    vector<int> posMap(maxEle + 1);
    for(int idx = 0; idx < size1; idx++)
        posMap[arr1[idx]]++;
    int lastIdx = 0;
    for(int idx = 0; idx < size2; idx++)
        while(posMap[arr2[idx]]-- > 0)
            arr1[lastIdx++] = arr2[idx];
    for(int num = 0; num <= maxEle; num++)
        while(posMap[num]-- > 0)
            arr1[lastIdx++] = num;

    return arr1;
}

// DAY 12 (75. Sort Colors)==============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void sortColors(vector<int>& nums)
{
    int size = nums.size();
    int idx0 = 0, idx1 = 0, idx2 = size-1;
    while(idx1 <= idx2)
    {
        if(nums[idx1] == 0)
            swap(nums[idx0++], nums[idx1++]);
        else if(nums[idx1] == 2)
            swap(nums[idx2--], nums[idx1]);
        else idx1++;
    }
}

// DAY 13 (2037. Minimum Number of Moves to Seat Everyone)==========================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int minMovesToSeat(vector<int>& seats, vector<int>& students)
{
    int size = seats.size();
    sort(seats.begin(), seats.end());
    sort(students.begin(), students.end());
    int minOps = 0;
    for(int idx = 0; idx < size; idx++)
        minOps += abs(seats[idx] - students[idx]);
    return minOps;
}

// DAY 14 (945. Minimum Increment to Make Array Unique)================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

int minIncrementForUnique(vector<int>& nums)
{
    int size = nums.size();
    int prev = -1, minMoves = 0;
    sort(nums.begin(), nums.end());
    for(int num : nums)
    {
        int curr = max(prev + 1, num);
        minMoves += curr - num;
        prev = curr;
    }
    return minMoves;
}

// [PREMIUM] WEEK 2 (2083. Substrings That Begin and End With the Same Letter)=========================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

long long numberOfSubstrings(string s) 
{
    vector<int> charMap(26, 0);
    long long ans = 0;
    for(char c : s)
        ans += ++charMap[c-'a'];
    return ans;
}

// DAY 15 (502. IPO)==================================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital)
{
    int projects = profits.size();
    vector<pair<int,int>> capProfPair(projects);
    priority_queue<pair<int,int>> maxProfPq;
    int lastIdx = 0;
    int maxCap = w;
    for(int idx = 0; idx < projects; idx++)
        capProfPair[idx] = {capital[idx], profits[idx]};
    sort(capProfPair.begin(), capProfPair.end());

    do
    {
        while(lastIdx < projects && maxCap >= capProfPair[lastIdx].first)
        {
            int capital = capProfPair[lastIdx].first;
            int profit = capProfPair[lastIdx].second;
            maxProfPq.push({profit, capital});
            lastIdx++;
        }
        if(!maxProfPq.empty() && k--)
        {
            maxCap += maxProfPq.top().first;
            maxProfPq.pop();
        }
        else break;
    }
    while(true);

    return maxCap;
}

// DAY 16 (330. Patching Array)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minPatches(vector<int>& nums, int n)
{
    int size = nums.size();
    int ans = 0;
    long currSum = 1;
    for(int idx = 0; currSum <= n; )
    {
        if(idx < size && nums[idx] <= currSum)
            currSum += nums[idx++];
        else
        {
            currSum += currSum;
            ans++;
        }
    }
    return ans;
}

// DAY 17 (633. Sum of Square Numbers)===================================================================================

// APPROACH 1 (Binary search)

// Time Complexity = O(sqrt(c) * log(sqrt(c)))
// Space Complexity = O(1)

bool judgeSquareSum(int c)
{
    int c2 = sqrt(c);
    for(long a = 0; a <= c2; a++)
    {
        int lo = a, hi = c2;
        while(lo <= hi)
        {
            int b = (lo + hi) >> 1;
            if(a*a + b*b == c)
                return true;
            if(a*a + b*b < c)
                lo = b + 1;
            else hi = b - 1;
        }
    }
    return false;
}

// APPROACH 2 (2 pointer) [OPTIMIZED]

// Time Complexity = O(sqrt(c))
// Space Complexity = O(1)

bool judgeSquareSum(int c)
{
    long long a = 0, b = sqrt(c);
    while(a <= b)
    {
        if(a*a + b*b == c)
            return true;
        if(a*a + b*b < c)
            a++;
        else b--;
    }
    return false;
}

// DAY 18 (826. Most Profit Assigning Work)========================================================

// Time Complexity = O(n + maxDifficulty + m)
// Space Complexity = O(maxDifficulty)

int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker)
{
    int n = difficulty.size(), m = worker.size();
    int maxDifficulty = *max_element(difficulty.begin(), difficulty.end());
    vector<int> maxProfit(maxDifficulty+1, 0);
    for(int idx = 0; idx < n; idx++)
        maxProfit[difficulty[idx]] = max(maxProfit[difficulty[idx]], profit[idx]);
    for(int diff = 1; diff <= maxDifficulty; diff++)
        maxProfit[diff] = max(maxProfit[diff], maxProfit[diff-1]);
    
    int totalProfit = 0;
    for(int ability : worker)
        totalProfit += maxProfit[min(ability, maxDifficulty)];
    
    return totalProfit;
}

// DAY 19 (1482. Minimum Number of Days to Make m Bouquets)===============================================================================================

// Time Complexity = O(n*log(mx))
// Space Complexity = O(1)

bool canMakeBouquetsInDays(int days, vector<int> &bloomDay, int blooms, int k, int m)
{
    int bouquets = 0;
    for(int idx = 0; idx < blooms && bouquets < m; )
    {
        int itr = idx;
        while(itr < blooms && (itr - idx < k) && bloomDay[itr] <= days)
            itr++;
        if(itr - idx == k)
            bouquets++;
        idx = itr;
        if(idx < blooms && bloomDay[idx] > days)
            idx++;
    }
    return bouquets >= m;
}

int minDays(vector<int>& bloomDay, int m, int k)
{
    int blooms = bloomDay.size();
    if(blooms < 1ll*m*k)
        return -1;
    int lo = 1, hi = *max_element(bloomDay.begin(), bloomDay.end());
    int ans = -1;
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(canMakeBouquetsInDays(mid, bloomDay, blooms, k, m))
        {
            hi = mid - 1;
            ans = mid;
        }
        else lo = mid + 1;
    }
    return ans;
}

// DAY 20 (1552. Magnetic Force Between Two Balls)==================================================================================

// Time Complexity = O(n*log(maxDist))
// Space Complexity = O(1)

bool canArrangeWithDistance(int minDist, vector<int> &position, int m)
{
    int ballsPlaced = 0, prevDist = -1;
    for(int dist : position)
    {
        if(prevDist == -1 || dist - prevDist >= minDist)
        {
            ballsPlaced++;
            prevDist = dist;
        }
    }
    return ballsPlaced >= m;
}

int maxDistance(vector<int>& position, int m)
{
    int size = position.size();
    sort(position.begin(), position.end());
    int low = 0, high = position[size-1] - position[0];
    int ans = -1;
    while(low <= high)
    {
        int mid = low + ((high - low) >> 1);
        if(canArrangeWithDistance(mid, position, m))
        {
            low = mid + 1;
            ans = mid;
        }
        else high = mid - 1;
    }
    return ans;
}

// DAY 21 (1052. Grumpy Bookstore Owner)==================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes)
{
    int size = customers.size();
    int maxExtra = 0, currExtra = 0, totalCustomers = 0;
    for(int minute = 0; minute < size; minute++)
    {
        if(!grumpy[minute])
            totalCustomers += customers[minute];
        else currExtra += customers[minute];
        currExtra -= minute - minutes >= 0 && grumpy[minute - minutes]? customers[minute - minutes] : 0;
        maxExtra = max(maxExtra, currExtra);
    }
    return totalCustomers + maxExtra;
}

// WEEK 3 (1580. Put Boxes Into the Warehouse II)==========================================================================

// APPROACH 1 (Starting from the smallest effective warehouse height and box to the biggest)

// Time Complexity = O(n*logn + m*logm + m)
// Space Complexity = O(m)

int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse)
{
    int n = boxes.size(), m = warehouse.size();
    vector<int> effectiveHeight(m);
    int minHeight = INT_MAX;
    int boxCount = 0;
    for(int idx = 0; idx < m; idx++)
    {
        minHeight = min(minHeight, warehouse[idx]);
        effectiveHeight[idx] = minHeight;
    }
    minHeight = INT_MAX;
    for(int idx = m-1; idx >= 0; idx--)
    {
        minHeight = min(minHeight, warehouse[idx]);
        effectiveHeight[idx] = max(minHeight, effectiveHeight[idx]);
    }
    sort(boxes.begin(), boxes.end());
    sort(effectiveHeight.begin(), effectiveHeight.end());

    for(int idx = 0, boxIdx = 0; idx < m && boxIdx < n; idx++)
        if(effectiveHeight[idx] >= boxes[boxIdx])
            boxIdx++, boxCount++;
    
    return boxCount;
}

// APPROACH 2 (Starting from the biggest box to the smallest) --> [OPTIMIZED]

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse)
{
    int n = boxes.size(), m = warehouse.size();
    int boxCount = 0;
    sort(boxes.begin(), boxes.end());
    
    for(int leftIdx = 0, rightIdx = m-1, boxIdx = n-1; leftIdx <= rightIdx && boxIdx >= 0; boxIdx--)
    {
        if(warehouse[leftIdx] >= boxes[boxIdx])
            leftIdx++, boxCount++;
        else if(warehouse[rightIdx] >= boxes[boxIdx])
            rightIdx--, boxCount++;
    }
    
    return boxCount;
}

// DAY 22 (1248. Count Number of Nice Subarrays)=======================================================================================================

// APPROACH 1 (Querying for k and k-1 (in 2 Loops))

// Time Complexity = O(n)
// Space Complexity = O(1)

long getNiceCountWithAtMost(int k, int size, vector<int> &nums)
{
    long odds = 0, niceCount = 0;
    for(long ridx = 0, lidx = 0; ridx < size; ridx++)
    {
        odds += nums[ridx] & 1;
        while(odds > k)
            odds -= nums[lidx++] & 1;
        niceCount += (ridx - lidx + 1);
    }
    return niceCount;
}

int numberOfSubarrays(vector<int>& nums, int k)
{
    int size = nums.size();
    return getNiceCountWithAtMost(k, size, nums) - getNiceCountWithAtMost(k-1, size, nums);
}

// APPROACH 2 (Single loop) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfSubarrays(vector<int>& nums, int k)
{
    int size = nums.size();
    int niceCount = 0, gapWithPrevOdd = 0, odds = 0;
    for(int ridx = 0, lidx = 0; ridx < size; ridx++)
    {
        odds += nums[ridx] & 1;
        if(odds == k)
        {
            gapWithPrevOdd = 0;
            while(odds == k)
            {
                gapWithPrevOdd++;
                odds -= nums[lidx++] & 1;
            }
        }
        niceCount += gapWithPrevOdd;
    }
    return niceCount;
}

// DAY 23 (1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit)=========================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int longestSubarray(vector<int>& nums, int limit)
{
    int size = nums.size();
    multiset<int> st;
    int maxSize = 0;
    for(int ridx = 0, lidx = 0; ridx < size; ridx++)
    {
        st.insert(nums[ridx]);
        int minEle = *st.begin();
        int maxEle = *st.rbegin();
        while(maxEle - minEle > limit)
        {
            st.erase(st.find(nums[lidx++]));
            minEle = *st.begin();
            maxEle = *st.rbegin();
        }
        maxSize = max(maxSize, ridx - lidx + 1);
    }

    return maxSize;
}

// DAY 24 (995. Minimum Number of K Consecutive Bit Flips)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minKBitFlips(vector<int>& nums, int k)
{
    int size = nums.size();
    int totalFlips = 0, currFlips = 0;
    for(int idx = 0; idx < size; idx++)
    {
        if(idx - k >= 0 && nums[idx - k] == 2)
            currFlips--;
        if((currFlips & 1) == nums[idx])
        {
            if(idx + k > size)
                return -1;
            nums[idx] = 2;
            totalFlips++;
            currFlips++;
        }
    }
    return totalFlips;
}

// DAY 25 (1038. Binary Search Tree to Greater Sum Tree)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

void bstToGstDFS(TreeNode* node, int &greaterSum)
{
    if(!node) return;
    
    bstToGstDFS(node->right, greaterSum);
    greaterSum += node->val;
    node->val = greaterSum;
    bstToGstDFS(node->left, greaterSum);
}

TreeNode* bstToGst(TreeNode* root)
{
    int greaterSum = 0;
    bstToGstDFS(root, greaterSum);
    return root;
}

// WEEK 4 (2743. Count Substrings Without Repeating Character)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numberOfSpecialSubstrings(string s)
{
    int size = s.size();
    int totalSubtrings = 0;
    int charMask = 0;
    for(int ridx = 0, lidx = 0; ridx < size; ridx++)
    {
        int currMask = (1 << (s[ridx]-'a'));
        while(charMask & currMask)
            charMask ^= (1 << (s[lidx++]-'a'));
        charMask ^= currMask;

        totalSubtrings += ridx - lidx + 1;
    }
    return totalSubtrings;
}

// DAY 26 (1382. Balance a Binary Search Tree)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

void addNodesToList(TreeNode* node, vector<int> &nodes)
{
    if(!node)
        return;
    addNodesToList(node->left, nodes);
    nodes.push_back(node->val);
    addNodesToList(node->right, nodes);
}

TreeNode* createTree(int lidx, int ridx, vector<int> &nodes)
{
    if(lidx > ridx)
        return nullptr;
    
    int midIdx = (lidx + ridx) / 2;
    TreeNode* node = new TreeNode(nodes[midIdx]);
    
    node->left = createTree(lidx, midIdx - 1, nodes);
    node->right = createTree(midIdx + 1, ridx, nodes);

    return node;
}

TreeNode* balanceBST(TreeNode* root)
{
    vector<int> nodes;
    addNodesToList(root, nodes);
    return createTree(0, nodes.size()-1, nodes);
}

// DAY 27 (1791. Find Center of Star Graph)======================================================================================

// APPROACH 1 (Through In-degree)

// Time Complexity = O(n)
// Space Complexity = O(n)

int findCenter(vector<vector<int>>& edges)
{
    int n = edges.size() + 1;
    vector<int> inDegree(n+1, 0);
    for(vector<int> &edge : edges)
    {
        if(inDegree[edge[0]])
            return edge[0];
        if(inDegree[edge[1]])
            return edge[1];
        inDegree[edge[0]]++;
        inDegree[edge[1]]++;
    }
    return 0;
}

// APPROACH 2 (One-Liner) --> [OPTIMIZED]

// Time Complexity = O(1)
// Space Complexity = O(1)

int findCenter(vector<vector<int>>& edges)
{
    return (edges[0][0] == edges[1][0] || edges[0][0] == edges[1][1])? edges[0][0] : edges[0][1];
}

// DAY 28 (2285. Maximum Total Importance of Roads)=================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

long long maximumImportance(int n, vector<vector<int>>& roads)
{
    vector<int> inDegree(n, 0);
    for(vector<int> &road : roads)
    {
        inDegree[road[0]]++;
        inDegree[road[1]]++;
    }
    sort(inDegree.rbegin(), inDegree.rend());

    long long maximumTotalImp = 0, currValue = n;
    for(long long degree : inDegree)
        maximumTotalImp += degree * currValue--;
    return maximumTotalImp;
}

// DAY 29 (2192. All Ancestors of a Node in a Directed Acyclic Graph)=================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*n)

vector<vector<int>> getAncestors(int n, vector<vector<int>>& edges)
{
    vector<vector<int>> graph(n);
    vector<int> inDegree(n, 0);
    vector<unordered_set<int>> ancestors(n);
    queue<int> que;
    for(vector<int> &edge : edges)
    {
        int src = edge[0], dest = edge[1];
        graph[src].push_back(dest);
        inDegree[dest]++;
    }
    for(int node = 0; node < n; node++)
        if(inDegree[node] == 0)
            que.push(node);
    while(!que.empty())
    {
        int currNode = que.front();
        que.pop();
        for(int nextNode : graph[currNode])
        {
            if(--inDegree[nextNode] == 0)
                que.push(nextNode);
            ancestors[nextNode].insert(currNode);
            for(int nodeInPath : ancestors[currNode])
                ancestors[nextNode].insert(nodeInPath);
        }
    }

    vector<vector<int>> ans;
    for(unordered_set<int> ancestorSet : ancestors)
    {
        ans.emplace_back(ancestorSet.begin(), ancestorSet.end());
        sort(ans.back().begin(), ans.back().end());
    }
    return ans;
}

// DAY 30 (1579. Remove Max Number of Edges to Keep Graph Fully Traversable)==================================================================================

// Time Complexity = O(V + E)
// Space Complexity = O(V)

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
            par[node] = node;
    }

    int findPar(int node)
    {
        return par[node] = par[node] == node? node : findPar(par[node]);
    }

    bool canMergeThenMerge(int node1, int node2)
    {
        int par1 = findPar(node1);
        int par2 = findPar(node2);
        if(par1 == par2) return false;

        if(parSize[par1] < parSize[par2])
            swap(par1, par2);
        parSize[par1] += parSize[par2];
        par[par2] = par1;

        return true;
    }
};

int redundantEdgesCount = 0;

vector<int> getTypeCount(vector<vector<int>> &edges)
{
    vector<int> typeCount(3);
    for(vector<int> edge : edges)
        typeCount[edge[0]-1]++;
    return typeCount;
}

DSU getGraphForType(int type, DSU dsu, vector<vector<int>> &edges)
{
    for(vector<int> &edge : edges)
        if(edge[0] == type)
            if(!dsu.canMergeThenMerge(edge[1]-1, edge[2]-1))
                redundantEdgesCount++;
    return dsu;
}

bool isGraphCompletelyConnected(DSU dsu)
{
    int lastPar = -1;
    for(int par : dsu.par)
    {
        int realPar = dsu.findPar(par);
        if(lastPar != -1 && lastPar != realPar)
            return false;
        lastPar = realPar;
    }
    return true;
}

int maxNumEdgesToRemove(int n, vector<vector<int>>& edges)
{
    DSU dsu(n);
    
    DSU dsuType3 = getGraphForType(3, dsu, edges);
    
    DSU dsuType1 = getGraphForType(1, dsuType3, edges);
    if(!isGraphCompletelyConnected(dsuType1))
        return -1;
    
    DSU dsuType2 = getGraphForType(2, dsuType3, edges);
    if(!isGraphCompletelyConnected(dsuType2))
        return -1;
    
    return redundantEdgesCount;
}
