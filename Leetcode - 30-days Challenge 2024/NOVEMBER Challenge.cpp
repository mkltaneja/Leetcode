
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
