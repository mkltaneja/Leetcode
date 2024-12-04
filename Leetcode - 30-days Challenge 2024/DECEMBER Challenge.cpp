
// DAY 1 (1346. Check If N and Its Double Exist)=====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool checkIfExist(vector<int>& arr) {
    unordered_set<int> numSet;
    for(int num : arr) {
        if(numSet.count(num * 2) || ((num & 1 ^ 1) && (numSet.count(num >> 1))))
            return true;
        numSet.insert(num);
    }
    return false;
}

// DAY 2 (1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence)================================================

// Time Complexity = O(count(words) * searchWord.size())
// Space Complexity = O(sentence.size())

int isPrefixOfWord(string sentence, string searchWord) {
    stringstream ss(sentence);
    string word;
    int index = 1;
    while(getline(ss, word, ' ')) {
        if(word.size() >= searchWord.size() && word.substr(0, searchWord.size()) == searchWord) {
            return index;
        }
        index++;
    }
    return -1;
}

// DAY 3 (2109. Adding Spaces to a String)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string addSpaces(string s, vector<int>& spaces) {
    string ans = "";
    for(int sidx = 0, arrIdx = 0; sidx < s.size(); sidx++) {
        if(arrIdx < spaces.size() && sidx == spaces[arrIdx]) {
            ans += " ";
            arrIdx++;
        }
        ans += s[sidx];
    }
    return ans;
}

// DAY 4 (2825. Make String a Subsequence Using Cyclic Increments)===============================================

// Time Complexity = O(min(n, m))
// Space Complexity = O(1)

char getNext(char c) {
    return char((((c - 'a') + 1) % 26) + 'a');
}

bool canMakeSubsequence(string str1, string str2) {
    int size1 = str1.size(), size2 = str2.size();
    if(size2 > size1) {
        return false;
    }
    int idx1 = 0, idx2 = 0;
    while(idx1 < str1.size() && idx2 < str2.size()) {
        if(str2[idx2] == str1[idx1] || str2[idx2] == getNext(str1[idx1])) {
            idx2++;
        }
        idx1++;
    }
    return idx2 == str2.size();
}
