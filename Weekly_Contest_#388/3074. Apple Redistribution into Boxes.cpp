
// Time Complexity = O(n + m*logm + m)
// Space Complexity = O(1)

class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) 
    {
        int ta = 0;
        for(int x : apple)
            ta += x;
        sort(capacity.rbegin(), capacity.rend());
        
        int i = 0;
        while(i < capacity.size() && ta > 0)
            ta -= capacity[i++];
        
        return i;
    }
};
