
// DAY 1 (1957. Delete Characters to Make Fancy String)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

string makeFancyString(string s) {
    int size = s.size();
    if(size < 3)
        return s;
    int prevItr = 2;
    for(int itr = 2; itr < size; itr++)
        if(s[itr] != s[prevItr-1] || s[itr] != s[prevItr-2])
            s[prevItr++] = s[itr];
    s.resize(prevItr);
    return s;
}

// DAY 2 (2490. Circular Sentence)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isCircularSentence(string sentence) {
    for(int idx = 0; idx < sentence.size(); idx++)
        if(sentence[idx] == ' ' && sentence[idx-1] != sentence[idx+1])
            return false;
    return sentence[0] == sentence.back();
}

// DAY 3 (796. Rotate String)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> getLpsArray(string &s) {
    vector<int> lps(s.size(), 0);
    int len = 0;
    for(int idx = 1; idx < s.size(); ) {
        if(s[idx] == s[len])
            lps[idx++] = ++len;
        else {
            if(len)
                len = len? lps[len-1] : 0;
            else idx++;
        }
    }
    return lps;
}

bool rotateString(string s, string goal) {
    if(s.size() != goal.size())
        return false;
    string kmpStr = goal + "#" + s + s;
    vector<int> lps = getLpsArray(kmpStr);
    for(int idx = 0; idx < lps.size(); idx++) {
        if(lps[idx] == goal.size())
            return true;
    }
    return false;
}

// DAY 4 (3163. String Compression III)===============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string compressedString(string word) {
    int size = word.size();
    string ans = "";
    for(int idx = 0; idx < size; ) {
        int idx2 = idx;
        while(idx2 < size && idx2 - idx + 1 <= 9 && word[idx2] == word[idx])
            idx2++;
        ans += to_string(idx2 - idx) + word[idx];
        idx = idx2;
    }
    return ans;
}

// DAY 5 (2914. Minimum Number of Changes to Make Binary String Beautiful)============================================================

// APPROACH 1 (Checking through odd-even segments)

// Time Complexity = O(n)
// Space Complexity = O(1)

int minChanges(string s) {
    int size = s.size();
    int prevEvens = 0, prevOdds = 0;
    int moves = 0;
    for(int idx = 0; idx < size; ) {
        int nextIdx = idx;
        while(nextIdx < size && s[nextIdx] == s[idx])
            nextIdx++;
        if((nextIdx - idx) & 1) {
            if(prevOdds) {
                moves += prevEvens + 1;
                prevOdds = 0;
            }
            else prevOdds++;
            prevEvens = 0;
        }
        else prevEvens++;

        idx = nextIdx;
    }
    return moves;
}

// APPROACH 2 (Checking in bubbles)

// Time Complexity = O(n)
// Space Complexity = O(1)

int minChanges(string s) {
    int moves = 0;
    for(int idx = 0; idx < s.size(); idx += 2)
        moves += s[idx] != s[idx+1];
    return moves;
}

// DAY 6 (3011. Find if Array Can Be Sorted)======================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

bool isSortedArray(int size, vector<int> &nums) {
    for(int idx = 1; idx < size; idx++)
        if(nums[idx] < nums[idx-1])
            return false;
    return true;
}

bool canSortArray(vector<int>& nums) {
    int size = nums.size();
    for(int idx = 0; idx < size; idx++) {
        int pidx = idx;
        int bits = __builtin_popcount(nums[idx]);
        while(idx + 1 < size && __builtin_popcount(nums[idx+1]) == bits)
            idx++;
        sort(nums.begin() + pidx, nums.begin() + idx + 1);
    }

    return isSortedArray(size, nums);
}

// DAY 7 (2275. Largest Combination With Bitwise AND Greater Than Zero)================================================

// Time Complexity = O(n*32)
// Space Complexity = O(32)

int largestCombination(vector<int>& candidates) {
    vector<int> bitCandidates(32);
    int largestCombination = 0;
    for(int candidate : candidates)
        for(int bit = 0; bit < 32; bit++)
            if(candidate & (1 << bit))
                bitCandidates[bit]++;

    for(int bit = 0; bit < 32; bit++)
        largestCombination = max(largestCombination, bitCandidates[bit]);
    return largestCombination;
}

// DAY 8 (1829. Maximum XOR for Each Query)================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getTotalXor(vector<int> &nums) {
    int res = 0;
    for(int num : nums)
        res ^= num;
    return res;
}

vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
    int size = nums.size();
    int totalXor = getTotalXor(nums);
    vector<int> ans(size);
    for(int idx = size-1; idx >= 0; idx--) {
        int k = ~totalXor & ((1 << maximumBit) - 1);
        ans[size - idx - 1] = k;
        totalXor ^= nums[idx];
    }
    return ans;
}

// DAY 9 ()===================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

#define ll long long
long long minEnd(int n, int x) {
    ll ans = x;
    n--;

    for(int xbit = 0, nbit = 0; xbit < 64; xbit++) {
        if(x & (1ll << xbit))
            continue;
        if(n & (1ll << (nbit++)))
            ans |= 1ll << xbit;
    }

    return ans;
}

// DAY 10 (3097. Shortest Subarray With OR at Least K II)===================================================

// Time Complexity = O(n*32)
// Space Complexity = O(32)

int minimumSubarrayLength(vector<int>& nums, int k) {
    int minLen = INT_MAX, currOr = 0;
    vector<int> bitCnt(32);
    for(int idx = 0, pidx = 0; idx < nums.size(); idx++) {
        currOr |= nums[idx];
        for(int bit = 0; bit < 32; bit++)
            bitCnt[bit] += (nums[idx] >> bit) & 1;
        while(pidx <= idx && currOr >= k) {
            minLen = min(minLen, idx - pidx + 1);
            for(int bit = 0; bit < 32; bit++) {
                bitCnt[bit] -= (nums[pidx] >> bit) & 1;
                if(bitCnt[bit] == 0)
                    currOr &= ~(1 << bit);
            }
            pidx++;
        }
    }
    return minLen == INT_MAX? -1 : minLen;
}
