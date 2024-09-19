
// DAY 1 (2022. Convert 1D Array Into 2D Array)====================================================================

// Time Complexity - O(n*m)
// Space Complexity - O(n*m)

vector<vector<int>> construct2DArray(vector<int>& original, int m, int n)
{
    int size = original.size();
    if(size != n*m)
        return {};
    
    vector<vector<int>> ans(m, vector<int>(n));
    for(int i = 0; i < size; i++)
    {
        int row = i / n;
        int col = i % n;
        ans[row][col] = original[i];
    }

    return ans;
}

// DAY 2 (1894. Find the Student that Will Replace the Chalk)=========================================================

// Time Complexity = O(n + logn)
// Time Complexity = O(n)

int chalkReplacer(vector<int>& chalk, int k)
{
    int size = chalk.size();
    vector<long> prefChalkSum(size, 0);
    for(int idx = 0; idx < size; idx++)
        prefChalkSum[idx] = (idx? prefChalkSum[idx-1] : 0) + chalk[idx];
    
    long kulChalks = prefChalkSum[size-1];
    int bacheChalks = k % kulChalks;

    int bakchodBacha = upper_bound(prefChalkSum.begin(), prefChalkSum.end(), bacheChalks) - prefChalkSum.begin();

    return bakchodBacha;
}

// DAY 3 (1945. Sum of Digits of String After Convert)======================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getLucky(string s, int k)
{
    int size = s.size();
    string numStr = "";
    for(char c : s)
        numStr += to_string(c - 'a' + 1);
    
    int ans = 0;
    for(char c : numStr)
        ans += c-'0';
    while(--k)
    {
        int nextNum = 0;
        while(ans)
        {
            nextNum += ans % 10;
            ans /= 10;
        }
        ans = nextNum;
    }

    return ans;
}

// DAY 4 (874. Walking Robot Simulation)=======================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(n)

int getEuclidianDistance(int x, int y)
{
    return x*x + y*y;
}

int robotSim(vector<int>& commands, vector<vector<int>>& obstacles)
{
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    unordered_map<int,unordered_set<int>> obsMap;
    int itr = 0;
    for(vector<int> obstacle : obstacles)
        obsMap[obstacle[0]].insert(obstacle[1]);
    
    int maxDist = 0, currX = 0, currY = 0;
    
    for(int command : commands)
    {
        if(command == -1)
            itr = (itr + 1) % 4;
        else if(command == -2)
            itr = ((itr - 1) + 4) % 4;
        else
        {
            int k = command;
            int nextX = currX + dir[itr][0];
            int nextY = currY + dir[itr][1];
            while(!obsMap[nextX].count(nextY) && k--)
            {
                currX = nextX;
                currY = nextY;
                maxDist = max(maxDist, getEuclidianDistance(currX, currY));
                nextX = currX + dir[itr][0];
                nextY = currY + dir[itr][1];
            }
        }
    }

    return maxDist;
}

// DAY 5 (2028. Find Missing Observations)=======================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(n)

vector<int> missingRolls(vector<int>& rolls, int mean, int n)
{
    int m = rolls.size();
    int currSum = accumulate(rolls.begin(), rolls.end(), 0);
    int target = mean * (n + m) - currSum;
    if(target > n*6 || target < n)
        return {};
    
    int q = target / n;
    int r = target % n;
    vector<int> ans(n, q);
    fill(ans.begin(), ans.begin() + r, q+1);

    return ans;
}

// DAY 6 (3217. Delete Nodes From Linked List Present in Array)=================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* modifiedList(vector<int>& nums, ListNode* head)
{
    unordered_set<int> st;
    for(int num : nums)
        st.insert(num);
    
    ListNode* itr = head, *prev = nullptr;
    while(itr)
    {
        if(st.count(itr->val))
        {
            if(prev)
                prev->next = itr->next;
            else head = itr->next;
        }
        else prev = itr;
        itr = itr->next;
    }

    return head;
}

// DAY 7 (1367. Linked List in Binary Tree)=================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

bool checkIfValidPathDFS(ListNode* head, TreeNode* node)
{
    if(head == nullptr)
        return true;
    if(node == nullptr || head->val != node->val)
        return false;
    
    if(checkIfValidPathDFS(head->next, node->left) || checkIfValidPathDFS(head->next, node->right))
        return true;
    
    return false;
}

