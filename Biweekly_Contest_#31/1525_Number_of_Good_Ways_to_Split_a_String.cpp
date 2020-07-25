
// O(n)
int numSplits(string s)
{
    unordered_map<char, int> countl;
    unordered_map<char, int> countr;
    // cout<<countl.size()<<" "<<countr.size()<<endl;

    for (char c : s)
        countr[c]++;

    int count = 0;
    for (char c : s)
    {
        countl[c]++;
        countr[c]--;
        if (countr[c] == 0)
            countr.erase(c);
        // cout<<countl.size()<<" "<<countr.size()<<endl;
        if (countl.size() == countr.size())
            count++;
    }
    // cout<<endl;
    return count;
}