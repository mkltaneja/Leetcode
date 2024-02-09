
// DAY 1 (2966. Divide Array Into Arrays With Max Difference)===========================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<vector<int>> divideArray(vector<int> &nums, int k)
{
    int size = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    for(int idx = 0; idx+2 < size; idx+=3)
    {
        if(nums[idx+2] - nums[idx] > k)
            return {};
        ans.push_back({nums[idx], nums[idx+1], nums[idx+2]});
    }
    return ans;
}

// Week 1 (293. Flip Game)=================================================================================================

// APPROACH 1 (Altering the strings while adding)

// Time Complexity = O(n^2)
// Space Complexity = O(n)

vector<string> generatePossibleNextMoves(string currentState)
{
    vector<string> possibleStates;
    for(int idx = 0; idx+1 < currentState.size(); idx++)
    {
        if(currentState[idx] == '+' && currentState[idx+1] == '+')
        {
            string tempState = currentState;
            tempState[idx] = tempState[idx+1] = '-';
            possibleStates.push_back(tempState);
        }
    }

    return possibleStates;
}

// APPROACH 2 (Adding the indices first then changing the strings separately)

// Time Complexity = O(2*n)
// Space Complexity = O(2*n)

vector<string> generatePossibleNextMoves(string currentState)
{
    vector<int> possibleStatesIdx;
    for(int idx = 0; idx+1 < currentState.size(); idx++)
        if(currentState[idx] == '+' && currentState[idx+1] == '+')
            possibleStatesIdx.push_back(idx);

    vector<string> possibleStates(possibleStatesIdx.size(), currentState);
    for(int idx = 0; idx < possibleStatesIdx.size(); idx++)
    {
        int convertIdx = possibleStatesIdx[idx];
        possibleStates[idx][convertIdx] = '-';
        possibleStates[idx][convertIdx+1] = '-';
    }

    return possibleStates;
}

// DAY 2 (1291. Sequential Digits)=========================================================================================

// APPROACH 1

// Time Complexity = ((log10(high) + 1)^2 * ((9 + (9 - log10(high))) / 2)) - ((log10(low) + 1)^2 * ((9 + (9 - log10(low))) / 2))
// Space Complexity = O((log10(high) + 1) * ((9 + (9 - log10(high))) / 2))

vector<int> sequentialDigits(int low, int high)
{
    vector<int> ans;
    int lowDigs = log10(low) + 1;
    int highDigs = log10(high) + 1;
    for(int digs = lowDigs; digs <= highDigs; digs++)
    {
        for(int start = 1; start + digs - 1 <= 9; start++)
        {
            int num = 0;
            for(int dig = start, idx = 0; idx < digs; dig++, idx++)
                num = num*10 + dig;
            if(num >= low && num <= high)
                ans.push_back(num);
        }
    }
    return ans;
}

// APPROACH 2

// Time Complexity = O(9*9 + 9*9*log2(9*9))
// Space Complexity = O(9*9)

