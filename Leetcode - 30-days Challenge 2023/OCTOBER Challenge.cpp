
// DAY 1 (557. Reverse Words in a String III)=========================================================================

string reverseWords(string s) 
{
    string ans = "", prev = "";
    for(int i = 0; i <= s.size(); i++)
    {
        if(i == s.size() || s[i] == ' ')
        {
            reverse(prev.begin(), prev.end());
            ans += prev + (i != s.size()? " " : "");
            prev = "";
        }
        else prev += s[i];
    }

    return ans;
}

// DAY 2 (2038. Remove Colored Pieces if Both Neighbors are the Same Color)============================================================

bool winnerOfGame(string colors) 
{
    int As = 0, Bs = 0, Aturns = 0, Bturns = 0;
    for(char c : colors)
    {
        if(c == 'A')
        {
            As++;
            Bturns += max(0, Bs-2);
            Bs = 0;
        }
        else
        {
            Bs++;
            Aturns += max(0, As-2);
            As = 0;
        }
    }
    Aturns += max(0, As-2);
    Bturns += max(0, Bs-2);

    bool AliceWon = Aturns > Bturns;

    return AliceWon;
}

// DAY 3 (1512. Number of Good Pairs)=====================================================================================

int numIdenticalPairs(vector<int>& nums) 
{
    int ans = 0;
    unordered_map<int,int> mp;
    for(int x : nums)
        mp[x]++;
    for(auto p : mp)
        ans += p.second * (p.second - 1) / 2;

    return ans;
}

// DAY 4 (706. Design HashMap)=============================================================================================

// APPROACH 1 (Using 1D array of bigger size to avoid collision) --> Time = O(1), Space = O(MAX_NUMBER)

class MyHashMap {
public:

    vector<int> map;
    int size = 1e6+1;
    MyHashMap() 
    {
        map.assign(size, -1);
    }
    
    void put(int key, int value) 
    {
        map[key] = value;
    }
    
    int get(int key) 
    {
        return map[key];
    }
    
    void remove(int key) 
    {
        map[key] = -1;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// APPROACH 2 (Using BST to avoid collision) --> Time = O(size * log(queries)), Space = O(size*queries) --> [OPTIMIZED]

class MyHashMap {
public:

    class Node
    {
        public:
        Node* left, *right;
        int key, val;
        Node(int key, int val)
        {
            this->key = key;
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node* insert(Node* root, int key, int val)
    {
        if(!root)
            return new Node(key, val);
        if(root->key == key)
            root->val = val;
        else if(root->key < key)
            root->right = insert(root->right, key, val);
        else root->left = insert(root->left, key, val);

        return root;
    }

    Node* removeNode(Node* root, int key)
    {
        if(!root)
            return nullptr;
        if(root->key == key)
        {
            if(!root->left)
            {
                Node* tmp = root->right;
                delete root;
                return tmp;
            }
            else if(!root->right)
            {
                Node* tmp = root->left;
                delete root;
                return tmp;
            }

            Node* minNode = root->right;
            while(minNode->left) minNode = minNode->left;

            root->key = minNode->key;
            root->val = minNode->val;
            root->right = removeNode(root->right, minNode->key);
        }
        else if(root->key < key)
            root->right = removeNode(root->right, key);
        else root->left = removeNode(root->left, key);

        return root;
    }

    int getNodeVal(Node* root, int key)
    {
        if(!root)
            return -1;
        if(root->key < key)
            return getNodeVal(root->right, key);
        else if(root->key > key)
            return getNodeVal(root->left, key);
        else return root->val;
    }

    vector<Node*> map;
    int size = 10000;
    MyHashMap() 
    {
        map.assign(size, nullptr);
    }
    
    void put(int key, int value) 
    {
        int hash = key % size;
        map[hash] = insert(map[hash], key, value);
    }
    
    int get(int key) 
    {
        int hash = key % size;
        return getNodeVal(map[hash], key);
    }
    
    void remove(int key) 
    {
        int hash = key % size;
        map[hash] = removeNode(map[hash], key);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */
