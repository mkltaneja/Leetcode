
int findFinalValue(vector<int> &nums, int original)
{
    unordered_set<int> s;
    for (int x : nums)
        s.insert(x);
    while (s.count(original))
        original *= 2;

    return original;
}