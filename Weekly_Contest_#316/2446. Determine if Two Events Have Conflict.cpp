// APPROACH 1 (Creating minutes array)

class Solution {
public:
    
    int mins[25];
    int minn(int h, int m)
    {
        return mins[h] + m;
    }
    
    bool haveConflict(vector<string>& event1, vector<string>& event2) 
    {
        int hs1 = stoi(event1[0].substr(0,2));
        int ms1 = stoi(event1[0].substr(3,2));
        int he1 = stoi(event1[1].substr(0,2));
        int me1 = stoi(event1[1].substr(3,2));
        
        int hs2 = stoi(event2[0].substr(0,2));
        int ms2 = stoi(event2[0].substr(3,2));
        int he2 = stoi(event2[1].substr(0,2));
        int me2 = stoi(event2[1].substr(3,2));
        
        // mins[0] = 0;
        for(int i = 1; i < 25; i++)
            mins[i] = i*60 + mins[i-1];
        
        int arrive = max(minn(hs1, ms1), minn(hs2, ms2));
        int dep = min(minn(he1, me1), minn(he2, me2));
        
        int tot = dep - arrive + 1;
        return tot > 0;
    }
};

// APPROACH 2 (Mathematically)

class Solution {
public:
    
    int time(string t)
    {
        return (t[0]-'0')*1000 + (t[1]-'0')*100 + (t[3]-'0')*10 + (t[4]-'0');
    }
    
    bool haveConflict(vector<string>& event1, vector<string>& event2) 
    {
        return max(time(event1[0]), time(event2[0])) <= min(time(event1[1]), time(event2[1]));
    }
};
