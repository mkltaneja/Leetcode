// APPROACH 1 (Brute Force)

class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) 
    {
        int ma1 = stoi(arriveAlice.substr(0,2));
        int da1 = stoi(arriveAlice.substr(3));
        int ma2 = stoi(leaveAlice.substr(0,2));
        int da2 = stoi(leaveAlice.substr(3));
        
        int mb1 = stoi(arriveBob.substr(0,2));
        int db1 = stoi(arriveBob.substr(3));
        int mb2 = stoi(leaveBob.substr(0,2));
        int db2 = stoi(leaveBob.substr(3));
        
        int mp[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        
        int ans = 0;
        if(mb1 <= ma2 && mb1 >= ma1)
        {
            if(mb1 == ma2 && db1 > da2) return 0;
            int st = ma1 == mb1? max(da1, db1) : db1;
            for(int i = mb1; i <= min(ma2, mb2); i++)
            {
                int curr = 0;
                if(i != ma2 && i != mb2) 
                    curr = mp[i];
                else if(i == ma2 && i == mb2) 
                    curr = min(da2, db2);
                else if(i == ma2)
                    curr = da2;
                else curr = db2;
                ans += curr - st + 1;
                st = 1;
            }
        }
        else if(ma1 <= mb2 && ma1 >= mb1)
        {
            if(ma1 == mb2 && da1 > db2) return 0;
            int st = ma1 == mb1? max(da1, db1) : da1;
            for(int i = ma1; i <= min(ma2, mb2); i++)
            {
                int curr = 0;
                if(i != ma2 && i != mb2) 
                    curr = mp[i];
                else if(i == ma2 && i == mb2) 
                    curr = min(da2, db2);
                else if(i == ma2)
                    curr = da2;
                else curr = db2;
                ans += curr - st + 1;
                st = 1;
            }
        }
        
        return ans;
    }
};
