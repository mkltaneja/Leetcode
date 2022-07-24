
string bestHand(vector<int> &ranks, vector<char> &suits)
{
    unordered_map<int, int> mpr;
    unordered_map<char, int> mps;
    for (int x : ranks)
        mpr[x]++;
    for (char x : suits)
        mps[x]++;

    if (mps.size() == 1)
        return "Flush";
    for (auto p : mpr)
        if (p.second >= 3)
            return "Three of a Kind";
    for (auto p : mpr)
        if (p.second == 2)
            return "Pair";

    return "High Card";
}