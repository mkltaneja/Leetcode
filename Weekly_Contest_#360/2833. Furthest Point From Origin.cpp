class Solution {
public:
    int furthestDistanceFromOrigin(string moves) 
    {
        int u = 0, x = 0;
        for(char c : moves)
        {
            if(c == '_')
            {
                u++;
                continue;
            }
            x += (c == 'L')? -1 : 1;
        }
        return abs(x) + u;
    }
};