vector<int> sequentialDigits(int low, int high)
{
    vector<int> ans;
    for(int start = 1; start <= 9; start++)
    {
        for(int end = start, num = start; end <= 9 && num <= high; )
        {
            if(num >= low)
                ans.push_back(num);
            num = num*10 + ++end;
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// DAY 3 (1043. Partition Array for Maximum Sum)===================================================================================

// Time Complexity = O(n*k)
// Space Complexity = O(n)

int maxSumAfterPartitioning(vector<int> &arr, int k)
{
    int size = arr.size();
    vector<int> maxSumDP(size, 0);

    for(int idx1 = size-1; idx1 >= 0; idx1--)
    {
        int maxNum = 0, tot = 1;
        for(int idx2 = idx1; idx2 < size && tot <= k; idx2++, tot++)
        {
            maxNum = max(maxNum, arr[idx2]);
            int nextMaxSum = idx2 != size-1? maxSumDP[idx2 + 1] : 0;
            maxSumDP[idx1] = max(maxSumDP[idx1], maxNum*tot + nextMaxSum);
        }
    }
    return maxSumDP[0];
}

// DAY 4 (76. Minimum Window Substring)================================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(2*52)

string minWindow(string s, string t)
{
    int sSize = s.size();
    int tSize = t.size();
    unordered_map<char, int> sMap, tMap;
    int left = 0, right = 0, tRem = tSize;
    int minLen = sSize+1, start = -1;

    for(char c : t)
        tMap[c]++;

    while(right < sSize)
    {
        if(sMap[s[right]]++ < tMap[s[right]])
            tRem--;
        while(tRem == 0)
        {
            int currLen = right - left + 1;
            if(currLen < minLen)
                minLen = currLen, start = left;
            if(sMap[s[left]]-- == tMap[s[left]])
                tRem++;
            left++;
        }
        right++;
    }
    
    return start == -1? "" : s.substr(start, minLen);
}

// DAY 5 (387. First Unique Character in a String)==========================================================================

int firstUniqChar(string s)
{
    int size = s.size();
    vector<pair<int,int>> conf(26, {0, size});
    for(int idx = 0; idx < size; idx++)
    {
        conf[s[idx]-'a'].first++;
        conf[s[idx]-'a'].second = idx;
    }
    int minIdx = size;
    for(int idx = 0; idx < 26; idx++)
        if(conf[idx].first == 1)
            minIdx = min(minIdx, conf[idx].second);
    return minIdx == size? -1 : minIdx;
}

// DAY 6 (49. Group Anagrams)=====================================================================================

// Time Complexity = O(100*sqrt(100) + n*m)
// Space Complexity = O(26 + n*m)

const int MOD = 1e9 + 7;
bool isPrime(int num)
{
    for(int x = 2; x*x <= num; x++)
        if(num % x == 0)
            return false;
    return true;
}

vector<int> generateFirst26Primes()
{
    vector<int> primes;
    int num = 2;
    while(primes.size() < 26)
    {
        if(isPrime(num))
            primes.push_back(num);
        num++;
    }
    return primes;
}

int findHash(string inputString, vector<int> &primes)
{
    long long hashValue = 1;
    for(char c : inputString)
        hashValue = (hashValue % MOD * primes[c-'a'] % MOD) % MOD;
    return hashValue;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
    vector<int> primes = generateFirst26Primes();
    unordered_map<int, vector<string>> hashMap;
    vector<vector<string>> ans;
    for(string str : strs)
    {
        int hash = findHash(str, primes);
        hashMap[hash].push_back(str);
    }
    for(auto pair : hashMap)
        ans.emplace_back(pair.second.begin(), pair.second.end());
    return ans;
}

// DAY 7 (451. Sort Characters By Frequency)=================================================================================================

// Time Complexity = O(n + 52)
// Space Complexity = O(256)

string frequencySort(string s)
{
    string ans = "";
    vector<pair<int,char>> freqMap(256, {0, ' '});
    for(char c : s)
        freqMap[c-' '].first++, freqMap[c-' '].second = c;
    sort(freqMap.rbegin(), freqMap.rend());

    for(int idx = 0; idx < 256 && freqMap[idx].first; idx++)
        while(freqMap[idx].first--)
            ans += freqMap[idx].second;

    return ans;
}

// DAY 8 (279. Perfect Squares)===========================================================================================================

Time Complexity = O(sqrt(n) + n)
Space Complexity = O(sqrt(n) + n)

vector<int> findSquaresTilln(int n)
{
    vector<int> ans;
    for(int x = 1; x*x <= n; x++)
        ans.push_back(x*x);
    return ans;
}


int findMinAnsBFS(int n, vector<int> &squares)
{
    unordered_set<int> vis;
    queue<int> que;
    que.push(n);
    vis.insert(n);
    int numbersCount = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            int top = que.front();
            que.pop();
            if(top == 0)
                return numbersCount;
            for(int num : squares)
            {
                if(top-num == 0)
                    return numbersCount + 1;
                if(top-num > 0 && !vis.count(top-num))
                {
                    que.push(top - num);
                    vis.insert(top - num);
                }
            }
        }
        numbersCount++;
    }
    return numbersCount;
}

int numSquares(int n)
{
    vector<int> squares = findSquaresTilln(n);
    int minNumbers = findMinAnsBFS(n, squares);
    return minNumbers;
}

// DAY 9 (368. Largest Divisible Subset)=============================================================================================

// Time Complexity = O(n*logn + n^2)
// Space Complexity = O(2*n)

vector<int> largestDivisibleSubset(vector<int>& nums) 
{
    int size = nums.size();
    vector<int> nextMaxIdx(size, -1), maxCounts(size, 1);
    vector<int> ans;
    int maxCount = 0, maxIdx = -1;

    sort(nums.begin(), nums.end());

    for(int idx1 = size-1; idx1 >= 0; idx1--)
    {
        for(int idx2 = idx1+1; idx2 < size; idx2++)
        {
            if(nums[idx2] % nums[idx1] == 0 && maxCounts[idx2] + 1 > maxCounts[idx1])
            {
                maxCounts[idx1] = maxCounts[idx2] + 1;
                nextMaxIdx[idx1] = idx2;
            }
        }
        if(maxCounts[idx1] > maxCount)
        {
            maxCount = maxCounts[idx1];
            maxIdx = idx1;
        }
    }
    int currIdx = maxIdx;
    while(currIdx != -1)
    {
        ans.push_back(nums[currIdx]);
        currIdx = nextMaxIdx[currIdx];
    }
    return ans;
}
