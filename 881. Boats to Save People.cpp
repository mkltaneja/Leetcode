
int numRescueBoats(vector<int>& people, int limit) 
{
    int boats = 0;
    sort(people.begin(), people.end());
    int i = 0, j = people.size()-1;
    while(j >= i)
    {
        if(people[j] + people[i] <= limit) i++, j--;
        else j--;
        boats++;
    }
    return boats;
}