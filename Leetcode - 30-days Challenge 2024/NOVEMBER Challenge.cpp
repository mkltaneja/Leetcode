
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
