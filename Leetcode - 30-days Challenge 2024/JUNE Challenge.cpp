
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
