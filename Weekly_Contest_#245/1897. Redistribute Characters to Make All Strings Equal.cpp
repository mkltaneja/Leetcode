
bool makeEqual(vector<string> &words)
{
    int n = words.size();
    vector<int> cnt(26, 0);
    for (string s : words)
        for (char c : s)
            cnt[c - 'a']++;
    for (int x : cnt)
        if (x % n != 0)
            return false;
    return true;
}