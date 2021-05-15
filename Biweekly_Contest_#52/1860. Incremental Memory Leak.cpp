
vector<int> memLeak(int memory1, int memory2)
{
    int t = 1;
    while (t <= max(memory1, memory2))
    {
        if (memory1 >= memory2)
            memory1 -= t;
        else
            memory2 -= t;
        t++;
    }
    return {t, memory1, memory2};
}