bool traverseDFS(ListNode* head, TreeNode* node)
{
    if(!node)
        return false;
    
    if(head->val == node->val && checkIfValidPathDFS(head, node))
        return true;
    
    if(traverseDFS(head, node->left))
        return true;
    if(traverseDFS(head, node->right))
        return true;
    
    return false;
}

bool isSubPath(ListNode* head, TreeNode* root)
{
    return traverseDFS(head, root);
}

// DAY 8 (725. Split Linked List in Parts)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getListSize(ListNode* head)
{
    ListNode* itr = head;
    int size = 0;
    while(itr)
    {
        size++;
        itr = itr->next;
    }
    return size;
}

vector<ListNode*> splitListToParts(ListNode* head, int k)
{
    int size = getListSize(head);
    int subSize = size / k;
    int extra = size % k;
    vector<ListNode*> ans;

    ListNode* itr = head;
    while(k--)
    {
        ListNode* tmp = itr;
        int currSize = subSize;
        if(extra)
        {
            extra--;
            currSize++;
        }
        ans.push_back(tmp);
        while(tmp && --currSize > 0)
            tmp = tmp->next;
        if(tmp)
        {
            itr = tmp->next;
            tmp->next = nullptr;
        }
        else itr = nullptr;
    }

    return ans;
}

// DAY 9 (2326. Spiral Matrix IV)==============================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

vector<vector<int>> spiralMatrix(int m, int n, ListNode* head)
{
    vector<vector<int>> ans(m, vector<int>(n, -1));
    int sr = 0, sc = 0, er = m-1, ec = n-1;
    int r = 0, c = 0, d = 0;
    ListNode* itr = head;
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    while(itr)
    {
        while(itr && r >= sr && r <= er && c >= sc && c <= ec)
        {
            ans[r][c] = itr->val;
            itr = itr->next;
            r += dir[d][0];
            c += dir[d][1];
        }
        if(d == 0)
            r++, c--, sr++;
        else if(d == 1)
            r--, c--, ec--;
        else if(d == 2)
            r--, c++, er--;
        else if(d == 3)
            r++, c++, sc++;
        d = (d + 1) % 4;
    }

    return ans;
}

// DAY 10 (2807. Insert Greatest Common Divisors in Linked List)==================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* insertGreatestCommonDivisors(ListNode* head)
{
    ListNode* itr = head;
    while(itr && itr->next)
    {
        int gcd = __gcd(itr->val, itr->next->val);
        ListNode* next = itr->next;
        itr->next = new ListNode(gcd);
        itr->next->next = next;
        itr = next;
    }
    return head;
}

// DAY 11 (2220. Minimum Bit Flips to Convert Number)=============================================================================

// Time Complexity = O(log(N))
// Space Complexity = O(1)

int minBitFlips(int start, int goal)
{
    int minFlips = 0;
    while(start || goal)
    {
        minFlips += (start & 1) ^ (goal & 1);
        start >>= 1;
        goal >>= 1;
    }
    return minFlips;
}

// DAY 12 (1684. Count the Number of Consistent Strings)=======================================================================

// Time Complexity = O(n*26)
// Space Complexity = O(1)

int getWordMask(string &word)
{
    int mask = 0;
    for(char c : word)
        mask |= (1 << (c - 'a'));
    return mask;
}

int countConsistentStrings(string allowed, vector<string>& words)
{
    int allowedMask = getWordMask(allowed);
    int consistentWords = 0;
    for(string word : words)
    {
        int wordMask = getWordMask(word);
        bool isConsitentWord = true;
        for(int bit = 0; bit < 26 && isConsitentWord; bit++)
            if((wordMask & (1 << bit)) && !(allowedMask & (1 << bit)))
                isConsitentWord = false;
        if(isConsitentWord)
            consistentWords++;
    }
    return consistentWords;
}

// DAY 13 (1310. XOR Queries of a Subarray)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries)
{
    int size = arr.size();
    vector<int> prefXor(size, 0);
    vector<int> ans;
    for(int idx = 0; idx < size; idx++)
        prefXor[idx] = arr[idx] ^ (idx? prefXor[idx-1] : 0);
    
    for(vector<int> &query : queries)
    {
        int left = query[0];
        int right = query[1];
        ans.push_back(prefXor[right] ^ (left? prefXor[left-1] : 0));
    }
    return ans;
}

