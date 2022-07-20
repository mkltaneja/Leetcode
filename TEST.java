import java.util.*;

Input: nums = [2,3,1,1,4]
Output: true

Input: nums = [3,2,1,0,4]
Output: false

curr_jumps = 0 -> 3 -> 2 -> 1 -> 0

public TEST
{
    public boolean canReach(int n, int[] jumps)
    {
        int curr_jumps = 0;
        for(int i = 0; i < n-1; i++)
        {
            curr_jumps = max(curr_jumps, jumps[i]);
            if(curr_jumps == 0) return false;
            curr_jumps--;
        }
        return true;
    }

    public static void main(String[] args)
    {

    }
}