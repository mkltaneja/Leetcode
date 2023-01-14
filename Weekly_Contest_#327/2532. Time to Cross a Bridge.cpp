class Solution {
public:
    
    #define LEFT  0
    #define RIGHT 1
    
    int findCrossingTime(int n, int k, vector<vector<int>>& time) 
    {
        priority_queue<vector<int>> waiting, ready;
        
        // waiting priority => time, side, effeciency, index
        // ready priority => side, effeciency, index
        
        for(int i = 0; i < k; i++)
            waiting.push({0, LEFT, time[i][0] + time[i][2], i});
        
        int currTime = 0;
        int rem = n;
        while(n)
        {
            if(ready.empty() && currTime < -waiting.top()[0])
                currTime = -waiting.top()[0];
            while(!waiting.empty() && currTime >= -waiting.top()[0])
            {
                vector<int> worker = waiting.top();
                waiting.pop();
                ready.push({worker[1], worker[2], worker[3]});
            }
            
            vector<int> worker = ready.top();
            ready.pop();
            int side = worker[0];
            int eff = worker[1];
            int i = worker[2];
            
            if(side == RIGHT)
            {
                n--;
                currTime += time[i][2];
                waiting.push({-(currTime + time[i][3]), side^1, eff, i});
            }
            else
            {
                if(rem == 0) continue;
                else rem--;
                currTime += time[i][0];
                waiting.push({-(currTime + time[i][1]), side^1, eff, i});
            }
        }
        
        return currTime;
    }
};
