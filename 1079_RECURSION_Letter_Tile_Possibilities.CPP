// this approach continuously cuts the strings, which is O(n) operation; so time comlexity will be :--
// O(n^2)
int numTilePossibilities(string tiles)
{
    if (tiles.size() == 0)
        return 0;
    int n = tiles.size();
    int vis = 0;
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int mask = 1 << (tiles[i] - 'A');
        if ((vis & mask) == 0)
        {
            vis ^= mask;
            count += numTilePossibilities(tiles.substr(0, i) + tiles.substr(i + 1)) + 1;
        }
    }
    return count;
}

///////////////OR///////////////
//by using array, instead of cutting the string
// O(n)
// --> We mark 1 on the index of the encountered character upon caling and mark back it 0 while returning