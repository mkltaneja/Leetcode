class Solution {
public:
    
    int gcd(int x, int y)
    {
        while(y)
        {
            int z = x % y;
            x = y;
            y = z;
        }
        
        return x;
    }
    
    bool isReachable(int targetX, int targetY) 
    {
        while(targetX % 2 == 0) targetX >>= 1;
        while(targetY % 2 == 0) targetY >>= 1;
        
        return gcd(targetX, targetY) == 1;
    }
};
