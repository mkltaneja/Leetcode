class Solution {
public:
    int passThePillow(int n, int time) 
    {
        int x = 1, y = 1;
        while(time--)
        {
            if(x == n) y = -1;
            else if(x == 1) y = 1;
            x += y;
        }
        
        return x;
    }
};
