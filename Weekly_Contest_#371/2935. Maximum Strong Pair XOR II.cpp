class Solution {
public:
    
    class Trie 
    {
        public:
        vector<Trie*> children;
        int count;

        Trie() 
        {
            children.resize(2);
            for (int i = 0; i < 2; i++) 
                this->children[i] = nullptr;
            this->count = 0;
        }
    };
    
    int j;
    void insert(Trie* root, int num) 
    {
        Trie* curr = root;
        for (int i = 31; i >= 0; i--) 
        {
            int bit = (num >> i) & 1;
            if (!curr->children[bit]) 
                curr->children[bit] = new Trie();
            curr = curr->children[bit];
            curr->count++;
        }
    }
    
    void remove(Trie* root, int idx, vector<int> &arr)
    {
        while(j >= idx)
        {
            Trie* curr = root;
            for (int i = 31; i >= 0; i--) 
            {
                int bit = (arr[j] >> i) & 1;
                curr = curr->children[bit];
                curr->count--;
            }
            j--;
        }
    }
    
    int maximumStrongPairXor(vector<int>& nums) 
    {
        int n = nums.size();
        j = n-1;
        vector<vector<int>> cb(n, vector<int> (32, 0));
        sort(nums.begin(), nums.end());
        int ans = 0;
        
        Trie* root = new Trie();
        int maxXOR = 0;
        
        for(int i = n-1; i >= 0; i--)
        {
            int ub = upper_bound(nums.begin(), nums.end(), nums[i] * 2) - nums.begin();
            
            remove(root, ub, nums);
            
            int currXOR = 0;
            Trie* curr = root;

            for (int j = 31; j >= 0; j--) 
            {
                int bit = (nums[i] >> j) & 1;
                int oppBit = 1 ^ bit;

                if(!curr) break;
                if (curr->children[oppBit] && curr->children[oppBit]->count > 0)
                {
                    currXOR |= (1 << j);
                    curr = curr->children[oppBit];
                }
                else
                    curr = curr->children[bit];
            }

            maxXOR = max(maxXOR, currXOR);
            insert(root, nums[i]);
        }
        
        return maxXOR;
    }
};