// DAY 14 (2419. Longest Subarray With Maximum Bitwise AND)=============================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int longestSubarray(vector<int>& nums)
{
    int size = nums.size();
    int maxEle = 0, maxLen = 0;
    for(int idx = 0; idx < size; )
    {
        if(nums[idx] < maxEle)
        {
            idx++;
            continue;
        }
        if(nums[idx] > maxEle)
        {
            maxEle = nums[idx];
            maxLen = 0;
        }
        int tempIdx = idx;
        while(tempIdx < size && nums[tempIdx] == maxEle)
            tempIdx++;
        maxLen = max(maxLen, tempIdx - idx);
        idx = tempIdx;
    }

    return maxLen;
}

// DAY 15 (1371. Find the Longest Substring Containing Vowels in Even Counts)====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int findTheLongestSubstring(string s)
{
    int vowelMask = 0;
    int pos = 0, maxLen = 0;
    unordered_map<char,int> charIdx;
    unordered_map<int,int> maskPos;
    charIdx['a'] = 0;
    charIdx['e'] = 1;
    charIdx['i'] = 2;
    charIdx['o'] = 3;
    charIdx['u'] = 4;
    maskPos[0] = -1;

    for(char c : s)
    {
        if(isVowel(c))
            vowelMask ^= (1 << charIdx[c]);
        if(maskPos.count(vowelMask))
            maxLen = max(maxLen, pos++ - maskPos[vowelMask]);
        else maskPos[vowelMask] = pos++;
    }

    return maxLen;
}

// DAY 16 (539. Minimum Time Difference)======================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int getMinutes(string &time)
{
    return ((time[0]-'0') * 10 + (time[1]-'0')) * 60 + (time[3]-'0') * 10 + (time[4]-'0');
}

int findMinDifference(vector<string>& timePoints)
{
    int size = timePoints.size();
    vector<int> minutePoints;
    for(string time : timePoints)
        minutePoints.push_back(getMinutes(time));
    sort(minutePoints.begin(), minutePoints.end());

    int minDiff = 1439 - minutePoints.back() + minutePoints[0] + 1;
    for(int idx = 0; idx < minutePoints.size()-1; idx++)
        minDiff = min(minDiff, minutePoints[idx+1] - minutePoints[idx]);
    
    return minDiff;
}

// DAY 17 (884. Uncommon Words from Two Sentences)============================================================

// Time Complexty = O(n + m)
// Space Complexty = O(n + m)

vector<string> uncommonFromSentences(string s1, string s2)
{
    stringstream ss1(s1), ss2(s2);
    string token;
    unordered_map<string,int> wordCnt;
    vector<string> ans;
    while(getline(ss1, token, ' '))
        wordCnt[token]++;
    while(getline(ss2, token, ' '))
        wordCnt[token]++;
    for(auto pair : wordCnt)
        if(pair.second == 1)
            ans.push_back(pair.first);
    return ans;
}

// DAY 18 (179. Largest Number)=============================================================================

// Time Complexity = O(n + (n+m)*log(n+m)*m + n)
// Space Complexity = O(n)

string largestNumber(vector<int>& nums)
{
    string ans = "";
    vector<string> numStrs;
    for(int num : nums)
        numStrs.push_back(to_string(num));
    sort(numStrs.begin(), numStrs.end(), [](auto const &a, auto const &b){
        return (a + b) > (b + a);
    });
    if(numStrs[0] == "0")
        return "0";
    for(string str : numStrs)
        ans += str;

    return ans;
}

// DAY 19 (241. Different Ways to Add Parentheses)===================================================================

// Time Complexity = O(n^n)
// Space Complexity = O(n^n)

vector<int> diffWaysToCompute(string expression)
{
    vector<int> ans;
    for(int idx = 0; idx < expression.size(); idx++)
    {
        char c = expression[idx];
        if(c == '+' || c == '-' || c == '*')
        {
            vector<int> lans = diffWaysToCompute(expression.substr(0, idx));
            vector<int> rans = diffWaysToCompute(expression.substr(idx+1));

            for(int num1 : lans)
            {
                for(int num2 : rans)
                {
                    if(c == '+')
                        ans.push_back(num1 + num2);
                    else if(c == '-')
                        ans.push_back(num1 - num2);
                    else if(c == '*')
                        ans.push_back(num1 * num2);
                }
            }
        }
    }
    if(ans.empty())
        ans.push_back(stoi(expression));
    return ans;
}
