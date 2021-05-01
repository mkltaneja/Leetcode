
// APPROACH 1(Using set) --> O(n*logn)
// AC

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

// APPROACH 2 (Using vector) --> O(n^2)
// TLE
class SeatManager
{
public:
    int focc;
    vector<int> v;
    SeatManager(int n)
    {
        focc = 0;
        v.assign(n + 1, 0);
    }

    int reserve()
    {
        for (int i = focc + 1; i < v.size(); i++)
        {
            if (v[i] == 0)
            {
                v[i] = 1;
                return focc = i;
            }
        }
        return -1;
    }

    void unreserve(int seatNumber)
    {
        v[seatNumber] = 0;
        focc = min(focc, seatNumber - 1);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */