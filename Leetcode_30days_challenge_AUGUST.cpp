// Day 1 (Detect Capital)===========================================

bool detectCapitalUse(string word)
{
    int count = 0;
    for (char w : word)
        if (isupper(w))
            count++;
    return ((isupper(word[0]) && count == 1) || (count == word.size()) || count == 0);
}