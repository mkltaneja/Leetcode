class StockPrice
{
public:
    unordered_map<int, int> m;
    map<int, int> s;
    int lat = 0, latt = 0;
    StockPrice() {}

    void update(int timestamp, int price)
    {
        if (latt <= timestamp)
        {
            latt = timestamp;
            lat = price;
        }
        if (m.count(timestamp))
            if (--s[m[timestamp]] == 0)
                s.erase(m[timestamp]);
        s[price]++;
        m[timestamp] = price;
    }

    int current()
    {
        return lat;
    }

    int maximum()
    {
        auto itr = s.end();
        itr--;
        return (itr->first);
    }

    int minimum()
    {
        return (s.begin()->first);
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */