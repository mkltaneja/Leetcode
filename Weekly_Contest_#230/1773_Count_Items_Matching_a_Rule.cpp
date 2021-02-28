
int countMatches(vector<vector<string>> &items, string ruleKey, string ruleValue)
{
    int count = 0;
    int key = (ruleKey == "type") ? 0 : ((ruleKey == "color") ? 1 : 2);

    for (auto v : items)
        if (v[key] == ruleValue)
            count++;
    return count;
}