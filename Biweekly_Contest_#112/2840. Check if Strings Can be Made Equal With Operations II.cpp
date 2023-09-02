class Solution {
public:
    bool checkStrings(string s1, string s2) 
    {
        int n = s1.size();
        string o1 = "";
        string e1 = "";
        string o2 = "";
        string e2 = "";
        for(int i = 0; i < n; i++)
        {
            if(i&1)
            {
                o1 += s1[i];
                o2 += s2[i];
            }
            else
            {
                e1 += s1[i];
                e2 += s2[i];
            }
        }
        
        sort(o1.begin(), o1.end());
        sort(o2.begin(), o2.end());
        sort(e1.begin(), e1.end());
        sort(e2.begin(), e2.end());
        
        return o1 == o2 && e1 == e2;
    }
};
