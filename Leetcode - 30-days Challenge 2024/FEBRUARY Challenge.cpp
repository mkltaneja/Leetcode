
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

// DAY 10 (647. Palindromic Substrings)===========================================================================

// Time Complexity = O(n*n)
// Space Complexity = O(1)

int countSubstrings(string s)
{
    int size = s.size();
    int totalPalStrings = 0;
    for(int center = 0; center < size; )
    {
        int itr = center;
        while(itr < size && s[itr] == s[center]) itr++;

        int countEqual = itr - center;
        totalPalStrings += countEqual * (countEqual + 1) / 2;

        int left = center - 1, right = itr, countBoundary = 0;
        while(left >= 0 && right < size && s[left--] == s[right++])
            countBoundary++;

        totalPalStrings += countBoundary;
        center = itr;
    }

    return totalPalStrings;
}

// WEEK 2 (276. Paint Fence)=====================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numWays(int n, int k)
{
    if(n <= 1) return n == 0? 0 : k;

    int last2diff = k * (k - 1), last2same = k;
    for(int fence = 3; fence <= n; fence++)
    {
        int temp = last2diff;
        last2diff = (last2diff + last2same) * (k - 1);
        last2same = temp;
    }
    return last2diff + last2same;
}

// DAY 11 (1463. Cherry Pickup II)==============================================================================

// Time Complexity = O(n * m * m * 9)
// Space Complexity = O(n * m * m)

int cherryPickupTabulation(vector<vector<int>> &cherries)
{
    int rows = cherries.size(), cols = cherries[0].size();
    vector<vector<vector<int>>> stateCache(rows, vector<vector<int>>(cols, vector<int>(cols, 0)));
    for(int row = rows-1; row >= 0; row--)
    {
        for(int col1 = 0; col1 < cols; col1++)
        {
            for(int col2 = col1; col2 < cols; col2++)
            {
                int maxCherries = 0;
                for(int d1 = -1; d1 <= 1; d1++)
                {
                    for(int d2 = -1; d2 <= 1; d2++)
                    {
                        if(row + 1 == rows || col1 + d1 == -1 || col1 + d1 == cols || col2 + d2 == -1 || col2 + d2 == cols)
                            continue;
                        maxCherries = max(maxCherries, stateCache[row+1][col1 + d1][col2 + d2]);
                    }
                }
                stateCache[row][col1][col2] = maxCherries + (col1 == col2? cherries[row][col1] : cherries[row][col1] + cherries[row][col2]);
            }
        }
    }

    return stateCache[0][0][cols-1];
}

int cherryPickup(vector<vector<int>> &grid)
{
    return cherryPickupTabulation(grid);
}

// DAY 12 (169. Majority Element)==================================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int majorityElement(vector<int>& nums) 
{
    int majNum = nums[0], majNumFreq = 1;
    for(int idx = 1; idx < nums.size(); idx++)
    {
        if(nums[idx] == majNum)
            majNumFreq++;
        else if(--majNumFreq == 0)
            majNum = nums[idx], majNumFreq = 1;
    }
    return majNum;
}

// DAY 13 (2108. Find First Palindromic String in the Array)=================================================================================

bool isPalindrome(string &word)
{
    int left = 0, right = word.size()-1;
    while(left < right && word[left] == word[right])
        left++, right--;
    return left >= right;
}

string firstPalindrome(vector<string> &words)
{
    for(string word : words)
        if(isPalindrome(word))
            return word;
    return "";
}

// DAY 14 (2149. Rearrange Array Elements by Sign)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> rearrangeArray(vector<int> &nums)
{
    int size = nums.size();
    vector<int> modifiedArray(size);
    for(int idx = 0, posIdx = 0, negIdx = 1; idx < size; idx++)
    {
        int num = nums[idx];
        if(num > 0)
        {
            modifiedArray[posIdx] = num;
            posIdx += 2;
        }
        else
        {
            modifiedArray[negIdx] = num;
            negIdx += 2;
        }
    }
    return modifiedArray;
}

// DAY 15 (2971. Find Polygon With the Largest Perimeter)=================================================================================

// Time Complexity = O(n*logn + 2*n)
// Space Complexity = O(n)

#define ll long long
long long largestPerimeter(vector<int> &nums)
{
    int size = nums.size();
    vector<ll> prefSum(size);

    sort(nums.begin(), nums.end());
    for(int idx = 0; idx < size; idx++)
        prefSum[idx] += nums[idx] + (idx? prefSum[idx-1] : 0);
    
    for(int idx = size-1; idx >= 2; idx--)
        if(prefSum[idx-1] > nums[idx])
            return prefSum[idx];
    return -1;
}

