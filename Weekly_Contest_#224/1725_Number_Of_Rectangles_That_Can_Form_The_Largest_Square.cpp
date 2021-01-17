
int countGoodRectangles(vector<vector<int>> &rectangles)
{
    int maxlen = 0;
    for (auto p : rectangles)
        maxlen = max(maxlen, min(p[0], p[1]));
    int count = 0;
    for (auto p : rectangles)
        if (min(p[0], p[1]) == maxlen)
            count++;
    return count;
}