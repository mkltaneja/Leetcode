// $ DAY 1 (Number of Recent Calls)==========================================================

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

////////////////////////////////////////////////////////OR//////////////////////////////////////////

// METHOD 2 (Using queue)
// Memory optimized
class RecentCounter {
public:
    
    queue<int> time;
    int qsize;
    
    RecentCounter() 
    {
        this->qsize = 0;
    }
    
    int ping(int t) 
    {
        time.push(t);
        qsize++;
        while(time.front() < t - 3000)
        {
            time.pop();
            qsize--;
        }
        return qsize;
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */