
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
