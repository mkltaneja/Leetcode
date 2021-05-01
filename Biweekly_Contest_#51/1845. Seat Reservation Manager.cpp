class SeatManager
{
public:
    set<int> v;
    SeatManager(int n)
    {
        for (int i = 1; i <= n; i++)
            v.insert(i);
    }

    int reserve()
    {
        int x = *v.begin();
        v.erase(x);
        return x;
    }

    void unreserve(int seatNumber)
    {
        v.insert(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */