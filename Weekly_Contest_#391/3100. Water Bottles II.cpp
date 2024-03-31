
// Time Complexity = O(sqrt(numBottles) - sqrt(numExchange))
// Space Complexity = O(1)

class Solution {
public:
    int maxBottlesDrunk(int numBottles, int numExchange) 
    {
        int ans = 0, empty = 0;
        while(numBottles > 0)
        {
            ans += numBottles;
            empty += numBottles;
            numBottles = 0;
            while(empty >= numExchange)
            {
                empty -= numExchange++;
                numBottles++;
            }
        }
        return ans;
    }
};
