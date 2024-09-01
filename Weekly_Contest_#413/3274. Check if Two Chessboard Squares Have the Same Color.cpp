
// Time Complexity = O(1)
// Space Complexity = O(1)

class Solution {
public:
    bool checkTwoChessboards(string coordinate1, string coordinate2)
    {
        int p1 = (coordinate1[0] - 'a' + 1) & 1;
        int p2 = (coordinate1[1] - '1' + 1) & 1;
        int p3 = (coordinate2[0] - 'a' + 1) & 1;
        int p4 = (coordinate2[1] - '1' + 1) & 1;
        
        if(((p1 ^ p2) == 0 && (p3 ^ p4) == 0) || ((p1 ^ p2) == 1 && (p3 ^ p4) == 1))
            return true;
        return false;
    }
};
