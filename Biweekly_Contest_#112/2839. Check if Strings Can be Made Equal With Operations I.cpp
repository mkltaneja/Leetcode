class Solution {
public:
    bool canBeEqual(string s1, string s2) 
    {
        string o1 = s1.substr(1, 1);
        o1 += s1[3];
        string o2 = s2.substr(1, 1);
        o2 += s2[3];
        string e1 = s1.substr(0, 1);
        e1 += s1[2];
        string e2 = s2.substr(0, 1);
        e2 += s2[2];
        sort(o1.begin(), o1.end());
        sort(o2.begin(), o2.end());
        sort(e1.begin(), e1.end());
        sort(e2.begin(), e2.end());
        
        return o1 == o2 && e1 == e2;
    }
};

// METHOD 2 

class Solution {
public:
    bool canBeEqual(string s1, string s2) 
    {
        auto sort = [&](string &s){
            if(s[0] > s[2]) swap(s[0], s[2]);
            if(s[1] > s[3]) swap(s[1], s[3]);
        };
        
        sort(s1);
        sort(s2);
        return s1 == s2;
    }
};
