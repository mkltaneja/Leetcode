class LUPrefix {
public:
    
    vector<int> exist;
    int x;
    LUPrefix(int n) 
    {
        exist.resize(n+1,0);
        x = 1;
    }
    
    void upload(int video) 
    {
        exist[video] = 1;
    }
    
    int longest() 
    {
        while(x < exist.size() && exist[x]) x++;
        return x-1;
    }
};

/**
 * Your LUPrefix object will be instantiated and called as such:
 * LUPrefix* obj = new LUPrefix(n);
 * obj->upload(video);
 * int param_2 = obj->longest();
 */