// DAY 16 (1481. Least Number of Unique Integers after K Removals)===========================================================================

// Time Complexity = O(2*n*logn + 2*n)
// Space Complexity = O(n)

int findLeastNumOfUniqueInts(vector<int>& arr, int k) 
{
    int size = arr.size();
    vector<int> freqs;

    sort(arr.begin(), arr.end());
    for(int idx = 0; idx < size; )
    {
        int idx1 = idx + 1;
        while(idx1 < size && arr[idx1] == arr[idx])
            idx1++;
        freqs.push_back(idx1 - idx);
        idx = idx1;
    }
    sort(freqs.rbegin(), freqs.rend());

    while(!freqs.empty() && k && freqs.back() <= k)
    {
        k -= freqs.back();
        freqs.pop_back();
    }

    return freqs.size();
}

// DAY 17 (1642. Furthest Building You Can Reach)=================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

int furthestBuilding(vector<int>& heights, int bricks, int ladders)
{
    int size = heights.size();
    priority_queue<int> maxHeightBricks;
    for(int building = 0; building < size-1; building++)
    {
        int heightDiff = heights[building+1] - heights[building];
        if(heightDiff <= 0)
            continue;
        if(bricks >= heightDiff)
        {
            bricks -= heightDiff;
            maxHeightBricks.push(heightDiff);
            continue;
        }
        if(ladders == 0) return building;
        if(!maxHeightBricks.empty() && maxHeightBricks.top() > heightDiff)
        {
            bricks += maxHeightBricks.top() - heightDiff;
            maxHeightBricks.pop();
            maxHeightBricks.push(heightDiff);
        }
        ladders--;
    }
    
    return size-1;
}

// DAY 18 (2402. Meeting Rooms III)=================================================================================

// Time Complexity = O(n + m * (2*logn))
// Space Complexity = O(3*n)

#define ll long long
int mostBooked(int n, vector<vector<int>> &meetings)
{
    int size = meetings.size();
    int maxUsedCount = 0, minRoomNum = n;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<pair<ll,int>>> endTimePq;
    priority_queue<int, vector<int>, greater<int>> roomPq;
    vector<int> roomUsedCount(n, 0);

    sort(meetings.begin(), meetings.end());
    for(int room = 0; room < n; room++)
        roomPq.push(room);
    
    for(vector<int> &meeting : meetings)
    {
        ll startTime = meeting[0];
        ll endTime = meeting[1];
        
        while(!endTimePq.empty() && endTimePq.top().first <= startTime)
        {
            roomPq.push(endTimePq.top().second);
            endTimePq.pop();
        }
        if(roomPq.empty())
        {
            ll waitTime = endTimePq.top().first - startTime;
            endTime = endTime + waitTime;
            roomPq.push(endTimePq.top().second);
            endTimePq.pop();
        }
        int currRoom = roomPq.top();
        endTimePq.push({endTime, currRoom});
        roomPq.pop();

        if(++roomUsedCount[currRoom] > maxUsedCount)
        {
            maxUsedCount = roomUsedCount[currRoom];
            minRoomNum = currRoom;
        }
        else if(roomUsedCount[currRoom] == maxUsedCount)
            minRoomNum = min(minRoomNum, currRoom);
    }

    return minRoomNum;
}

// DAY 19 (231. Power of Two)======================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)


bool isPowerOfTwo(int n) 
{
    return n > 0 && (n & (n-1)) == 0;
}

// DAY 20 (268. Missing Number)=============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int missingNumber(vector<int> &nums)
{
    int size = nums.size();
    int totalSum = 0;
    int sumOfFirstN = size * (size + 1) / 2;
    for(int num : nums)
        totalSum += num;
    int missingNumber = sumOfFirstN - totalSum;

    return missingNumber;
}

// DAY 21 (201. Bitwise AND of Numbers Range)===============================================================================

// METHOD 1 (Traversing on every bit from MSB to LSB)

// Time Complexity = O(32)
// Space Complexity = O(1)

int rangeBitwiseAnd(int left, int right)
{
    int andAns = 0;
    bool shouldCheckFurther = true;
    for(int bit = 30; bit >= 0 && shouldCheckFurther; bit--)
    {
        int mask = (1 << bit);
        if(!(right & mask))
            continue;
        int lastOnPos = right / mask * mask;
        if(lastOnPos <= left)
            andAns |= mask;
        else shouldCheckFurther = false;
    }
    return andAns;
}

// METHOD 2 (Removing the unequal part from left and right)

