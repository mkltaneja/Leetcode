int countWords(vector<string> &words1, vector<string> &words2)
{
    unordered_map<string, int> m1, m2;
    for (string s : words1)
        m1[s]++;
    for (string s : words2)
        m2[s]++;

    int ans = 0;
    for (auto p : m1)
        if (p.second == 1 && m2[p.first] == p.second)
            ans++;
    return ans;
}