class Solution {
public:
    
    int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f) 
    {
        int ta = a, tb = b, tc = c, td = d;
        while(ta < 8 && !(ta == c && b == d) && !(ta == e && b == f))
            ta++;
        if(ta == e && b == f)
            return 1;
        ta = a;
        while(ta >= 0 && !(ta == c && b == d) && !(ta == e && b == f))
            ta--;
        if(ta == e && b == f)
            return 1;
        
        while(tb < 8 && !(a == c && tb == d) && !(a == e && tb == f))
            tb++;
        if(a == e && tb == f)
            return 1;
        tb = b;
        while(tb >= 0 && !(a == c && tb == d) && !(a == e && tb == f))
            tb--;
        if(a == e && tb == f)
            return 1;
        
        while(tc < 8 && td < 8 && !(tc == a && td == b) && !(tc == e && td == f))
            tc++, td++;
        if(tc == e && td == f)
            return 1;
        tc = c, td = d;
        while(tc < 8 && td >= 0 && !(tc == a && td == b) && !(tc == e && td == f))
            tc++, td--;
        if(tc == e && td == f)
            return 1;
        
        tc = c, td = d;
        while(tc >= 0 && td < 8 && !(tc == a && td == b) && !(tc == e && td == f))
            tc--, td++;
        if(tc == e && td == f)
            return 1;
        tc = c, td = d;
        while(tc >= 0 && td >= 0 && !(tc == a && td == b) && !(tc == e && td == f))
            tc--, td--;
        if(tc == e && td == f)
            return 1;
        
        return 2;
    }
};
