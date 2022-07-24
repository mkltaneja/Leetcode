class NumberContainers
{
public:
    unordered_map<int, set<int>> mpn;
    unordered_map<int, int> mpi;
    NumberContainers()
    {
    }

    void change(int index, int number)
    {
        if (mpi.count(index))
            mpn[mpi[index]].erase(index);
        mpn[number].insert(index);
        mpi[index] = number;
    }

    int find(int number)
    {
        if (!mpn.count(number) || mpn[number].empty())
            return -1;

        return *mpn[number].begin();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */