class Solution {
public:
    bool isItPossible(string word1, string word2) 
    {
        vector<int> map1(26), map2(26);
        int dis1 = 0, dis2 = 0;
        for(char c : word1)
        {
            dis1 += map1[c-'a'] == 0;
            map1[c-'a']++;
        }
        for(char c : word2)
        {
            dis2 += map2[c-'a'] == 0;
            map2[c-'a']++;
        }

        if(dis2 < dis1)
        {
            swap(dis1, dis2);
            swap(map1, map2);
        }
        
        int diff = dis2 - dis1;
        if(diff > 2) return false;
        
        for(int i = 0; i < 26; i++)
        {
            if(!map2[i]) continue;
            for(int j = 0; j < 26; j++)
            {
                if(!map1[j]) continue;
                if(i == j)
                {
                    if(diff == 0) return true;
                    continue;
                }

                int x = 0, y = 0;
                
                if(!map1[i]) x++;
                if(map1[j] == 1) x--;
                
                if(!map2[j]) y++;
                if(map2[i] == 1) y--;
                
                if(diff == x-y) return true;
            }
        }
        
        return false;
    }
};
