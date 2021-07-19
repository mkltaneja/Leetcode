
int numRabbits(vector<int> &answers)
{
    unordered_map<int, int> m;
    for (int x : answers)
        m[x]++;
    int groups = 0;
    for (auto p : m)
        groups += ceil(1.0 * p.second / (p.first + 1)) * (p.first + 1);
    return groups;
}