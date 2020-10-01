
// METHOD 1 (Using vector)

class RecentCounter {
public:
    
    vector<int> time;
    int i;
    
    RecentCounter() 
    {
        this->i = 0;
    }
    
    int ping(int t) 
    {
        time.push_back(t);
        while(time[i] < time.back() - 3000)
            i++;
        return time.size() - i;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */