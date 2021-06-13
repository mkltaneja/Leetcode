
bool mergeTriplets(vector<vector<int>> &triplets, vector<int> &target)
{
    bool f0 = false, f1 = false, f2 = false;
    for (int i = 0; i < triplets.size(); i++)
    {
        if (triplets[i][0] == target[0] && triplets[i][1] <= target[1] && triplets[i][2] <= target[2])
            f0 = true;
        if (triplets[i][1] == target[1] && triplets[i][0] <= target[0] && triplets[i][2] <= target[2])
            f1 = true;
        if (triplets[i][2] == target[2] && triplets[i][1] <= target[1] && triplets[i][0] <= target[0])
            f2 = true;
    }
    return (f0 && f1 && f2);
}