// Time Complexity = O(log(left))
// Space Complexity = O(1)

int rangeBitwiseAnd(int left, int right)
{
    int andAns = 0;
    int shifts = 0;
    while(left != right)
    {
        left >>= 1;
        right >>= 1;
        shifts++;
    }
    andAns = left << shifts;
    return andAns;
}

// DAY 22 (997. Find the Town Judge)==================================================================================

// Time Complexity = O(m + n)
// Space Complexity = O(n)

int findJudge(int n, vector<vector<int>> &trust)
{
    vector<int> trustCount(n+1);
    for(vector<int> &pair : trust)
    {
        trustCount[pair[0]]--;
        trustCount[pair[1]]++;
    }
    
    for(int person = 1; person <= n; person++)
        if(trustCount[person] == n-1)
            return person;
    
    return -1;
}

// DAY 23 (787. Cheapest Flights Within K Stops)=================================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dest, int k)
{
    vector<vector<vector<int>>> graph(n);
    queue<vector<int>> priceQue;
    vector<int> minPrice(n, INT_MAX);
    minPrice[src] = 0;
    for(vector<int> &flight : flights)
        graph[flight[0]].push_back({flight[1], flight[2]});
    priceQue.push({0, 0, src}); // {price, level, city}

    while(!priceQue.empty())
    {
        int priceSf = priceQue.front()[0];
        int stops = priceQue.front()[1];
        int srcCity = priceQue.front()[2];
        priceQue.pop();
        
        for(vector<int> destCity : graph[srcCity])
        {
            int newPrice = priceSf + destCity[1];
            int newStops = stops + (destCity[0] != dest);
            if(minPrice[destCity[0]] > newPrice && newStops <= k)
            {
                minPrice[destCity[0]] = newPrice;
                priceQue.push({newPrice, newStops, destCity[0]});
            }
        }
    }
    return minPrice[dest] == INT_MAX? -1 : minPrice[dest];
}

// DAY 24 (2092. Find All People With Secret)======================================================================

// Time Complexity = O(n + m*logm + m)
// Space Complexity = O(2*n)

class DSU
{
    int size;
    vector<int> parent;
    public:
    DSU(int size)
    {
        this->size = size;
        this->parent.resize(size);
        for(int node = 0; node < size; node++)
            this->parent[node] = node;
    }

    void setParent(int node, int parent)
    {
        this->parent[node] = parent;
    }

    int findParent(int node)
    {
        return this->parent[node] = (this->parent[node] == node)? node : findParent(this->parent[node]);
    }

    void merge(int node1, int node2, vector<int> &knowsSecret)
    {
        int parent1 = findParent(node1);
        int parent2 = findParent(node2);
        if(parent1 == parent2)
            return;

        int secretValue = knowsSecret[parent1] | knowsSecret[parent2];
        knowsSecret[parent1] = secretValue;
        knowsSecret[parent2] = secretValue;
        
        parent[parent1] = parent2;
    }
};

static bool sortByTime(vector<int> &meeting1, vector<int> &meeting2)
{
    return meeting1[2] < meeting2[2];
}

vector<int> findAllPeople(int n, vector<vector<int>> &meetings, int firstPerson)
{
    int size = meetings.size();
    vector<int> knowsSecret(n);
    knowsSecret[0] = 1;
    knowsSecret[firstPerson] = 1;
    vector<int> finalPeople;
    DSU dsu(n);
    sort(meetings.begin(), meetings.end(), sortByTime);

    for(int idx = 0; idx < size; )
    {
        int currTime = meetings[idx][2];
        int itr = idx;
        while(itr < size && meetings[itr][2] == currTime)
        {
            int person1 = meetings[itr][0];
            int person2 = meetings[itr][1];

            dsu.merge(person1, person2, knowsSecret);
            itr++;
        }
        itr = idx;
        while(itr < size && meetings[itr][2] == currTime)
        {
            int person1 = meetings[itr][0];
            int person2 = meetings[itr][1];
            int parent = dsu.findParent(person1);
            
            knowsSecret[person1] |= knowsSecret[parent];
            knowsSecret[person2] |= knowsSecret[parent];
            itr++;
        }
        itr = idx;
        while(itr < size && meetings[itr][2] == currTime)
        {
            int person1 = meetings[itr][0];
            int person2 = meetings[itr][1];

            dsu.setParent(person1, person1);
            dsu.setParent(person2, person2);
            itr++;
        }
        idx = itr;
    }

    for(int person = 0; person < n; person++)
        if(knowsSecret[person])
            finalPeople.push_back(person);

    return finalPeople;
}
