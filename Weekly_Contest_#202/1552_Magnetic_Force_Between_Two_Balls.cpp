
int maxDistance(vector<int>& position, int m) 
{
    sort(position.begin(), position.end());
    int lhs = 0, rhs = 1e9;
    
    while(lhs < rhs)
    {
        int last = -1e9;
        int placed = 0;
        int mid = (lhs + rhs + 1) / 2;
            
        for(int i : position)
        {
            if(i - last >= mid)
            {
                placed++;
                last = i;
            }
        }
        if(placed >= m)
            lhs = mid;
        else
            rhs = mid - 1;
    }
    return lhs;
}