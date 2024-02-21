
// Time Complexity = O(target * log(target) * log(target))
// Space Complexity = O(target * log(target))

class Solution {
public:
    int racecar(int target)
    {
        if(target == 0) return 0;

        queue<pair<int,int>> posSpeedQue;
        set<pair<int,int>> visitedConf;
        int sequenceLength = 0;
        
        posSpeedQue.push({0, 1});
        visitedConf.insert({0, 1});

        while(!posSpeedQue.empty())
        {
            int queSize = posSpeedQue.size();
            while(queSize--)
            {
                int position = posSpeedQue.front().first;
                int speed = posSpeedQue.front().second;
                posSpeedQue.pop();
                
                int nextPosition = position + speed;
                if(abs(position) > target*2) continue;
                if(nextPosition == target) return sequenceLength + 1;

                // push for 'A' instruction
                int speedA = speed * 2;
                if(!visitedConf.count({nextPosition, speedA}))
                {
                    visitedConf.insert({nextPosition, speedA});
                    posSpeedQue.push({nextPosition, speedA});
                }
                
                // push for 'R' instruction
                int speedR = speed > 0? -1 : 1;
                if(!visitedConf.count({position, speedR}) && ((nextPosition > target && speedR < 0) || (nextPosition < target && speedR > 0)))
                {
                    visitedConf.insert({position, speedR});
                    posSpeedQue.push({position, speedR});
                }
            }
            sequenceLength++;
        }

        return -1;
    }
};
