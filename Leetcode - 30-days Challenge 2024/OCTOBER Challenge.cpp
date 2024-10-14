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
